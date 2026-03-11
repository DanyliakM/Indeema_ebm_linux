#include "MqttService.hpp"
#include "logger.hpp"

MqttService::MqttService(const std::string& broker, const std::string& clientId, const std::string& cmdTopic, const std::string& statusTopic)
    : _client(broker, clientId), _topic_cmd(cmdTopic), _topic_status(statusTopic) {
    _client.set_callback(*this);
}

bool MqttService::connect() {
    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);
    connOpts.set_automatic_reconnect(true);

    try {
        _client.connect(connOpts)->wait();
        _client.subscribe(_topic_status, 1)->wait();
        return true;
    } catch (const mqtt::exception& exc) {
        Logger::error(exc.what());
        return false;
    }
}

void MqttService::send(const std::string& payload) {
    try {
        auto msg = mqtt::make_message(_topic_cmd, payload);
        msg->set_qos(1);
        _client.publish(msg)->wait();
    } catch (const mqtt::exception& exc) {
        Logger::error(exc.what());
    }
}

void MqttService::message_arrived(mqtt::const_message_ptr msg) {
    Logger::info("MQTT Status: " + msg->get_payload_str());
}

void MqttService::connection_lost(const std::string& cause) {
    Logger::error("MQTT Connection lost: " + cause);
}