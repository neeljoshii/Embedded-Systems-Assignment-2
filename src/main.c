#include "/home/neeljoshi/speaking_clock/include/FreeRTOSv202406.04-LTS/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/include/FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>

SemaphoreHandle_t time_request_sem;

extern void key_task(void *p);
extern void ntp_task(void *p);
extern void speech_task(void *p);

// --- NEW: Explicitly power on the UART hardware ---
void hardware_init(void) {
    volatile unsigned int *USART1_CR1 = (unsigned int *)0x4001100C;
    volatile unsigned int *USART2_CR1 = (unsigned int *)0x4000440C;
    
    // 0x200C in binary is 0010 0000 0000 1100
    // This turns on Bit 13 (Enable), Bit 3 (Transmit), and Bit 2 (Receive)
    *USART1_CR1 = 0x200C; 
    *USART2_CR1 = 0x200C; 
}
// --------------------------------------------------

int _write(int file, char *ptr, int len) {
    volatile unsigned int *USART1_SR = (unsigned int *)0x40011000; 
    volatile unsigned int *USART1_DR = (unsigned int *)0x40011004; 
    for (int i = 0; i < len; i++) {
        while ((*USART1_SR & 0x80) == 0); 
        *USART1_DR = ptr[i]; 
    }
    return len;
}

int main(void) {
    // 1. Power on the hardware before anything else!
    hardware_init(); 

    printf("Hardware Initialized. Creating IPC...\n");

    time_request_sem = xSemaphoreCreateBinary();

    xTaskCreate(key_task, "KEY", 256, NULL, 1, NULL);
    xTaskCreate(ntp_task, "NTP", 512, NULL, 2, NULL); 
    xTaskCreate(speech_task, "SPEECH", 256, NULL, 1, NULL); 

    printf("Booting FreeRTOS...\n");
    vTaskStartScheduler();
    
    while (1) {}
    return 0;
}