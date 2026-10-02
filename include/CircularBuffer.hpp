// En vez de usar vectores que pueden usar fragmentaciones de memoria y latencia dinámicas este programa va a diseñar un Buffer Circular (Ring Buffer)

#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

#include <array>
#include <iostream>
#include <optional>
#include <condition_variable>
#include <mutex>
#include <vector>

namespace Lidar {
    template <typename T, size_t Capacity>
    class CircularBuffer {

        static_assert(Capacity > 0, "Error: Buffer capacity can not be 0");

        static_assert((Capacity & (Capacity-1)) == 0, "Error: Buffer capacity must be a power of 2");

        private:
            std::array<T, Capacity> buffer;
            size_t rd = 0;
            size_t wr = 0;
            size_t current_size = 0;

            bool closed = false;
            std::mutex mtx;
            std::condition_variable not_empty;
            std::condition_variable not_full;

            size_t bitwise(size_t index) {
                return (index + 1) & (Capacity - 1); //Reducción del coste de CPU con un and en vez de con mod
            }
            
        public:
            CircularBuffer() = default;

            bool push(T&& item) {
            
                std::unique_lock<std::mutex> lock(mtx);
                
                not_full.wait(lock, [this] { return current_size < Capacity || closed; });

                buffer[wr] = std::move(item);
                wr = bitwise(wr);
                current_size++;
                
                lock.unlock();

                not_empty.notify_one();

                return true;
            }

            bool push(const T& item) {
            
                std::unique_lock<std::mutex> lock(mtx);
                not_full.wait(lock, [this] { return current_size < Capacity || closed;});

                buffer[wr] = item;
                wr = bitwise(wr);
                current_size++;
                
                lock.unlock();
                
                not_empty.notify_one();

                return true;
            }

            std::optional<T> pop() {
                
                std::unique_lock<std::mutex> lock(mtx);
                
                not_empty.wait(lock, [this] {return current_size > 0 || closed; });

                if (current_size == 0 && closed) {
                    return std::nullopt;
                }
                
                auto value = std::move(buffer[rd]);
                rd = bitwise(rd);
                current_size--;

                lock.unlock();

                not_full.notify_one();
                
                return value;
                
            }
            /** @brief Pop de bloque de datos en los que el buffer otorgará un n <= que max_items
             *  @param max_items Número máximo de <T> que se quiere obtener 
             */
            size_t blockPop(std::vector<T> &block, size_t max_items) {
                
                std::unique_lock<std::mutex> lock(mtx);
                
                not_empty.wait(lock, [this] {return current_size > 0 || closed;});

                if (current_size == 0 && closed) {
                    return 0;
                }

                size_t n = std::min(current_size, max_items);

                block.clear();

                for (size_t i = 0; i < n; ++i) {
                    block.push_back(std::move(buffer[rd]));
                    rd = bitwise(rd);
                    current_size--;
                }

                lock.unlock();
                not_full.notify_one();

                return n;
                
            }

            void close() {
                std::lock_guard<std::mutex> lock(mtx);

                closed = true;

                not_empty.notify_all();
                not_full.notify_all();

            }

            size_t size() const {
                std::lock_guard<std::mutex> lock(mtx);
                return current_size;
            }

            bool isEmpty() {
                std::lock_guard<std::mutex> lock(mtx);
                return current_size == 0;
            }

            size_t getCapacity() const {
                return Capacity;
            }

            void clear() {
                std::lock_guard<std::mutex> lock(mtx);
                rd = 0;
                wr = 0;
                current_size = 0;
            }
    
    };

}

#endif
