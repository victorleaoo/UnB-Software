/*
  -> Arquivo MQTT
    - Faz a conexão MQTT
    - Trata os eventos MQTT
*/

// Includes
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"
#include "cJSON.h"

#include "mqtt.h"
#include "buzzer.h"
#include "music.h"

#define TAG "MQTT"

// Semáforos
extern SemaphoreHandle_t conexaoMQTTSemaphore;
esp_mqtt_client_handle_t client;

extern int highTemp;

// Log de erro para erro no MQTT
static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0) {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

// Encontra o index da música escolhida para tocar
int find_music_index(const char* music_name, struct Music musics[]) {

    // Faz uma busca linear entre todas as buscas
    for (int i = 0; i < 4; i++) {
        if (strcmp(musics[i].name, music_name) == 0) {
            return i;  // Retorna o índice se encontrado
        }
    }

    return -1;  // Retorna -1 se não encontrado
}

// Handler para eventos MQTT
// Conexão, disconexão, inscrição, desinscrição, publicação, recebimento de dados e erro.
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, (int) event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    switch ((esp_mqtt_event_id_t)event_id) {

    // caso conecte no mqtt (inscreve em topicos)
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        xSemaphoreGive(conexaoMQTTSemaphore);
        esp_mqtt_client_subscribe(client, "v1/devices/me/rpc/request/+", 0);
        esp_mqtt_client_subscribe(client, "v1/devices/me/attributes/response/+", 0);
        break;
    
    // caso desconecta
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    // caso inscreva em algum topico
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, INSCRITO EM TOPICO - msg_id=%d", event->msg_id);
        break;

    // caso desinscreva em algum topico
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;

    // caso envia dado
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;

    // caso receba dado
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);

        // Leitura do JSON recebido
        cJSON* root = cJSON_Parse(event->data);
        
        // Se o tipo for um method (RPC)
        cJSON* method_item = cJSON_GetObjectItemCaseSensitive(root, "method");
        if (cJSON_IsString(method_item) && (method_item->valuestring != NULL)) {
            cJSON* params_item = cJSON_GetObjectItemCaseSensitive(root, "params");

            // Caso a temperatura esteja muito alta, não toca a música
            if (highTemp == 1){
                printf("Temperatura muito alta! Não é possível tocar música agora!");
                return;
            }

            // Verifica se o atributo é o esperado (1) para tocar música
            if (cJSON_IsNumber(params_item)) {
                // Envia uma mensagem para poder pegar o nome da música a ser tocada
                mqtt_envia_mensagem("v1/devices/me/attributes/request/1", "{\"clientKeys:\": \"musica\"}");
                return;
            }
        }

        // Se o tipo for um "client" (pegar valor de atributo)
        cJSON* client_item = cJSON_GetObjectItemCaseSensitive(root, "client");
        if (cJSON_IsObject(client_item)) {
            // Pega o nome da música
            cJSON* musica_item = cJSON_GetObjectItemCaseSensitive(client_item, "musica");

            if (cJSON_IsString(musica_item) && (musica_item->valuestring != NULL)) {
                // Músicas possíveis de serem tocadas
                struct Music musics[] = {
                    musica_mario(),
                    musica_sonic(),
                    musica_zelda(),
                    musica_megalovania()
                };

                // Pega nome da música escolhida pelo usuário
                const char* musica_nome = musica_item->valuestring;
                printf("musica: %s", musica_nome);
                
                // A partir do índice da música encontrado, implementa a lógica de tocar música
                int idx_musica = find_music_index(musica_nome, musics);
                if (idx_musica != -1){
                    ESP_LOGI("BUZZER", "Tocando a musica %s", musics[idx_musica].name);

                    // Toca música
                    toca_musica(musics[idx_musica]);

                    ESP_LOGI("BUZZER", "Finalizou a musica");
                } else{
                    ESP_LOGW("BUZZER", "Música não encontrada");
                }
                
            }
        }
        
        break;
    
    // Caso aconteça algum erro
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));

        }
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}

// Inicia o MQTT com as informações próprias
void mqtt_start()
{
    esp_mqtt_client_config_t mqtt_config = {
        .broker.address.uri = "mqtt://164.41.98.25",
        .credentials.username = "f9Ox3peTNOLDrknppdNG"
    };
    client = esp_mqtt_client_init(&mqtt_config);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}

// Função para enviar/publicar uma mensagem
void mqtt_envia_mensagem(char * topico, char * mensagem)
{
    int message_id = esp_mqtt_client_publish(client, topico, mensagem, 0, 1, 0);
    ESP_LOGI(TAG, "Mensagem enviada, ID: %d", message_id);
}