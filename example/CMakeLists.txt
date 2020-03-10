cmake_minimum_required(VERSION 3.13)

project(example_JsonPP LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(example_JsonPP_SRCS
    src/main.cpp
    )

add_executable(example_JsonPP ${example_JsonPP_SRCS})

find_package(PkgConfig REQUIRED)

pkg_check_modules(JSONPP REQUIRED libjsonpp-0.1)
target_link_libraries(example_JsonPP PUBLIC ${JSONPP_LIBRARIES})
target_link_options(example_JsonPP PUBLIC ${JSONPP_LDFLAGS})

install(TARGETS example_JsonPP
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/usr/bin)

