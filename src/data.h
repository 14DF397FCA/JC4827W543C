//
// Created by Gennadii Ilyashenko on 15.01.2026.
//
#pragma once

#include <Arduino.h>
typedef struct intercoolerTemp {
    int16_t airIn;
    int16_t airOut;
    int16_t coolantIn;
    int16_t coolantOut;
} intercoolerTemp;

extern intercoolerTemp intercooler;
extern const bool verbose;

extern int16_t oldAirIn;
extern int16_t oldAirOut;
extern int16_t oldCoolantIn;
extern int16_t oldCoolantOut;

// extern uint updateDisplayInterval;
// extern uint clearDisplay;
