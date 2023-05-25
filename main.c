#include "pico/stdlib.h"


//Se define el pin del led
#define LED_PIN PICO_DEFAULT_LED_PIN

int main()
{
    // configurar el pin
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    // bucle principal
    while(true)
    {
        // encender led
        gpio_put(LED_PIN, 1);
        sleep_ms(50);
        // apagar led
        gpio_put(LED_PIN, 0);
        sleep_ms(1500);
    }
}