#include "kernel/kernel.h"
#include "threads/thread.c"

void tick_handler(struct repeating_timer *t)
{
    static uint32_t tick = 0;
    tick++;

    for (int i = 0; i < THREAD_CREATE; i++)
    {
        // salta el thread actual
        if (control_block[i].tid == current_thread->tid)
        {
            continue;
        }
        // verifica si es necesario reestablecer el tiempo restante del sub process
        if (tick % control_block[i].priority == 0)
        {
            control_block[i].remaining_time = 0;
        }
    }
}

void scheduler(struct thread *t)
{
    int next_thread = 0;
    int actual_priority = t->priority;
    int active_threads = 0;

    for (int i = 0; i < THREAD_CREATE; i++)
    {
        if (t->tid == control_block[i].tid)
        {
            continue;
        }
        if (control_block[i].status == THREAD_READY)
        {
            active_threads = 1;
            if (control_block[i].priority < actual_priority)
            {
                actual_priority = control_block[i].priority;
                next_thread = i;
            }
        }
    }
    if (active_threads == 0)
    {
        printf("Non-existent active thread.\n");
        sleep_ms(1000);
        exit(0);
    }

    control_block[next_thread].priority = actual_priority;
    control_block[next_thread].status = THREAD_RUNNING;
    control_block[t->tid-1].priority = control_block[t->tid-1].priority_original;
    control_block[t->tid-1].status = THREAD_BLOCKED;
    current_thread = &control_block[next_thread];
}

