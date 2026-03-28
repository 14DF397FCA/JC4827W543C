#include "display.h"

#define GFX_BL 1

static Arduino_ESP32QSPI bus(45, 47, 21, 48, 40, 39);
Arduino_NV3041A gfx(&bus, GFX_NOT_DEFINED, 0, true);

void display_init() {
    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);
    gfx.begin();
    gfx.fillScreen(0x0000);
}

void disp_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;
    gfx.draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)color_p, w, h);
    lv_disp_flush_ready(drv);
}
