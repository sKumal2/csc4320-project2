
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <semaphore>

int main() {
    std::mutex mtx;
    std::condition_variable cv;
    std::counting_semaphore<2> sem(1);

    std::thread worker([&]() {
        sem.acquire();

        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "Worker running!" << std::endl;
        }

        sem.release();
    });

    worker.join();

    std::cout << "C++20 environment OK!" << std::endl;
    return 0;
}
