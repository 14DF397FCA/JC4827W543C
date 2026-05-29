//
// Created by Gennadii Ilyashenko on 28.03.2026.
//

#include <Arduino.h>
#include "callbacks.h"
#include <lvgl.h>
#include "ui/ui.h"
#include "data.h"

lv_color_t getColorByValue(int16_t value) {
    if (value < -20) {
        return lv_color_hex(0x281C59);
    } else if (value < 0) {
        return lv_color_hex(0x4E8D9C);
    } else if (value < 30) {
        return lv_color_hex(0x3ae700);
    } else if (value < 60) {
        return lv_color_hex(0xfaff08);
    } else if (value < 90) {
        return lv_color_hex(0xfe2c2f);
    } else if (value < 120) {
        return lv_color_hex(0x8a2be2);
    } else {
        return lv_color_hex(0x3A2759);
    }
}

void slider_event_cb(lv_event_t *e) {
    lv_obj_t *slider = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(slider);

    static lv_style_t style_ind;
    lv_style_init(&style_ind);

    lv_color_t color = getColorByValue(value);
    lv_obj_set_style_text_color(ui_lblAirIn, color, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui_lblAirOut, color, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui_lblCoolantIn, color, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui_lblCoolantOut, color, LV_PART_MAIN);

    char buf[32];
    snprintf(buf, sizeof(buf), "%d", value);
    lv_label_set_text(ui_lblAirIn, buf);
    lv_label_set_text(ui_lblAirOut, buf);
    lv_label_set_text(ui_lblCoolantIn, buf);
    lv_label_set_text(ui_lblCoolantOut, buf);

    lv_arc_set_value(ui_arcAirIn, value);
    lv_arc_set_value(ui_arcAirOut, value);
    lv_bar_set_value(ui_brCoolantIn, value, LV_ANIM_ON);
    lv_bar_set_value(ui_brCoolantOut, value, LV_ANIM_ON);
}

void ui_timer_cb(lv_timer_t *timer) {
    updateAirIn(intercooler.airIn);
    updateAirOut(intercooler.airOut);
    updateCoolantIn(intercooler.coolantIn);
    updateCoolantOut(intercooler.coolantOut);
}

void updateAirIn(int16_t value) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", value);
    lv_label_set_text(ui_lblAirIn, buf);
    lv_color_t color = getColorByValue(value);
    lv_obj_set_style_text_color(ui_lblAirIn, color, LV_PART_MAIN);

    lv_arc_set_value(ui_arcAirIn, value);
}

void updateAirOut(int16_t value) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", value);
    lv_label_set_text(ui_lblAirOut, buf);
    lv_color_t color = getColorByValue(value);
    lv_obj_set_style_text_color(ui_lblAirOut, color, LV_PART_MAIN);
    lv_arc_set_value(ui_arcAirOut, value);
}

void updateCoolantIn(int16_t value) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", value);
    lv_label_set_text(ui_lblCoolantIn, buf);
    lv_color_t color = getColorByValue(value);
    lv_obj_set_style_text_color(ui_lblCoolantIn, color, LV_PART_MAIN);
    lv_bar_set_value(ui_brCoolantIn, value, LV_ANIM_ON);
}

void updateCoolantOut(int16_t value) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", value);
    lv_label_set_text(ui_lblCoolantOut, buf);
    lv_color_t color = getColorByValue(value);
    lv_obj_set_style_text_color(ui_lblCoolantOut, color, LV_PART_MAIN);
    lv_bar_set_value(ui_brCoolantOut, value, LV_ANIM_ON);
}
