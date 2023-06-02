#include "semaphore/semaphore.h"

void sema_init(struct semaphore *sema)
{
    sema->prior = 1;
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

void sema_release(struct semaphore *sema)
{
    // Verifica overflow
    if (sema->prior < UINT32_MAX) 
    {
        sema->prior = sema->prior + 1;
    }
}
