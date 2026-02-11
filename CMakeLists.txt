# 1. Мінімальна версія CMake [cite: 58]
cmake_minimum_required(VERSION 3.10)

# 2. Назва проекту [cite: 60]
project(coreapp)

# 3. Стандарт C++ 20 (для сучасних функцій) [cite: 62]
set(CMAKE_CXX_STANDARD 20)

# 4. Додаємо підпапку common (запускає CMakeLists.txt всередині common) [cite: 105]
add_subdirectory(common)

# 5. Створюємо виконуваний файл з main.cpp [cite: 107]
add_executable(coreapp main.cpp)

# 6. Лінкуємо бібліотеку common до нашого додатка [cite: 109]
target_link_libraries(coreapp PRIVATE common)