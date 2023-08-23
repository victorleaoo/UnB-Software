/*
  -> Arquivo para o encoder
    - Configura o encoder para detecção de movimento ou clicque, além de enviar os dados relacionados para a dash
*/

#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "wifi.h"
#include "mqtt.h"
#include "sound.h"
#include "nvs.h"
#include "encoder.h"

volatile int encoder_value = 0;
volatile bool button_pressed = false;
int selected_music = 0; // Índice da música selecionada

// Semáforos
extern SemaphoreHandle_t conexaoWifiSemaphore;
extern SemaphoreHandle_t conexaoMQTTSemaphore;


// Manipulador de interrupção para o encoder
void IRAM_ATTR encoder_isr_handler(void *arg)
{
    static int8_t lookup_table[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
    static uint8_t encoder_state = 0;
    encoder_state = ((encoder_state << 2) + (gpio_get_level(PIN_DT) << 1) + gpio_get_level(PIN_CLK)) & 0x0f;
    encoder_value += lookup_table[encoder_state];
}

// Manipulador de interrupção para o botão
void IRAM_ATTR button_isr_handler(void *arg)
{
    button_pressed = true;
}

// Tarefa para lidar com o encoder
void encoder_task(void *arg)
{
    int last_encoder_value = encoder_value;
    while (1)
    {
        if (last_encoder_value != encoder_value)
        {
            ESP_LOGI("ENCODER", "Value: %d", encoder_value);
            last_encoder_value = encoder_value;

            // Atualizar o índice da música selecionada
            int index = abs(encoder_value) / 2; // Descartar valores ímpares.
            index = index % NUM_MUSICAS;        // Garantir que o índice fique entre 0 e (NUM_MUSICAS - 1).

            if (encoder_value < 0)
            {
                index = NUM_MUSICAS - 1 - index; // Inverter o índice se encoder_value for negativo.
            }

            selected_music = index;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

// Tarefa para lidar com o botão
void button_task(void *arg)
{
    char JsonAtr[200];
    int32_t musica_escolhida;

    if (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
    {
        while (1)
        {
            if (button_pressed)
            {
                ESP_LOGI("BUTTON", "Button pressed");

                // Executar a ação correspondente à seleção da música
                switch (selected_music)
                {
                case 0:
                    // Tocar a música do Mario

                    musica_escolhida = 0;

                    sprintf(JsonAtr, "{\"musica\": \"mario\"}");
                    mqtt_envia_mensagem("v1/devices/me/attributes", JsonAtr);
                    grava_valor_nvs("musica_escolhida", musica_escolhida);

                    break;
                case 1:
                    // Tocar a música do Sonic

                    musica_escolhida = 1;

                    sprintf(JsonAtr, "{\"musica\": \"sonic\"}");
                    mqtt_envia_mensagem("v1/devices/me/attributes", JsonAtr);
                    grava_valor_nvs("musica_escolhida", musica_escolhida);
                    break;
                case 2:
                    // Tocar a música do Zelda

                    musica_escolhida = 2;

                    sprintf(JsonAtr, "{\"musica\": \"zelda\"}");
                    mqtt_envia_mensagem("v1/devices/me/attributes", JsonAtr);
                    grava_valor_nvs("musica_escolhida", musica_escolhida);

                    break;
                case 3:
                    // Tocar a música do Megalovania

                    musica_escolhida = 3;

                    sprintf(JsonAtr, "{\"musica\": \"megalovania\"}");
                    mqtt_envia_mensagem("v1/devices/me/attributes", JsonAtr);
                    grava_valor_nvs("musica_escolhida", musica_escolhida);
                    break;
                default:
                    break;
                }

                button_pressed = false;
            }
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}

