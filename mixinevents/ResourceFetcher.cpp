#include <chrono>
#include <thread>
#include "ResourceFetcher.hpp"

void ResourceFetcher::get() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    stuff = 32;
    blah = 2.3;
    _emit_ready();
}