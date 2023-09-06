#include "../LIB/STD_Types.h"
#include "../LIB/BIT_Math.h"
#include "../MSTK/MSYSTICK_Interface.h"
#include "RTOS_INTERFACE.h"
#include "RTOS_CFG.h"
#include "RTOS_PRV.h"

// Arrays to store task information and track task timing
Task RTOS_SystemTasks[MAX_NUMBER_TASKS] = {0};
u8 RTOS_Timing[MAX_NUMBER_TASKS];

// Placeholder for an empty task
Task RTOS_Empty = {0};

/**
 * @brief Create a new task
 * @param handler Pointer to the task's function
 * @param copy_u8periodicity Task's periodicity
 * @param Copy_u8priority Task's priority
 * @param fdelay Initial delay before task starts
 * @return 0 on success, 1 for priority error, 2 for task already exists
 */
u8 RTOS_u8CreateTask(void (*handler)(void), u8 copy_u8periodicity, u8 Copy_u8priority, u8 fdelay) {
    u8 Local_ErrorState = 0;

    if (Copy_u8priority < MAX_NUMBER_TASKS) {
        if (RTOS_SystemTasks[Copy_u8priority].TaskHandler == 0) {
            // Check if the task doesn't already exist
            RTOS_SystemTasks[Copy_u8priority].TaskHandler = handler;
            RTOS_SystemTasks[Copy_u8priority].Periodicity = copy_u8periodicity;
            RTOS_Timing[Copy_u8priority] = fdelay;
            RTOS_SystemTasks[Copy_u8priority].Tstate = Running;
        } else {
            Local_ErrorState = 2;  // Task already exists
        }
    } else {
        Local_ErrorState = 1;  // Invalid priority
    }

    return Local_ErrorState;
}

/**
 * @brief Scheduler that manages task execution
 */
void RTOS_Scheduler(void) {
    u8 Local_Counter = 0;

    for (Local_Counter = 0; Local_Counter < MAX_NUMBER_TASKS; Local_Counter++) {
        if (RTOS_SystemTasks[Local_Counter].TaskHandler != 0) {
            // Check if the task exists
            if (RTOS_SystemTasks[Local_Counter].Tstate == Running) {
                // Check if the task is running
                if (RTOS_Timing[Local_Counter] == 0) {
                    // Execute the task if timing is reached
                    RTOS_SystemTasks[Local_Counter].TaskHandler();
                    RTOS_Timing[Local_Counter] = RTOS_SystemTasks[Local_Counter].Periodicity;
                } else {
                    RTOS_Timing[Local_Counter]--;  // Decrement timing counter
                }
            }
        }
    }
}

/**
 * @brief Delete a task
 * @param Priority Priority of the task to delete
 * @return 0 on success, 1 if no task exists
 */
u8 RTOS_DeleteTask(u8 Priority) {
    u8 Local_ErrorState = 0;

    if (RTOS_SystemTasks[Priority].TaskHandler != 0) {
        // Check if the task exists
        RTOS_SystemTasks[Priority].TaskHandler = 0;
        // Delete the task by nullifying its handler
        RTOS_SystemTasks[Priority].Periodicity = 0;
        RTOS_Timing[Priority] = 0;
    } else {
        Local_ErrorState = 1;  // Task does not exist
    }

    return Local_ErrorState;
}

u8 RTOS_Suspend(u8 Priority) {
    u8 Local_ErrorState = 0;

    if (RTOS_SystemTasks[Priority].TaskHandler != 0) {
        // Check if the task exists
        RTOS_SystemTasks[Priority].Tstate = Suspended;
        // Set task state to Suspended
    } else {
        Local_ErrorState = 1;  // Task does not exist
    }

    return Local_ErrorState;
}

u8 RTOS_ResumeTask(u8 Priority) {
    u8 Local_ErrorState = 0;

    if (RTOS_SystemTasks[Priority].TaskHandler != 0) {
        // Check if the task exists
        RTOS_SystemTasks[Priority].Tstate = Running;
        // Set task state to Running
    } else {
        Local_ErrorState = 1;  // Task does not exist
    }

    return Local_ErrorState;
}
