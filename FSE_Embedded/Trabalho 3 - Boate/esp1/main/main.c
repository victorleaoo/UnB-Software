/*
  -> Arquivo Main
    - Conexões Wifi e MQTT
    - Cria Tasks iniciais de cada módulo
*/

// Includes "externos"
#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

// Includes de outros módulos próprios
#include "wifi.h"
#include "mqtt.h"
#include "buzzer.h"
#include "rgb_led.h"
#include "ds18b20.h"
#include "music.h"
#include "nvs.h"

// Semáforos
SemaphoreHandle_t conexaoWifiSemaphore;
SemaphoreHandle_t conexaoMQTTSemaphore;

#define LED_PLACA 2
int32_t highTemp = 0;

// Após conexão no Wifi, faz conexão com MQTT
void conectadoWifi(void * params)
{
  while(true)
  {
    // Espera por conexão Wifi estar completa
    if(xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY)){
      // Processamento Internet
      mqtt_start();
    }
  }
}

// A partir da leitura a cada segundo da temperatura no sensor
// envia para o servidor (Thingsboard)
void enviaTemperaturaParaServidor(void * params){
  char mensagem[50];
  char JsonAtr[200];
  char mensagem_desligado[50];

  // Espera conexão MQTT estar pronta
  if(xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY)){

    // Envia atributo de que NÃO está tocando a música
    sprintf(mensagem_desligado, "{\"tocando\": 0}");
    mqtt_envia_mensagem("v1/devices/me/attributes", mensagem_desligado);

    esp_rom_gpio_pad_select_gpio(LED_PLACA);
    gpio_set_direction(LED_PLACA, GPIO_MODE_OUTPUT);
    while(true){
      float temperatura = read_temperature();
      // Caso retorne erro, não envia para o servidor
      if (temperatura == 0.0){
        continue;
      }

      // Envia mensagem em JSON
      sprintf(mensagem, "{\"temperature\": %f}", temperatura);
      mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);

      // Envia atributo para o Led de Sistema de Alarme
      if (temperatura >= 28){
        sprintf(JsonAtr, "{\"highTemp\": 1}");
        highTemp = 1;
        grava_valor_nvs("highTemp", highTemp);
      } else{
        sprintf(JsonAtr, "{\"highTemp\": 0}");
        highTemp = 0;
        grava_valor_nvs("highTemp", highTemp);
      }

      //printf("Valor gravado no nvs: %d\n", (int) le_valor_nvs("highTemp"));

      mqtt_envia_mensagem("v1/devices/me/attributes", JsonAtr);

      // Espera a cada segundo
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }
}


// Função Main do projeto
void app_main(void)
{
  // Inicializa o NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
  
  // Faz conexão Wifi
  conexaoWifiSemaphore = xSemaphoreCreateBinary();
  conexaoMQTTSemaphore = xSemaphoreCreateBinary();
  wifi_start();

  // Task: Inicia serviço MQTT
  xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
  // Task: Enviar temperatura a cada segunda
  xTaskCreate(&enviaTemperaturaParaServidor, "Enviando Temperatura ao Servidor", 4096, NULL, 1, NULL);
}