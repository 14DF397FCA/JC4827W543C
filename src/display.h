#pragma once
#include <Arduino_GFX_Library.h>
#include <lvgl.h>

extern Arduino_NV3041A gfx;

void display_init();
void disp_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p);
