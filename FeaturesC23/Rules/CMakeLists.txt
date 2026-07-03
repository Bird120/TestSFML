cmake_minimum_required(VERSION 3.16)
project(FactorialBenchmark CXX)

set(CMAKE_CXX_STANDARD 17)

# 1. Chercher la bibliothèque installée sur Ubuntu
find_package(benchmark REQUIRED)

add_executable(my_bench benchmarks.cpp)

# 2. Lier la bibliothèque à ton exécutable
target_link_libraries(my_bench benchmark::benchmark)