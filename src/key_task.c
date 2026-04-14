// #include "/home/neeljoshi/speaking_clock/include/FreeRTOSv202406.04-LTS/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/include/FreeRTOS.h"
// #include "task.h"
// #include "semphr.h"
// #include <stdio.h>

// extern SemaphoreHandle_t time_request_sem;

// void key_task(void *p) {
//     while (1) {
//         // Blocks until a key is pressed in the QEMU console
//         char c = getchar(); 
        
//         // The assignment skeleton checks for 0x65 ('e'), but 't' is also standard
//         if (c == 't' || c == 'T' || c == 0x65) { 
//             printf("\n[KEY TASK] Valid key pressed. Signaling NTP Task...\n");
//             xSemaphoreGive(time_request_sem);
//         }
        
//         // Small delay to yield to the scheduler
//         vTaskDelay(pdMS_TO_TICKS(10));
//     }
// }

#include "/home/neeljoshi/speaking_clock/include/FreeRTOSv202406.04-LTS/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/include/FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>

extern SemaphoreHandle_t time_request_sem;

#undef getchar
int getchar(void) {
    volatile unsigned int *USART1_SR = (unsigned int *)0x40011000; 
    volatile unsigned int *USART1_DR = (unsigned int *)0x40011004; 
    volatile unsigned int *USART2_SR = (unsigned int *)0x40004400; 
    volatile unsigned int *USART2_DR = (unsigned int *)0x40004404; 

    while (1) {
        // Check if USART1 received a key (Bit 5 is RXNE)
        if ((*USART1_SR & 0x20) != 0) return *USART1_DR;
        
        // Check if USART2 received a key
        if ((*USART2_SR & 0x20) != 0) return *USART2_DR;
        
        // If neither has a key, sleep for 10 ticks so other tasks can run
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void key_task(void *p) {
    while (1) {
        char c = getchar(); 
        
        if (c == 't' || c == 'T' || c == 0x65) { 
            printf("\n[KEY TASK] Valid key pressed. Signaling NTP Task...\n");
            xSemaphoreGive(time_request_sem);
        }
    }
}