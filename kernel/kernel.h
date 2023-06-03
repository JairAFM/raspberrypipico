#include "../threads/thread.c"
// Se definen encabezados de funciones
bool tick_handler(struct repeating_timer *t); /* Control tick for timer interrupt */
void t_scheduler(struct thread *t); /*thread scheduler*/