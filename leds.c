#include <stdio.h>
#include "pico/stdlib.h"
#include "semaforo.h"
#include "circular.h"
#include "porcolor.h"

#define MAX_LEDS 12

const uint leds[] = {4,3,2,16,17,18,26,27,28,13,14,15};

void mostrarLeds(const char patron[][MAX_LEDS], int pasos, int tiempo){
    for (int i = 0; i < pasos; i++){
        for (int l = 0; l < MAX_LEDS; l++){
            switch(patron[i][l]){
                case '0':
                    gpio_put(leds[l], 0);
                    break;
                case '1':
                    gpio_put(leds[l], 1);
                    break;
            }
        }
        sleep_ms(tiempo);
    }
}

int main()
{
    stdio_init_all();
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    for (int i = 0; i < MAX_LEDS; i++){
        gpio_init(leds[i]);
        gpio_set_dir(leds[i], GPIO_OUT);

    }
    gpio_put(LED_PIN, 1);
    sleep_ms(2000);
    gpio_put(LED_PIN, 0);
    sleep_ms(500);
    while (true) {
        for (int i = 0; i < 2; i++){
            mostrarLeds(semaforo, 34, 500);
        }
        for(int i = 0; i < 10; i++){
            mostrarLeds(porcolor,3, 100);
        }
        for(int i = 0; i < 10; i++){
            mostrarLeds(circular,12, 50);
        }
    }
    return 0;
}