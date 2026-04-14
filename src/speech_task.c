#include "/home/neeljoshi/speaking_clock/include/FreeRTOSv202406.04-LTS/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/include/FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "time_msg.h"
#include <stdio.h>

extern QueueHandle_t time_queue;

// A helper function to print the exact required tokens
void speak_time(uint8_t hour, uint8_t minute, uint8_t second) {
    printf("TOKEN THE\n");
    printf("TOKEN TIME\n");
    printf("TOKEN IS\n");
    printf("TOKEN %02d\n", hour);
    printf("TOKEN %02d\n", minute);
    printf("TOKEN %02d\n", second);
    printf("END\n");
}

void speech_task(void *p) { 
    time_msg msg; 
    
    while(1) {
        // Block until time data arrives from the NTP Task
        if (xQueueReceive(time_queue, &msg, portMAX_DELAY) == pdPASS) {
            // Call the function to emit the tokens over UART
            speak_time(msg.hour, msg.minute, msg.second); 
        }
    } 
}