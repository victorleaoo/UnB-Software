#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

int32_t le_valor_nvs(char* dado_salvar){
    int32_t valor = 0;
    nvs_handle particao_padrao_handle;
    
    // Abre o acesso à partição nvs
    esp_err_t res_nvs = nvs_open("armazenamento", NVS_READONLY, &particao_padrao_handle);
    
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND){
        ESP_LOGE("NVS", "Namespace: armazenamento, não encontrado");
    }
    else{
        esp_err_t res = nvs_get_i32(particao_padrao_handle, dado_salvar, &valor);

        switch (res){
        case ESP_OK:
            printf("Valor armazenado: %d\n", (int) valor);
            break;
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE("NVS", "Valor não encontrado");
            return -1;
        default:
            ESP_LOGE("NVS", "Erro ao acessar o NVS (%s)", esp_err_to_name(res));
            return -1;
            break;
        }

        nvs_close(particao_padrao_handle);
    }
    return valor;
}

void grava_valor_nvs(char* dado_salvar, int32_t valor){
    nvs_handle particao_padrao_handle;

    esp_err_t res_nvs = nvs_open("armazenamento", NVS_READWRITE, &particao_padrao_handle);
    
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND){
        ESP_LOGE("NVS", "Namespace: armazenamento, não encontrado");
    }

    esp_err_t res = nvs_set_i32(particao_padrao_handle, dado_salvar, valor);
    if(res != ESP_OK)
    {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)", esp_err_to_name(res));
    } else {
        ESP_LOGI("NVS", "%s gravado com sucesso", dado_salvar);
    }

    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}