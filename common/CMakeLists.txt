add_library(common_lib 
    src/logger.cpp 
    src/JsonParser.cpp
    src/MqttService.cpp
)

target_include_directories(common_lib PUBLIC include)

target_link_libraries(common_lib PUBLIC
    paho-mqttpp3
    paho-mqtt3as
    ${JSONCPP_LIBRARIES}
    serial
    pthread
)