//
// Created by Gennadii Ilyashenko on 09.06.2026.
//

#pragma once

#include <lvgl.h>

void turnOnSync(lv_event_t *e, lv_obj_t *ui_sw);

void swStateToSerial(bool swState, const String swName);

void turnOnFrontRight(lv_event_t *e);

void turnOnFrontLeft(lv_event_t *e);

void turnOnHeadRight(lv_event_t *e);

void turnOnHeadLeft(lv_event_t *e);
