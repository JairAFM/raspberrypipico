#include "thread.h"

// se define pin del led
#define LED_PIN PICO_DEFAULT_LED_PIN

int randomPriority(void) {
    srand((unsigned) time(0));
    return rand() % 6;
}

void thread_function(struct thread *t) {
    while(1) {
        if (t->status == THREAD_DYING) // verifica si el thread esta en estatus THREAD_DYING
        {
            printf("Thread dying, ID: %d .\n", t->tid);
            sleep_ms(1000);
            continue;
        }
        if (t->status == THREAD_BLOCKED)// verifica si el thread esta en estatus THREAD_BLOCKED
        {
            printf("Thread blocked, ID: %d .\n", t->tid);
            sleep_ms(1000);
        }
        if (t->status == THREAD_READY)// verifica si el thread esta en estatus THREAD_BLOCKED
        {
            printf("Thread ready, ID: %d .\n", t->tid);
            sleep_ms(1000);
        }
        if (t->status == THREAD_RUNNING)// verifica si el thread esta en estatus THREAD_RUNNING
        {
            //Realiza el acquire del semaforo
            sema_acquire(&led_sema);
            printf("Thread acquired the semaphore, ID %d .\n", t->tid);

            //Se muestra el estado del thread
            if (t->status == THREAD_DYING)
            {
                printf("State dying.\n");
            }
            if (t->status == THREAD_BLOCKED)
            {
                printf("State blocked.\n");
            }
            if (t->status == THREAD_RUNNING)
            {
                printf("State running.\n");
            }

            // Toggle the LED
            gpio_put(LED_PIN, 1);
            sleep_ms(300);
            gpio_put(LED_PIN, 0);
            sleep_ms(300);

            // Realiza el release del semaforo
            sema_release(&led_sema);
            printf("Thread released the semaphore, ID %d .\n", t->tid);

            //Se muestra el estado del thread
            if (t->status == THREAD_DYING)
            {
                printf("State dying.\n");
            }
            if (t->status == THREAD_BLOCKED)
            {
                printf("State blocked.\n");
            }
            if (t->status == THREAD_RUNNING)
            {
                printf("State running.\n");
            }
        }
        yield();
    }
}

void sema_acquire(struct semaphore *sema)
{
    // Verifica que el semaforo este disponible
    while (sema->prior == 0)
    {
        yield(); // Release CPU for the other threads
    }
    sema->prior = sema->prior - 1;
}

void yield(void)
{
    int next_thread = 0;
    for (int i = 0; i < THREAD_CREATE; i++)
    {
        if (current_thread->tid != control_block[i].tid)
        {
            next_thread = i;
        }

    }
    if (current_thread->status = THREAD_BLOCKED)
    {
        control_block[current_thread->tid-1].status = THREAD_DYING;
    }
    if (current_thread->status = THREAD_RUNNING)
    {
        control_block[current_thread->tid-1].status = THREAD_BLOCKED;
    }
    control_block[next_thread].status = THREAD_RUNNING;
    current_thread = &control_block[next_thread];
}

void thread_init(void)
{

    for (uint8_t i = 0; i < THREAD_CREATE; i++)
    {
        int priority = randomPriority();
        control_block[i].tid = i + 1;
        control_block[i].status = THREAD_RUNNING; 
        control_block[i].name = "Welt" + i;
        control_block[i].priority = priority;
        control_block[i].priority_original = priority;
        control_block[i].remaining_time = 0;
    }
}