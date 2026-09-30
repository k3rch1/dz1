#include <gtest/gtest.h>
#include "unique_ptr.hpp"
#include "array_sequence.hpp"

TEST(unique_ptr, constructor) {
    array_sequence<int> source = {1, 2, 3};
    unique_ptr<array_sequence<int>> ptr(new array_sequence<int>(source));

    ASSERT_NE(ptr.get(), nullptr);
    ASSERT_EQ(ptr->size(), 3);
    ASSERT_EQ((*ptr)[0], 1);
    ASSERT_EQ((*ptr)[1], 2);
    ASSERT_EQ((*ptr)[2], 3);
}

TEST(unique_ptr, dereference) {
    array_sequence<int> source = {1, 2, 3};
    unique_ptr<array_sequence<int>> ptr(new array_sequence<int>(source));

    ASSERT_EQ((*ptr)[0], 1);

    (*ptr)[0] = 10;

    ASSERT_EQ((*ptr)[0], 10);
}

TEST(unique_ptr, arrow_operator) {
    array_sequence<int> source = {1, 2, 3};
    unique_ptr<array_sequence<int>> ptr(new array_sequence<int>(source));

    ASSERT_EQ(ptr->size(), 3);
    ASSERT_EQ(ptr->get(0), 1);
}

TEST(unique_ptr, get) {
    array_sequence<int> source = {1, 2, 3};
    unique_ptr<array_sequence<int>> ptr(new array_sequence<int>(source));

    ASSERT_NE(ptr.get(), nullptr);
    ASSERT_EQ(ptr.get()->get(0), 1);
}

TEST(unique_ptr, bool_operator) {
    unique_ptr<array_sequence<int>> empty;

    array_sequence<int> source = {1, 2, 3};
    unique_ptr<array_sequence<int>> ptr(new array_sequence<int>(source));

    ASSERT_FALSE(empty);
    ASSERT_TRUE(ptr);
}

TEST(unique_ptr, move_constructor) {
    array_sequence<int> source = {1, 2, 3};
    unique_ptr<array_sequence<int>> first(
        new array_sequence<int>(source)
    );

    unique_ptr<array_sequence<int>> second(std::move(first));

    ASSERT_EQ(first.get(), nullptr);
    ASSERT_NE(second.get(), nullptr);

    ASSERT_EQ(second->size(), 3);
    ASSERT_EQ((*second)[0], 1);
    ASSERT_EQ((*second)[1], 2);
    ASSERT_EQ((*second)[2], 3);
}

TEST(unique_ptr, move_operator) {
    array_sequence<int> source1 = {1, 2, 3};
    array_sequence<int> source2 = {4, 5};

    unique_ptr<array_sequence<int>> first(
        new array_sequence<int>(source1)
    );

    unique_ptr<array_sequence<int>> second(
        new array_sequence<int>(source2)
    );

    second = std::move(first);

    ASSERT_EQ(first.get(), nullptr);
    ASSERT_NE(second.get(), nullptr);

    ASSERT_EQ(second->size(), 3);
    ASSERT_EQ((*second)[0], 1);
    ASSERT_EQ((*second)[1], 2);
    ASSERT_EQ((*second)[2], 3);
}

TEST(unique_ptr, release) {
    array_sequence<int> source = {1, 2, 3};
    unique_ptr<array_sequence<int>> ptr(new array_sequence<int>(source));

    array_sequence<int>* raw = ptr.release();

    ASSERT_EQ(ptr.get(), nullptr);
    ASSERT_NE(raw, nullptr);
    ASSERT_EQ(raw->size(), 3);
    ASSERT_EQ(raw->get(0), 1);

    delete raw;
}

TEST(unique_ptr, reset) {
    array_sequence<int> source1 = {1, 2, 3};
    array_sequence<int> source2 = {4, 5};

    unique_ptr<array_sequence<int>> ptr(
        new array_sequence<int>(source1)
    );

    ptr.reset(new array_sequence<int>(source2));

    ASSERT_EQ(ptr->size(), 2);
    ASSERT_EQ((*ptr)[0], 4);
    ASSERT_EQ((*ptr)[1], 5);
}

TEST(unique_ptr, reset_to_null) {
    array_sequence<int> source = {1, 2, 3};
    unique_ptr<array_sequence<int>> ptr(new array_sequence<int>(source));

    ptr.reset();

    ASSERT_EQ(ptr.get(), nullptr);
    ASSERT_FALSE(ptr);
}

TEST(unique_ptr_array, destructor) {
    int destructor_count = 0;

    struct test_object {
        int* counter;

        ~test_object() {
            ++(*counter);
        }
    };

    {
        test_object* objects = new test_object[5];

        for (int i = 0; i < 5; ++i) {
            objects[i].counter = &destructor_count;
        }

        unique_ptr<test_object[]> ptr(objects);
    }

    ASSERT_EQ(destructor_count, 5);
}