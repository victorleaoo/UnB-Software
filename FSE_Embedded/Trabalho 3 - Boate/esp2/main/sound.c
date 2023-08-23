/*
  -> Arquivo para o sensor de som
    - Configura o a detecção de som do sensor
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


// Tarefa para lidar com o sensor de som

void sound_task(void *arg)
{
  int32_t tocando;
  char JsonAtr[200];

  while (1)
  {
    int sound_detected = gpio_get_level(SOUND_SENSOR);

    if (sound_detected == 1) // Verifica se o pino está baixo
    {
      tocando = 1;
      ESP_LOGI("SENSOR", "Som detectado");
/*    sprintf(JsonAtr, "{\"tocando\":1}");
      mqtt_envia_mensagem("v1/devices/me/attributes", JsonAtr); */
      grava_valor_nvs("tocando", tocando);
    }else {
      tocando =0;
/*    sprintf(JsonAtr, "{\"tocando\":0}");
      mqtt_envia_mensagem("v1/devices/me/attributes", JsonAtr); */
      grava_valor_nvs("tocando", tocando);
    }

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}