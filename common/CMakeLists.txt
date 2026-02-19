# ТУТ ВАЖЛИВО: мають бути вказані обидва файли!
add_library(common_lib src/logger.cpp src/JsonParser.cpp)

# Вказуємо папку із заголовками
target_include_directories(common_lib PUBLIC include)