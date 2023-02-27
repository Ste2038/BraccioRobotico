#ifndef MQTTmanager_H
#define MQTTmanager_H

#include <Arduino.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

void wifi_init(char* mqtt_server);
bool wifi_isConnected();
void mqtt_loop();
void mqtt_reconnect();
void mqtt_subscribe(char* topic);
void mqtt_subscribeAll();
void mqtt_publish(char* topic, char* payload);
void mqtt_publish(char* topic, int payload);
void ota_init(char* psw);

#endif