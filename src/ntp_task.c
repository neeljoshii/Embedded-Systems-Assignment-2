#include "/home/neeljoshi/speaking_clock/include/FreeRTOSv202406.04-LTS/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/include/FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "time_msg.h"
#include <stdio.h>

extern SemaphoreHandle_t time_request_sem;
extern QueueHandle_t time_queue;

void ntp_task(void *p) {
    time_msg dummy_time;

    while (1) {
        // Wait forever for the semaphore from the Key Task [cite: 213]
        if (xSemaphoreTake(time_request_sem, portMAX_DELAY) == pdPASS) {
            printf("[NTP TASK] Semaphore received! Generating dummy time...\n");

            // Populate the struct with fake data
            dummy_time.hour = 14;
            dummy_time.minute = 32;
            dummy_time.second = 5;

            // Send the data to the Speech Task via the Queue [cite: 216]
            xQueueSend(time_queue, &dummy_time, portMAX_DELAY);
            printf("[NTP TASK] Dummy time sent to Queue.\n");
        }
    }
}