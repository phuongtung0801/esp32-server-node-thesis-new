#ifndef WEB_CONFIG_H
#define WEB_CONFIG_H

#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFiClientSecure.h> //thu vien connect wifi
#include <WiFiClient.h>
#include "SPIFFS.h"

void WebServerAPI(void *param);

class WebConfig
{
public:
    void init();
    void begin();
    void WebServerTask();
    // void onWsEvent();
};
extern WebConfig TungWeb;
#endif