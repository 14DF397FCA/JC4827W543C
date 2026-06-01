//
// Created by Gennadii Ilyashenko on 28.03.2026.
//

#include <Arduino.h>
#include <lvgl.h>
#include "display.h"
#include "touch.h"
#include "callbacks.h"
#include "ui/ui.h"
#include "espnow.h"
#include "data.h"

#define BUFF_SIZE (480 * 40)

static lv_color_t *buf1 = nullptr;
static lv_color_t *buf2 = nullptr;
static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;

intercoolerTemp intercooler;
const bool verbose = false;

constexpr uint8_t updateInterval = 100;
// static uint64_t lastUpdate = 0;

void setup() {
    Serial.begin(115200);
    delay(500);

    display_init();
    touch_init();

    lv_init();

    buf1 = (lv_color_t *) heap_caps_malloc(BUFF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    buf2 = (lv_color_t *) heap_caps_malloc(BUFF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, BUFF_SIZE);

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 480;
    disp_drv.ver_res = 272;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touch_cb;
    lv_indev_drv_register(&indev_drv);

    ui_init();

    lv_obj_add_event_cb(ui_Slider1, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    Serial.println("UI ready");

    lv_timer_create(ui_timer_cb, updateInterval, NULL);

    SetupEspNow();
}

void loop() {
    lv_timer_handler();
    delay(5);
    if (verbose) {
        Serial.printf("Air In: %d\n", intercooler.airIn);
        Serial.printf("Air Out: %d\n", intercooler.airOut);
        Serial.printf("Coolant In: %d\n", intercooler.coolantIn);
        Serial.printf("Coolant Out: %d\n", intercooler.coolantOut);
    }
}
