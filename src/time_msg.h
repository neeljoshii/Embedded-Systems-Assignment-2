#ifndef TIME_MSG_H
#define TIME_MSG_H

#include <stdint.h>

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} time_msg;

#endif