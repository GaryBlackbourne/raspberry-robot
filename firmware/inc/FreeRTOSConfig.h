// FreeRTOS config file

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* Cortex-M specific definitions. */
// this part is from demo STM32F407ZG-SK
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4        /* 16 priority levels */
#endif

extern void GPIO_on();

/* Here is a good place to include header files that are required across
your application. */

#define configUSE_PREEMPTION                    1 // preemtive scheduler
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0 // use default task selection
#define configUSE_TICKLESS_IDLE                 0 // dont use low power tickless mode
#define configCPU_CLOCK_HZ                      8000000 // 8MHz HSI clock source
#define configSYSTICK_CLOCK_HZ                  1000000 // 8MHz HSI clock source / 8 = 1000000
#define configTICK_RATE_HZ                      ( (TickType_t) 1000 ) // 1ms tick
#define configMAX_PRIORITIES                    10 // maximum priorities a task can have
#define configMINIMAL_STACK_SIZE                128 // minimal stack size
#define configMAX_TASK_NAME_LEN                 32 // maximum length of characters
#define configUSE_16_BIT_TICKS                  0 // use 32 bit long tick type
#define configIDLE_SHOULD_YIELD                 1 // Idle task yield (not used now)
#define configUSE_TASK_NOTIFICATIONS            1 // use notifications
#define configTASK_NOTIFICATION_ARRAY_ENTRIES   1 // use old notification settings (default was 3)
#define configUSE_MUTEXES                       1 // use mutexes
#define configUSE_RECURSIVE_MUTEXES             0 // dont use recursive mutexes
#define configUSE_COUNTING_SEMAPHORES           1 // use counting semaphores
#define configUSE_ALTERNATIVE_API               0 /* Deprecated! */
#define configQUEUE_REGISTRY_SIZE               10
#define configUSE_QUEUE_SETS                    0 // disable queue sets
#define configUSE_TIME_SLICING                  1 // use timeslicing scheduler
#define configUSE_NEWLIB_REENTRANT              0 // newlib?
#define configENABLE_BACKWARD_COMPATIBILITY     0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 5
#define configSTACK_DEPTH_TYPE                  uint16_t
#define configMESSAGE_BUFFER_LENGTH_TYPE        size_t

/* Memory allocation related definitions. */
#define configSUPPORT_STATIC_ALLOCATION             0
#define configSUPPORT_DYNAMIC_ALLOCATION            1
#define configTOTAL_HEAP_SIZE                       ( (size_t) (15 * 1024) ) // 20 KB SRAM in stm32f103c8 -> 15 KB heap usage. FreeRTOS TASKS ARE LOCATED IN HEAP, only global stuff doesn't
#define configAPPLICATION_ALLOCATED_HEAP            0 // linker allocates heap
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP   0 // dont want to mess with stack allocation

/* Hook function related definitions. */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configCHECK_FOR_STACK_OVERFLOW          0
#define configUSE_MALLOC_FAILED_HOOK            0
#define configUSE_DAEMON_TASK_STARTUP_HOOK      0

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                0
#define configUSE_STATS_FORMATTING_FUNCTIONS    0

/* Co-routine related definitions. */
#define configUSE_CO_ROUTINES                   0
#define configMAX_CO_ROUTINE_PRIORITIES         2

/* Software timer related definitions. */
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               3
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            configMINIMAL_STACK_SIZE

/* Interrupt nesting behaviour configuration. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY		0xf
#define configKERNEL_INTERRUPT_PRIORITY         ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )// from demo project 
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) ) // (5 << 4) = 0x50 = 80
// from demo project
#define configMAX_API_CALL_INTERRUPT_PRIORITY   configMAX_SYSCALL_INTERRUPT_PRIORITY // these are equivalent, src: freeRTOS documentation

/* Define to trap errors during development. from demo project */
#define configASSERT( x ) if( ( x ) == pdFALSE ) { taskDISABLE_INTERRUPTS(); for( ;; ); /*for( ;; ){GPIO_on();}*/ }

/* FreeRTOS MPU specific definitions. */
#define configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS 0
#define configTOTAL_MPU_REGIONS                                8 /* Default value. */
#define configTEX_S_C_B_FLASH                                  0x07UL /* Default value. */
#define configTEX_S_C_B_SRAM                                   0x07UL /* Default value. */
#define configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY            1
#define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS             1

/* Optional functions - most linkers will remove unused functions anyway. */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_xResumeFromISR                  1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     0
#define INCLUDE_uxTaskGetStackHighWaterMark2    0
#define INCLUDE_xTaskGetIdleTaskHandle          0
#define INCLUDE_eTaskGetState                   0
#define INCLUDE_xEventGroupSetBitFromISR        1
#define INCLUDE_xTimerPendFunctionCall          0
#define INCLUDE_xTaskAbortDelay                 0
#define INCLUDE_xTaskGetHandle                  1
#define INCLUDE_xTaskResumeFromISR              1

/* A header file that defines trace macro can be included here. */

// interrupt routine mapping (from:https://www.freertos.org/FAQHelp.html)
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
