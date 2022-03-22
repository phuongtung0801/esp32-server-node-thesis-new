#include "WebConfig.h"

// khai bao wifi, luu y chỉ kết nối 2.4GHz
const char *ssid = "TUNG";
const char *password = "123456789";
// config static IP
IPAddress local_IP(192, 168, 1, 8);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);
// http server port 80
AsyncWebServer server(80);
// websocket server
AsyncWebSocket ws("/ws");

WebConfig TungWeb;

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    case WS_EVT_DATA:
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}

void WebConfig::init()
{
    // register websocket
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    // start server
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", "text/html");
              Serial.println("index.html send"); });
}

void WebConfig::begin()
{
    // Connect to Wi-Fi
    // if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
    // {
    //     Serial.println("STA failed to config");
    // }

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println(WiFi.localIP());

    server.begin();
}

void WebConfig::WebServerTask()
{
    TaskHandle_t WebTaskHanlde;
    xTaskCreateUniversal(
        WebServerAPI,
        "WebServerAPI",
        40000,
        NULL,
        3,
        &WebTaskHanlde,
        1);
    Serial.println("running WebServerTask");
}

void WebServerAPI(void *param)
{
    // server.begin();
    vTaskDelete(NULL);
    Serial.println("Server begin");
    // for (;;)
    // {
    //     Serial.println("Server begin");
    //     const TickType_t xDelay = 100 / portTICK_PERIOD_MS;
    //     vTaskDelay(xDelay);
    // }
}
