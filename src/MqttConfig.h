#ifndef MQTT_CONFIG_H
#define MQTT_CONFIG_H

#include <PubSubClient.h>
#include <painlessMesh.h>
#include "WiFiClient.h"

extern PubSubClient mqttClient(wifiClientSecure);

class MqttConfig
{
public:
    // void mqttCallback(char *topic, byte *payload, unsigned int length);
    void init();
    void loop();
};
extern MqttConfig TungMQTT;

#endif