add_library(common_lib src/logger.cpp src/JsonParser.cpp)

target_include_directories(common_lib PUBLIC include)