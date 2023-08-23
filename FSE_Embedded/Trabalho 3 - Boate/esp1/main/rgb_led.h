#ifndef RGB_LED_H
#define RGB_LED_H

// Struct
typedef struct 
{
    int channel;
    int gpio;
    int mode;
    int timer_index;
} ledc_info_t;

// Funções
void rgb_led_set_color (int red, int green, int blue);
void stop_led_rbg(void);

#endif