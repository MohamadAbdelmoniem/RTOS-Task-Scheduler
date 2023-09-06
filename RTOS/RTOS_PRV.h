#ifndef RTOS_PRV_H
#define RTOS_PRV_H

#include "../LIB/STD_Types.h"



// Enumeration for task states
typedef enum {
    Running,
    Suspended,
    // Add more states as needed
} Tstate;

// Structure to represent a task
typedef struct {
    void (*TaskHandler)(void); // Pointer to the task's function
    u8 Periodicity;            // Task's periodicity
    Tstate Tstate;     // Task state (Running, Suspended, etc.)
} Task;

#endif
