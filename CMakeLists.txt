cmake_minimum_required(VERSION 3.27)
project(engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

# project name
project(OrderEngine VERSION 1.0)

add_library(OrderEngineLib INTERFACE)
target_include_directories(OrderEngineLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(order_engine src/main.cpp)

# for testing
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(
    test_order_engine
    test/test_engine.cpp
)

target_link_libraries(test_order_engine
    OrderEngineLib
    GTest::gtest_main
)

target_include_directories(test_order_engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
include(GoogleTest)
gtest_discover_tests(test_order_engine)