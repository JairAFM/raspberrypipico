#include <stdint.h>

// Se define estructura del thread
struct semaphore 
{
    uint32_t prior; /* Current value */
};

struct semaphore led_sema; /* Instance for control access LED */

// Se definen encabezados de funciones
void sema_init(struct semaphore *sema); /* Inicialize the semaphore */
void sema_acquire(struct semaphore *sema); /* Aquire to semaphore */
void sema_release(struct semaphore *sema); /* Release to semaphore*/