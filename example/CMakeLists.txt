cmake_minimum_required(VERSION 3.13)

project(example_JsonPP LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(example_JsonPP_SRCS
    src/main.cpp
    )

add_executable(example_JsonPP ${example_JsonPP_SRCS})

find_package(ccdJsonpp 1.0 REQUIRED)
target_link_libraries(example_JsonPP PUBLIC ccdJsonpp)

