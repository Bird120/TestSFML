cmake_minimum_required(VERSION 3.30)
project(github_ VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(github_
        src/main.cpp
        src/calcul.cpp
)

target_include_directories(github_ PUBLIC include)
