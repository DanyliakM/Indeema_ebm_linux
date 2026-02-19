cmake_minimum_required(VERSION 3.10)
project(SerialTest)

# 1. Шукаємо jsoncpp
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

# 2. Шукаємо нашу встановлену бібліотеку serial напряму
find_library(SERIAL_LIBRARY NAMES serial)
if(NOT SERIAL_LIBRARY)
    message(FATAL_ERROR "Бібліотеку serial не знайдено! Перевірте чи виконали sudo make install у папці serial.")
endif()

# 3. Підключаємо папку common (де лежить логер і парсер)
add_subdirectory(common)

# 4. Створюємо виконуваний файл
add_executable(my_app main.cpp)

# 5. Лінкуємо всі 3 бібліотеки: serial, jsoncpp та нашу оновлену common_lib
target_link_libraries(my_app ${SERIAL_LIBRARY} ${JSONCPP_LIBRARIES} common_lib)
target_include_directories(my_app PRIVATE ${JSONCPP_INCLUDE_DIRS})

# 6. Автоматично копіюємо config.json у папку збірки (щоб не було помилки конфігурації)
file(COPY config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})