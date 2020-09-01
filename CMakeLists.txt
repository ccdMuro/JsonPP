cmake_minimum_required(VERSION 3.10)

project(ccdJsonpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build as shared library" ON)

add_library(ccdJsonpp
	src/JsonPP.cpp
	src/Value.cpp
	)

install(TARGETS ccdJsonpp DESTINATION lib)
install(FILES 
	include/Value.h
	include/JsonPP.h
	DESTINATION include)
