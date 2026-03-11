cmake_minimum_required(VERSION 3.10)
project(IndeemaHostApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

add_subdirectory(common)

add_executable(${PROJECT_NAME} common/src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE common_lib)