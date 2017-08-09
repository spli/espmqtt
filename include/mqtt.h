#ifndef _MQTT_H_
#define _MQTT_H_
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "mqtt_config.h"
#include "mqtt_msg.h"
#include "ringbuf.h"

#if defined(CONFIG_MQTT_SECURITY_ON)
#include "openssl/ssl.h"
#endif

typedef struct mqtt_client_t mqtt_client_t;
typedef mqtt_client_t mqtt_client; //for backward compatible
typedef struct mqtt_setting_t mqtt_settings;
typedef struct mqtt_event_data_t mqtt_event_data_t;

typedef struct mqtt_buffer_t {
    struct mqtt_buffer_t *next;
    struct mqtt_buffer_t *prev;
    char *data;
    int len;
} mqtt_buffer_t;
/**
 * \return True on connect success, false on error
 */
typedef bool (* mqtt_connect_callback)(mqtt_client *client);
/**
 */
typedef void (* mqtt_disconnect_callback)(mqtt_client *client);
/**
 * \param[out] buffer Pointer to buffer to fill
 * \param[in] len Number of bytes to read
 * \param[in] timeout_ms Time to wait for completion, or 0 for no timeout
 * \return Number of bytes read, less than 0 on error
 */
typedef int (* mqtt_read_callback)(mqtt_client *client, void *buffer, int len, int timeout_ms);
/**
 * \param[in] buffer Pointer to buffer to write
 * \param[in] len Number of bytes to write
 * \param[in] timeout_ms Time to wait for completion, or 0 for no timeout
 * \return Number of bytes written, less than 0 on error
 */
typedef int (* mqtt_write_callback)(mqtt_client *client, const void *buffer, int len, int timeout_ms);
typedef void (* mqtt_event_callback)(mqtt_client *client, mqtt_event_data_t *event_data);

typedef struct mqtt_setting_t {
    mqtt_connect_callback    connect_cb;
    mqtt_disconnect_callback disconnect_cb;

    mqtt_read_callback       read_cb;
    mqtt_write_callback      write_cb;

    mqtt_event_callback      connected_cb;
    mqtt_event_callback      disconnected_cb;

    mqtt_event_callback      subscribe_cb;
    mqtt_event_callback      publish_cb;
    mqtt_event_callback      data_cb;

    char     *host
    char     *client_id;
    char     *username;
    char     *password;
    char     *lwt_topic;
    char     *lwt_msg;
    uint32_t port;
    uint32_t lwt_msg_len;
    uint32_t lwt_qos;
    uint32_t lwt_retain;
    uint32_t clean_session;
    uint32_t keepalive;
    bool     auto_reconnect;
} mqtt_setting_t;

typedef struct mqtt_event_data_t
{
  uint8_t type;
  const char* topic;
  const char* data;
  uint16_t topic_length;
  uint16_t data_length;
  uint16_t data_offset;
  uint16_t data_total_length;
} mqtt_event_data_t;

typedef struct mqtt_state_t
{
  uint16_t port;
  int auto_reconnect;
  mqtt_connect_info_t* connect_info;
  uint8_t* in_buffer;
  uint8_t* out_buffer;
  int in_buffer_length;
  int out_buffer_length;
  uint16_t message_length;
  uint16_t message_length_read;
  mqtt_message_t* outbound_message;
  mqtt_connection_t mqtt_connection;
  uint16_t pending_msg_id;
  int pending_msg_type;
  int pending_publish_qos;
} mqtt_state_t;

typedef struct mqtt_client_t {
  int socket;

#if defined(CONFIG_MQTT_SECURITY_ON)  // ENABLE MQTT OVER SSL
  SSL_CTX *ctx;
  SSL *ssl;
#endif

  mqtt_settings *settings;
  mqtt_state_t  mqtt_state;
  mqtt_connect_info_t connect_info;
  QueueHandle_t xSendingQueue;
  RINGBUF send_rb;
  mqtt_buffer_t *send_buffer;
  uint32_t keepalive_tick;

  int (*_connect)(struct mqtt_client_t *mqtt_client);
  int (*_read)(struct mqtt_client_t *mqtt_client, char *buffer, int len);
  int (*_write)(struct mqtt_client_t *mqtt_client, char *buffer, int len);
  int (*_close)(struct mqtt_client_t *mqtt_client);
} mqtt_client_t;

mqtt_client_t *mqtt_start(mqtt_settings *mqtt_info);
mqtt_client_t *mqtt_new(const char *uri);

void mqtt_stop(mqtt_client_t *mqtt_client);
void mqtt_task(void *pvParameters);
void mqtt_subscribe(mqtt_client *client, const char *topic, uint8_t qos);
void mqtt_unsubscribe(mqtt_client *client, const char *topic);
void mqtt_publish(mqtt_client* client, const char *topic, const char *data, int len, int qos, int retain);
void mqtt_destroy();
#endif
