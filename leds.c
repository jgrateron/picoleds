#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "semaforo.h"
#include "circular.h"
#include "porcolor.h"

#define MAX_LEDS 12

const char encendidos[][12] = 
{
{'1','1','1','1','1','1','1','1','1','1','1','1'},
};

const char apagados[][12] = 
{
{'0','0','0','0','0','0','0','0','0','0','0','0'},
};


const uint leds[] = {4,3,2,16,17,18,26,27,28,13,14,15};
const uint LED_PIN = PICO_DEFAULT_LED_PIN;

uint patron_actual = 1;
uint velocidad = 250;

void mostrarLeds(uint patron_anterior, const char matriz[][MAX_LEDS], int pasos, int tiempo){
    for (int i = 0; i < pasos; i++){
        for (int l = 0; l < MAX_LEDS; l++){
            switch(matriz[i][l]){
                case '0':
                    gpio_put(leds[l], 0);
                    break;
                case '1':
                    gpio_put(leds[l], 1);
                    break;
            }
        }
        if (patron_anterior != patron_actual){
            return;
        }
        sleep_ms(tiempo);
    }
}

/*
*/
void core1_entry()
{
    gpio_put(LED_PIN, 1);
    sleep_ms(2000);
    gpio_put(LED_PIN, 0);
    sleep_ms(500);
    while (true) {
        switch(patron_actual){
            case 0:
                mostrarLeds(patron_actual, apagados, 1, velocidad);
                break;
            case 1:
                mostrarLeds(patron_actual, encendidos, 1, velocidad);
                break;
            case 2:
                mostrarLeds(patron_actual, semaforo, 34, velocidad);
                break;
            case 3:
                mostrarLeds(patron_actual, porcolor,3, velocidad);
                break;
            case 4:
                mostrarLeds(patron_actual, circular_a,12, velocidad);
                break;
            case 5:
                mostrarLeds(patron_actual, circular_b,12, velocidad);
                break;
        }
    }
}
/*
*/
int main()
{
    stdio_init_all();
    multicore_launch_core1(core1_entry);
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    for (int i = 0; i < MAX_LEDS; i++){
        gpio_init(leds[i]);
        gpio_set_dir(leds[i], GPIO_OUT);

    }
    while(true){
        char c = getchar();
        switch(c){
            case '0':
                patron_actual = 0;
                velocidad = 250;
                break;
            case '1':
                patron_actual = 1;
                velocidad = 250;
                break;
            case '2':
                patron_actual = 2;
                velocidad = 250;
                break;
            case '3':
                patron_actual = 3;
                velocidad = 100;
                break;
            case '4':
                patron_actual = 4;
                velocidad = 50;
                break;
            case '5':
                patron_actual = 5;
                velocidad = 50;
                break;
            case '+':
                velocidad += 5;
                break;
            case '-':
                velocidad -= 5;
                break;
            default:
                patron_actual = 0;
                velocidad = 50;
                break;
        }
    }

    return 0;
}