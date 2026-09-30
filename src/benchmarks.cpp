#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>

#include "unique_ptr.hpp"
#include "shared_ptr.hpp"

struct test_object {
    int value;

    test_object(int value = 0) : value(value) {}
};

using clock_type = std::chrono::high_resolution_clock;

double raw_benchmark(size_t count) {
    auto start = clock_type::now();

    test_object** objects = new test_object*[count];

    for (auto i = 0; i < count; ++i) objects[i] = new test_object(static_cast<int>(i));

    for (size_t i = 0; i < count; ++i) delete objects[i];

    delete[] objects;

    auto end = clock_type::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double unique_benchmark(size_t count) {
    auto start = clock_type::now();

    unique_ptr<test_object>* objects = new unique_ptr<test_object>[count];

    for (size_t i = 0; i < count; ++i) objects[i].reset(new test_object(static_cast<int>(i)));

    delete[] objects;

    auto end = clock_type::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double shared_benchmark(size_t count) {
    auto start = clock_type::now();

    shared_ptr<test_object>* objects = new shared_ptr<test_object>[count];

    for (size_t i = 0; i < count; ++i) objects[i].reset(new test_object(static_cast<int>(i)));

    delete[] objects;

    auto end = clock_type::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double std_unique_benchmark(size_t count) {
    auto start = clock_type::now();

    std::unique_ptr<test_object>* objects = new std::unique_ptr<test_object>[count];

    for (size_t i = 0; i < count; ++i) objects[i] = std::make_unique<test_object>(static_cast<int>(i));

    delete[] objects;

    auto end = clock_type::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

double std_shared_benchmark(size_t count) {
    auto start = clock_type::now();

    std::shared_ptr<test_object>* objects = new std::shared_ptr<test_object>[count];

    for (size_t i = 0; i < count; ++i) objects[i] = std::make_shared<test_object>(static_cast<int>(i));

    delete[] objects;

    auto end = clock_type::now();

    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main() {
    const size_t counts[] = {10000, 100000, 1000000};

    for (size_t count : counts) {
        std::cout
            << "Objects: " << count << "\n"
            << "Raw: " << raw_benchmark(count) << " ms\n"
            << "Unique: " << unique_benchmark(count) << " ms\n"
            << "std::unique: " << std_unique_benchmark(count) << " ms\n"
            << "Shared: " << shared_benchmark(count) << " ms\n"
            << "std::shared: " << std_shared_benchmark(count) << " ms\n\n";
    }

    return 0;
}