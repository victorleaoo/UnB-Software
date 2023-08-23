/*
  -> Arquivo para o Buzzer de música
    - Configura o toque das notas e, consequentemente, das músicas
*/

// Includes
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "esp_system.h"
#include "esp_log.h"
#include "esp_heap_caps.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "driver/gpio.h"
#include "driver/ledc.h"

#include "sdkconfig.h"
#include "buzzer.h"
#include "rgb_led.h"
#include "mqtt.h"
#include "nvs.h"

// Defines
#define BUZZER_GPIO 23
#define GPIO_OUTPUT_SPEED 0.7

// Função que configura o som de uma nota e o toca
void som_nota(int freq, int red, int green, int blue, int i, int size){
	// Define a nota (frequência)
	ledc_timer_config_t timer_conf = {
		.speed_mode = GPIO_OUTPUT_SPEED,
		.duty_resolution = LEDC_TIMER_10_BIT,
		.timer_num = LEDC_TIMER_0,
		.freq_hz = freq,
		.clk_cfg = LEDC_AUTO_CLK
		};
	ledc_timer_config(&timer_conf);

	ledc_channel_config_t ledc_conf = {
		.gpio_num = BUZZER_GPIO,
		.speed_mode = GPIO_OUTPUT_SPEED,
		.channel = LEDC_CHANNEL_0,
		.timer_sel = LEDC_TIMER_0,
		.hpoint = 0,
		.duty = 0x0
	};
	ledc_channel_config(&ledc_conf);

	// Toca a nota definida com volume máximo (0x03FF)
	if (i < size/4){
		ledc_set_duty(GPIO_OUTPUT_SPEED, LEDC_CHANNEL_0, 0x01FF);
		ledc_update_duty(GPIO_OUTPUT_SPEED, LEDC_CHANNEL_0);
	} else if (i >= size/4 && i <= 3*size/4) {
		ledc_set_duty(GPIO_OUTPUT_SPEED, LEDC_CHANNEL_0, 0x03FF);
		ledc_update_duty(GPIO_OUTPUT_SPEED, LEDC_CHANNEL_0);
	} else if (i > 3*size/4){
		ledc_set_duty(GPIO_OUTPUT_SPEED, LEDC_CHANNEL_0, 0x01FF);
		ledc_update_duty(GPIO_OUTPUT_SPEED, LEDC_CHANNEL_0);
	}
	

	// Troca a cor do LED para a definida na nota
	rgb_led_set_color(red, green, blue);
}

// Função que para de tocar o Buzzer
void para_buzzer(){
	ledc_set_duty(GPIO_OUTPUT_SPEED, LEDC_CHANNEL_0, 0);
	ledc_update_duty(GPIO_OUTPUT_SPEED, LEDC_CHANNEL_0);
}

// Destingue nota de delay (espera) e normal para toque
void chama_nota(struct Note note, int i, int size){
	// Caso seja uma nota de delay, só espera a duração
	if (note.freq == DELAY_NOTE){
		vTaskDelay(note.duracao / portTICK_PERIOD_MS);
		return;
	}

	// Toca a nota
	som_nota(note.freq, note.red, note.green, note.blue, i, size);
	vTaskDelay(note.duracao / portTICK_PERIOD_MS);
	para_buzzer();
}

// Toca a música (uma nota de cada vez)
void toca_musica(struct Music music){
	char mensagem_ligado[50];
	char mensagem_desligado[50];
	int32_t tocando;

	// Envia atributo de que está tocando a música
	sprintf(mensagem_ligado, "{\"tocando\": 1}");
	mqtt_envia_mensagem("v1/devices/me/attributes", mensagem_ligado);
	tocando = 1;
	grava_valor_nvs("tocando", tocando);

	//printf("Valor gravado no nvs: %d\n", (int) le_valor_nvs("tocando"));

	for (int i = 0; i < music.size; i++){
		chama_nota(music.notes[i], i, music.size);
	}

	// Envia atributo de que NÃO está tocando a música
	tocando = 0;
	sprintf(mensagem_desligado, "{\"tocando\": 0}");
	mqtt_envia_mensagem("v1/devices/me/attributes", mensagem_desligado);
	grava_valor_nvs("tocando", tocando);

	//printf("Valor gravado no nvs: %d\n", (int) le_valor_nvs("tocando"));

	// Para o buzzer e o led
	stop_led_rbg();
	para_buzzer();
	return;
}