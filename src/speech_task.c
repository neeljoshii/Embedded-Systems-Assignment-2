#include "/home/neeljoshi/speaking_clock/include/FreeRTOSv202406.04-LTS/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/include/FreeRTOS.h"
#include "task.h"

void speech_task(void *p) {
    while (1) {
        // Do nothing for Step 1
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}