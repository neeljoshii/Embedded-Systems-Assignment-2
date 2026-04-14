#include "/home/neeljoshi/speaking_clock/include/FreeRTOSv202406.04-LTS/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/include/FreeRTOS.h"
#include "task.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>

extern SemaphoreHandle_t time_request_sem;

void ntp_task(void *p) {
    while (1) {
        // Wait forever for the semaphore from the Key Task
        if (xSemaphoreTake(time_request_sem, portMAX_DELAY) == pdPASS) {
            printf("[NTP TASK] Semaphore received! Waking up...\n");
        }
    }
}