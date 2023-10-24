cmake_minimum_required(VERSION 3.0)

project(interval-swap VERSION 0.0.1)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)

add_executable(appTest test/src/test.cpp)
target_include_directories(appTest PRIVATE include)
target_link_libraries(appTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

set_target_properties(${CMAKE_PROJECT_NAME} appTest PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

enable_testing()
add_test(appTest appTest)

