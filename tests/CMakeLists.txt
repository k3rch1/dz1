add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../googletest
    googletest-build
)

add_executable(
    tests
    shared_ptr_tests.cpp
    unique_ptr_tests.cpp
)

target_include_directories(
    tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(
    tests
    GTest::gtest_main
    lab5
)

include(GoogleTest)

gtest_discover_tests(tests)