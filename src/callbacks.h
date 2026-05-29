//
// Created by Gennadii Ilyashenko on 28.03.2026.
//

#pragma once

#include <lvgl.h>

lv_color_t getColorByValue(int16_t value);

void slider_event_cb(lv_event_t *e);

void ui_timer_cb(lv_timer_t *timer);

void updateAirIn(int16_t value);

void updateAirOut(int16_t value);

void updateCoolantIn(int16_t value);

void updateCoolantOut(int16_t value);
