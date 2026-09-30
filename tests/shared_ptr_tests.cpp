#include <gtest/gtest.h>
#include "shared_ptr.hpp"
#include "array_sequence.hpp"

TEST(shared_ptr, constructor) {
    array_sequence<int> source = {1, 2, 3};
    shared_ptr<array_sequence<int>> ptr(new array_sequence<int>(source));

    ASSERT_NE(ptr.get(), nullptr);
    ASSERT_EQ(ptr->size(), 3);
    ASSERT_EQ(ptr.use_count(), 1);
}

TEST(shared_ptr, dereference) {
    array_sequence<int> source = {1, 2, 3};
    shared_ptr<array_sequence<int>> ptr(new array_sequence<int>(source));

    ASSERT_EQ((*ptr)[0], 1);

    (*ptr)[0] = 10;

    ASSERT_EQ((*ptr)[0], 10);
}

TEST(shared_ptr, arrow_operator) {
    array_sequence<int> source = {1, 2, 3};
    shared_ptr<array_sequence<int>> ptr(new array_sequence<int>(source));

    ASSERT_EQ(ptr->size(), 3);
    ASSERT_EQ(ptr->get(0), 1);
}

TEST(shared_ptr, get) {
    array_sequence<int> source = {1, 2, 3};
    shared_ptr<array_sequence<int>> ptr(new array_sequence<int>(source));

    ASSERT_NE(ptr.get(), nullptr);
    ASSERT_EQ(ptr.get()->get(0), 1);
}

TEST(shared_ptr, bool_operator) {
    shared_ptr<array_sequence<int>> empty;

    array_sequence<int> source = {1, 2, 3};
    shared_ptr<array_sequence<int>> ptr(new array_sequence<int>(source));

    ASSERT_FALSE(empty);
    ASSERT_TRUE(ptr);
}

TEST(shared_ptr, use_count) {
    array_sequence<int> source = {1, 2, 3};
    shared_ptr<array_sequence<int>> first(new array_sequence<int>(source));

    ASSERT_EQ(first.use_count(), 1);

    shared_ptr<array_sequence<int>> second(first);

    ASSERT_EQ(first.use_count(), 2);
    ASSERT_EQ(second.use_count(), 2);
}

TEST(shared_ptr, copy_constructor) {
    array_sequence<int> source = {1, 2, 3};
    shared_ptr<array_sequence<int>> first(new array_sequence<int>(source));
    shared_ptr<array_sequence<int>> second(first);

    ASSERT_EQ(first.get(), second.get());
    ASSERT_EQ(first.use_count(), 2);
    ASSERT_EQ(second.use_count(), 2);
    ASSERT_EQ(second->size(), 3);
}

TEST(shared_ptr, copy_operator) {
    array_sequence<int> source1 = {1, 2, 3};
    array_sequence<int> source2 = {4, 5};

    shared_ptr<array_sequence<int>> first(new array_sequence<int>(source1));
    shared_ptr<array_sequence<int>> second(new array_sequence<int>(source2));

    second = first;

    ASSERT_EQ(first.get(), second.get());
    ASSERT_EQ(first.use_count(), 2);
    ASSERT_EQ(second.use_count(), 2);
    ASSERT_EQ(second->size(), 3);
}

TEST(shared_ptr, move_constructor) {
    array_sequence<int> source = {1, 2, 3};
    shared_ptr<array_sequence<int>> first(new array_sequence<int>(source));
    shared_ptr<array_sequence<int>> second(std::move(first));

    ASSERT_EQ(first.get(), nullptr);
    ASSERT_EQ(first.use_count(), 0);

    ASSERT_NE(second.get(), nullptr);
    ASSERT_EQ(second.use_count(), 1);
    ASSERT_EQ(second->size(), 3);
}

TEST(shared_ptr, move_operator) {
    array_sequence<int> source1 = {1, 2, 3};
    array_sequence<int> source2 = {4, 5};

    shared_ptr<array_sequence<int>> first(new array_sequence<int>(source1));
    shared_ptr<array_sequence<int>> second(new array_sequence<int>(source2));

    second = std::move(first);

    ASSERT_EQ(first.get(), nullptr);
    ASSERT_EQ(first.use_count(), 0);

    ASSERT_NE(second.get(), nullptr);
    ASSERT_EQ(second.use_count(), 1);
    ASSERT_EQ(second->size(), 3);
}

TEST(shared_ptr, reset) {
    array_sequence<int> source1 = {1, 2, 3};
    array_sequence<int> source2 = {4, 5};

    shared_ptr<array_sequence<int>> ptr(new array_sequence<int>(source1));

    ptr.reset(new array_sequence<int>(source2));

    ASSERT_EQ(ptr.use_count(), 1);
    ASSERT_EQ(ptr->size(), 2);
    ASSERT_EQ((*ptr)[0], 4);
    ASSERT_EQ((*ptr)[1], 5);
}

TEST(shared_ptr_array, subscript) {
    shared_ptr<int[]> ptr(new int[3]);

    ptr[0] = 10;
    ptr[1] = 20;
    ptr[2] = 30;

    ASSERT_EQ(ptr[0], 10);
    ASSERT_EQ(ptr[1], 20);
    ASSERT_EQ(ptr[2], 30);
}

TEST(shared_ptr_array, use_count) {
    shared_ptr<int[]> first(new int[3]);
    shared_ptr<int[]> second(first);

    ASSERT_EQ(first.use_count(), 2);
    ASSERT_EQ(second.use_count(), 2);
}