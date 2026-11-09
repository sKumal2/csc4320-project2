/*
new build released -> smoke test -> passed -> move to detailed testing 
                                    failed -> move to debugging

Before the queue implementation, complete a smoke test: start two workers, have each print its identifier once, join
both, and then print a final main-thread message. Submit source, build/run commands, and actual output at Day 7.
Worker print order need not be fixed; the main-thread final message must follow both workers finishing.

What it needs to do (Section 10, as summarised in your plan):
1. Start two worker threads.
2. Each worker prints its ID once.
3. Join both workers.
4. Only after that, main prints a final message.
*/


#include <iostream>
#include <thread>

void worker1(int id) {
    std::cout << "Worker1 finished " << id << '\n';
}

void worker2(int id) {
    std::cout << "Worker2 finished " << id << '\n';
}

int main() {
    std::thread t1, t2;
    try{
        std::thread t1(worker1, 1);
        std::thread t2(worker2, 2);
        t1.join();
        t2.join();
        std::cout << "Main finished\n";
    }
    catch (const std::exception& e) {
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();

    std::cerr << "Thread creation or join failed: "
              << e.what() << '\n';
    return 1;
    }

    return 0;
}
