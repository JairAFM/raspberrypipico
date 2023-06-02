#include "kernel/kernel.c"


//Se define el pin del led
#define LED_PIN PICO_DEFAULT_LED_PIN



int main()
{
    tdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    thread_init();
    sema_init(&led_sema);
    struct repeating_timer kernel_timer;
    add_repeating_timer_us(1000, tick_handler, NULL, &kernel_timer);
    current_thread = &control_block[0];
    while (1)
    {
        thread_function(current_thread);
        // Perform thread scheduling
        scheduler(current_thread);
        // Update execution time
        execution_time++;   

        // Check if the execution time has reached a threshold
        if (execution_time >= 1000)
        {
            printf("Execution time limit reached. Exiting.\n");
            sleep_ms(1000);
            exit(0);
        }
    }

    return 0;
}