//
// Created by Gennadii Ilyashenko on 15.01.2026.
//
#pragma once

#include <Arduino.h>

typedef struct IntercoolerTemp {
    int8_t airIn;
    int8_t airOut;
    int8_t coolantIn;
    int8_t coolantOut;
} IntercoolerTemp;

typedef struct LightSwitch {
    bool frontRight;
    bool frontLeft;
    bool headRight;
    bool headLeft;
    bool updated;
} LightSwitch;

extern IntercoolerTemp intercooler;
extern LightSwitch lightSwitch;
extern const bool verbose;

// extern int8_t oldAirIn;
// extern int8_t oldAirOut;
// extern int8_t oldCoolantIn;
// extern int8_t oldCoolantOut;

// extern uint updateDisplayInterval;
// extern uint clearDisplay;
