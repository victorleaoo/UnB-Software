/*
  -> Arquivo Main
    - Conexões Wifi e MQTT
    - Cria Tasks iniciais de cada módulo
    - Cria as funções do encoder 
*/

// includes

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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



#define BOTAO 0

RTC_DATA_ATTR int Acordou = 0;

// Semáforos

SemaphoreHandle_t conexaoWifiSemaphore;
SemaphoreHandle_t conexaoMQTTSemaphore;

// Tarefa para lidar com a conexão ao Wi-Fi
void conectadoWifi(void *params)
{
  while (true)
  {
    if (xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
    {
      // Processamento Internet
      mqtt_start();
    }
  }
}

void app_main()
{
  gpio_install_isr_service(0);


  // Inicializa o NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  conexaoWifiSemaphore = xSemaphoreCreateBinary();
  conexaoMQTTSemaphore = xSemaphoreCreateBinary();
  
  wifi_start();

  xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);


  // Configurar pinos do encoder como entradas
  gpio_set_direction(PIN_DT, GPIO_MODE_INPUT);
  gpio_set_pull_mode(PIN_DT, GPIO_PULLUP_ONLY);
  gpio_set_intr_type(PIN_DT, GPIO_INTR_ANYEDGE);
  gpio_isr_handler_add(PIN_DT, encoder_isr_handler, NULL);

  gpio_set_direction(PIN_CLK, GPIO_MODE_INPUT);
  gpio_set_pull_mode(PIN_CLK, GPIO_PULLUP_ONLY);
  gpio_set_intr_type(PIN_CLK, GPIO_INTR_ANYEDGE);
  gpio_isr_handler_add(PIN_CLK, encoder_isr_handler, NULL);

  gpio_set_direction(PIN_SW, GPIO_MODE_INPUT);
  gpio_set_pull_mode(PIN_SW, GPIO_PULLUP_ONLY);
  gpio_set_intr_type(PIN_SW, GPIO_INTR_POSEDGE);
  gpio_isr_handler_add(PIN_SW, button_isr_handler, NULL);

  xTaskCreate(encoder_task, "encoder_task", 2048, NULL, 10, NULL);
  xTaskCreate(button_task, "button_task", 2048, NULL, 10, NULL);

  // Configurar o pino do sensor de som como entrada
  gpio_set_direction(SOUND_SENSOR, GPIO_MODE_INPUT);
  gpio_set_pull_mode(SOUND_SENSOR, GPIO_PULLUP_ONLY);

  xTaskCreate(sound_task, "sound_task", 2048, NULL, 10, NULL);

/*   rtc_gpio_pullup_en(BOTAO);
  rtc_gpio_pulldown_dis(BOTAO);
  esp_sleep_enable_ext0_wakeup(BOTAO, 0);
  printf("Acordou %d vezes \n", Acordou++);
 
  vTaskDelay(15000 / portTICK_PERIOD_MS);
  printf("entrando em modo Deep Sleep\n");
  esp_deep_sleep_start(); */

}


