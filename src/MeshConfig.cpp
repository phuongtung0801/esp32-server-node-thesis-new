#include <MeshConfig.h>

MeshConfig TungMesh;
painlessMesh mesh;

// define mesh
#define MESH_PREFIX "tung"
#define MESH_PASSWORD "phuongtung0801"
#define MESH_PORT 5555
#define HOSTNAME "MQTT_Bridge"

// ham nay nhan callback khi chay mesh network
void receivedCallback(const uint32_t &from, const String &msg)
{
    Serial.printf("bridge: Received from %u msg=%s\n", from, msg.c_str());
    // String topic = "painlessMesh/from/2131961461";
    String topic = "painlessMesh/from/" + String(from);
    // mqttClient.publish(topic.c_str(), msg.c_str());
    Serial.println("Data received");
}

void MeshConfig::init()
{
    mesh.setDebugMsgTypes(ERROR | STARTUP | CONNECTION); // set before init() so that you can see startup messages

    // Channel set to 6. Make sure to use the same channel for your mesh and for you other
    // network (STATION_SSID)
    mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA, 6);
    mesh.onReceive(&receivedCallback);

    mesh.stationManual("TUNG", "123456789");
    mesh.setHostname(HOSTNAME);
    Serial.println("Mesh root node initialized");
}

void MeshConfig::loop()
{
    mesh.update();
}