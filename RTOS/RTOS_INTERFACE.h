#ifndef RTOS_INTERFACE_H
#define RTOS_INTERFACE_H



// Public function prototypes
u8 RTOS_CreateTask(void (*handler)(void), u8 periodicity, u8 priority, u8 initialDelay);
void RTOS_Scheduler(void);
u8 RTOS_DeleteTask(u8 priority);
u8 RTOS_SuspendTask(u8 priority);
u8 RTOS_ResumeTask(u8 priority);


#endif
 
 
