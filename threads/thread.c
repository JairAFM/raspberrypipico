#include "threads/thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomPriority(void) {
    srand((unsigned) time(0));
    return rand() % 6;
}

void thread_function(void) {

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
        control_block[i].time_asleep = 0;
        control_block[i].function = thread_function;
    }
}