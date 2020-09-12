#include "ThreadPool.hpp"
#include <unistd.h>
#include <iostream>

int main() {
    ThreadPool threads(4);

    for (auto i = 0; i < 4; i++) {
        std::cout << "hello " << i << std::endl;
        threads.enqueue([](int sec) { sleep(sec); std::cout << "world" << std::endl; }, i);
    }
}
