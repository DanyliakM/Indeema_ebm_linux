cmake_minimum_required(VERSION 3.10)
project(SerialTest)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

find_library(SERIAL_LIBRARY NAMES serial)
if(NOT SERIAL_LIBRARY)
    message(FATAL_ERROR "Бібліотеку serial не знайдено! Перевірте чи виконали sudo make install у папці serial.")
endif()

add_subdirectory(common)

add_executable(my_app main.cpp)

target_link_libraries(my_app common_lib ${SERIAL_LIBRARY} ${JSONCPP_LIBRARIES})
target_include_directories(my_app PRIVATE ${JSONCPP_INCLUDE_DIRS})

file(COPY config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})