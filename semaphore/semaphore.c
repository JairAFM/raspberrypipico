#include "semaphore.h"

void sema_init(struct semaphore *sema)
{
    sema->prior = 1;
}

void sema_release(struct semaphore *sema)
{
    // Verifica overflow
    if (sema->prior < UINT32_MAX) 
    {
        sema->prior = sema->prior + 1;
    }
}
