//
// Created by Gennadii Ilyashenko on 28.03.2026.
//

#pragma once

#include <lvgl.h>

lv_color_t getColorByTemperature(int8_t value);

void slider_event_cb(lv_event_t *e);

void ui_timer_cb(lv_timer_t *timer);

void updateBar(lv_obj_t *uiBar, lv_obj_t *uiLabel, const int8_t v);

void updateAirIn(int8_t value);

void updateAirOut(int8_t value);

void updateCoolantIn(int8_t value);

void updateCoolantOut(int8_t value);
