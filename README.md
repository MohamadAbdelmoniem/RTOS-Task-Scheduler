# Real-Time Operating System (RTOS) Task Scheduler

### Overview
The RTOS Task Scheduler is a simple yet versatile task scheduling system designed for embedded systems. It provides a framework for managing tasks with varying priorities and execution frequencies. This project aims to facilitate the organization and execution of tasks in a real-time environment, making it suitable for microcontroller-based applications.

### Features
- **Task Management:** Easily create, delete, suspend, and resume tasks.
- **Priority-Based Scheduling:** Assign priorities to tasks for precise control over execution order.
- **Periodic Execution:** Define the periodicity of tasks to meet specific timing requirements.
- **Simple and Lightweight:** Designed for embedded systems with minimal resource overhead.

### Getting Started
1. **Include Dependencies:** Ensure that the required standard types and bit manipulation libraries are included.
2. **Define Maximum Number of Tasks:** Set the `MAX_NUMBER_TASKS` macro to the desired maximum number of tasks your system will support.
3. **Create Tasks:** Use the `RTOS_u8CreateTask` function to define tasks with their respective handlers, priorities, periodicities, and initial delays.
4. **Scheduler Callback:** Implement a callback function, such as `scheduler`, which will be periodically invoked to manage task execution.
5. **Build and Deploy:** Compile the code and deploy it to your target embedded system.

### Functions
- `RTOS_u8CreateTask`: Create a new task with specified parameters.
- `scheduler`: The main scheduler function that manages task execution.
- `RTOS_DeleteTask`: Delete a task by priority.
- `RTOS_Suspend`: Suspend a task by priority.
- `RTOS_ResumeTask`: Resume a suspended task by priority.

### Error Handling
- Priority Error (Return Code 1): Occurs when trying to create a task with an invalid priority.
- Task Already Exists (Return Code 2): Indicates that a task with the same priority already exists.
- No Task Exists (Return Code 3): Returned when attempting to delete, suspend, or resume a non-existent task.

### Example Usage
```c
// Create tasks
RTOS_u8CreateTask(Task1_Handler, 5, 1, 0);  // Priority 1, periodicity 5, no initial delay
RTOS_u8CreateTask(Task2_Handler, 10, 2, 3); // Priority 2, periodicity 10, initial delay 3

// Implement the scheduler callback
void SysTick_Handler(void) {
    scheduler();
}

// Delete a task
RTOS_DeleteTask(1); // Delete the task with priority 1

// Suspend and resume tasks
RTOS_Suspend(2);   // Suspend the task with priority 2
RTOS_ResumeTask(2); // Resume the suspended task with priority 2
```
---
