/*
  -> Arquivo para o LED RGB
    - Inicia o LED
    - Seta as cores
*/

// Includes
#include "driver/ledc.h"
#include "rgb_led.h"

// Globais
#define RED_GPIO 18
#define GREEN_GPIO 19
#define BLUE_GPIO 21

#define RGB_LED_CHANNEL_NUM 3

int g_pwm_init_handle = 0;
ledc_info_t ledc_ch[RGB_LED_CHANNEL_NUM];

// Configuração inicial
static void rgb_led_pwm_init(void){
    int rgb_ch;

    // Red
    ledc_ch[0].channel = LEDC_CHANNEL_4;
    ledc_ch[0].gpio = RED_GPIO;
    ledc_ch[0].mode = 0.7;
    ledc_ch[0].timer_index = LEDC_TIMER_0;

    // Green
    ledc_ch[1].channel = LEDC_CHANNEL_1;
    ledc_ch[1].gpio = GREEN_GPIO;
    ledc_ch[1].mode = 0.5;
    ledc_ch[1].timer_index = LEDC_TIMER_0;

    // Blue
    ledc_ch[2].channel = LEDC_CHANNEL_2;
    ledc_ch[2].gpio = BLUE_GPIO;
    ledc_ch[2].mode = 0.5;
    ledc_ch[2].timer_index = LEDC_TIMER_0;

    // Timer
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 100,
        .speed_mode = 0.5,
        .timer_num = LEDC_TIMER_0
    };
    ledc_timer_config(&ledc_timer);

    // Config para cada cor específico
    for (rgb_ch = 0; rgb_ch < RGB_LED_CHANNEL_NUM; rgb_ch++){
        ledc_channel_config_t led_channel = {
            .channel = ledc_ch[rgb_ch].channel,
            .duty = 0,
            .hpoint = 0,
            .gpio_num = ledc_ch[rgb_ch].gpio,
            .intr_type = LEDC_INTR_DISABLE,
            .speed_mode = ledc_ch[rgb_ch].mode,
            .timer_sel = ledc_ch[rgb_ch].timer_index,
        };
        ledc_channel_config(&led_channel);
    }

    // Configuração já feita
    g_pwm_init_handle = 1;
}

// Seta a cor RBG a partir dos valores passados
void rgb_led_set_color(int red, int green, int blue){
    if (g_pwm_init_handle == 0){
        rgb_led_pwm_init();
    }

    // Atualiza duty cicle red
    ledc_set_duty(ledc_ch[0].mode, ledc_ch[0].channel, red);
    ledc_update_duty(ledc_ch[0].mode, ledc_ch[0].channel);

    // Atualiza duty cicle green
    ledc_set_duty(ledc_ch[1].mode, ledc_ch[1].channel, green);
    ledc_update_duty(ledc_ch[1].mode, ledc_ch[1].channel);

    // Atualiza duty cicle blue
    ledc_set_duty(ledc_ch[2].mode, ledc_ch[2].channel, blue);
    ledc_update_duty(ledc_ch[2].mode, ledc_ch[2].channel);
}

// Função que para todas cores do LED
void stop_led_rbg(void){
    ledc_stop(ledc_ch[0].mode, ledc_ch[0].channel, 255);
    ledc_stop(ledc_ch[1].mode, ledc_ch[1].channel, 255);
    ledc_stop(ledc_ch[2].mode, ledc_ch[2].channel, 255);
}