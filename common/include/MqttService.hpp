#pragma once
#include <string>
#include <mqtt/async_client.h>

class MqttService : public virtual mqtt::callback {
private:
    mqtt::async_client _client;
    std::string _topic_cmd;
    std::string _topic_status;

    void message_arrived(mqtt::const_message_ptr msg) override;
    void connection_lost(const std::string& cause) override;

public:
    MqttService(const std::string& broker, const std::string& clientId, const std::string& cmdTopic, const std::string& statusTopic);
    bool connect();
    void send(const std::string& payload);
};