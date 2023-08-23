#ifndef ENCODER_H
#define ENCODER_H

#define PIN_DT GPIO_NUM_19
#define PIN_CLK GPIO_NUM_18
#define PIN_SW GPIO_NUM_21
#define NUM_MUSICAS 4

// Funções

void IRAM_ATTR encoder_isr_handler(void *arg);
void IRAM_ATTR button_isr_handler(void *arg);
void encoder_task(void *arg);
void button_task(void *arg);


#endif