# 1. Створюємо ціль бібліотеки як STATIC (архів) [cite: 84]
add_library(common STATIC
    src/logger.cpp
)

# 2. Вказуємо шлях до заголовків.
# PUBLIC означає, що цей шлях потрібен і самій бібліотеці,
# і будь-кому, хто її використовує[cite: 97, 98].
target_include_directories(common
    PUBLIC
    include
)