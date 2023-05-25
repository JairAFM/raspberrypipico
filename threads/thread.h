#include <stdint.h>

// Se define cantidad de threads que se pueden crear
#define THREAD_CREATE 2

// Se define prioridad minima
#define PRI_MIN 0

// Se definen los estados del ciclo de un thread
enum thread_status
  {
    THREAD_RUNNING,     /* Running thread. */
    THREAD_READY,       /* Not running but ready to run. */
    THREAD_BLOCKED,     /* Waiting for an event to trigger. */
    THREAD_DYING        /* About to be destroyed. */
  };

// Se define la estructura del thread
struct thread
  {
    uint32_t tid;                       /* Thread identifier. */
    enum thread_status status;          /* Thread state. */
    const char *name;                   /* Name (for debugging purposes). */
    int priority;                       /* Priority. */
    uint64_t time_asleep;               /* Time a Thread remains asleep */
    void (*function)(void);             /* Function to call */
  };

//Se define control block
struct thread control_block[THREAD_CREATE];

// Se define init current thread
volatile uint8_t current_thread;

// Se definen encabezados de funciones
int randomPriority(void);   /* Returns a random value from 0 to 5 that will be used to determine the initial priority of the thread. */
void thread_function(void); /* Function to handle the thread */
void thread_init (void);    /* Initializes threads */