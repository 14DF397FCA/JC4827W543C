//
// Created by Gennadii Ilyashenko on 28.03.2026.
//

#pragma once

#include <lvgl.h>

lv_color_t getColorByValue(int32_t value);

void slider_event_cb(lv_event_t *e);