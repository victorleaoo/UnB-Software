/*
  -> Arquivo para o Sensor ds18b20
    - Lê a temperatura do sensor
*/

// Includes
#include "ds18x20.h"
#include "ds18b20.h"
#include "esp_event.h"
#include "esp_log.h"
#include "driver/gpio.h"

// Definição Pin da GPIO
static const gpio_num_t SENSOR_GPIO = GPIO_NUM_4;

#define LED_PLACA 2
#define HIGH 1
#define LOW 0

// Função para ler a temperatura.
// Faz verificação de detecção dos sensores e erros.
float read_temperature(void){
    gpio_set_pull_mode(SENSOR_GPIO, GPIO_PULLUP_ONLY);

    ds18x20_addr_t addrs[1];
    float temps[8];
    size_t sensor_count = 0;
    
    esp_err_t res;

    // Verifica se há dispositivo conectado
    res = ds18x20_scan_devices(SENSOR_GPIO, addrs, 1, &sensor_count);

    // Erro de escanamento de sensores
    if (res != ESP_OK)
    {
        ESP_LOGE("TEMPERATURA", "Sensors scan error %d (%s)", res, esp_err_to_name(res));
        return 0.0;
    }

    // Nenhum sensor encontrado
    if (!sensor_count)
    {
        ESP_LOGW("TEMPERATURA", "No sensors detected!");
        return 0.0;
    }

    // Leitura da temperatura do sensor
    res = ds18x20_measure_and_read_multi(SENSOR_GPIO, addrs, sensor_count, temps);
        
    // Erro na leitura do sensor
    if (res != ESP_OK)
    {
        ESP_LOGE("TEMPERATURA", "Sensors read error %d (%s)", res, esp_err_to_name(res));
        return 0.0;
    }

    float temp_c = temps[0];
    ESP_LOGI("TEMPERATURA", "TEMPERATURA LIDA: %f", temp_c);
    
    // Verifica se houve erro ou não na leitura da temperatura
    if (__builtin_types_compatible_p(typeof(temp_c), float)){
        check_high_temperature(temp_c);
        return temp_c;
    } else{
        return 0.0;
    }
} 

// Função para verificar se a temperatura está muito alta.
// Caso sim, acende o LED da ESP, como sinal de aviso.
void check_high_temperature(float temp){
    if (temp >= 30){
        ESP_LOGI("-> CHECK TEMPERATURA", "TEMPERATURA ALTA!");
        gpio_set_level(LED_PLACA, HIGH);
        return;
    } else{
        gpio_set_level(LED_PLACA, LOW);
        return;
    }
}