# ESP32 MQTT Library

This is component based on ESP-IDF for ESP32 

Full documentation and sample project: https://github.com/tuanpmt/esp32-mqtt

## Prerequire

- ESP32 compiler: 
- ESP-IDF: https://github.com/espressif/esp-idf

## Add to your application as component

`git submodule addhttps://github.com/tuanpmt/espmqtt compoments/espmqtt`

## Usage

```
mqtt_client_t *client = mqtt_new("mqtt://username:pass@host.com:port/clientid");
//mqtt_client_t *client = mqtt_new("mqtts://username:pass@host.com:port/clientid");
client->event_connected = client_connected;
client->event_subscribe = client_subscribe;

mqtt_start(client);
```
