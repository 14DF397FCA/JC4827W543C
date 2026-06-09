//
// Created by Gennadii Ilyashenko on 28.03.2026.
//

#include <Arduino.h>
#include "callbacks.h"
#include <lvgl.h>
#include "ui/ui.h"
#include "data.h"

lv_color_t getColorByTemperature(int8_t value) {
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

void ui_timer_cb(lv_timer_t *timer) {
    updateAirIn(intercooler.airIn);
    updateAirOut(intercooler.airOut);
    updateCoolantIn(intercooler.coolantIn);
    updateCoolantOut(intercooler.coolantOut);
}

void updateBar(lv_obj_t *uiBar, lv_obj_t *uiLabel, const int8_t v) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", v);
    lv_label_set_text(uiLabel, buf);
    lv_color_t color = getColorByTemperature(v);
    lv_obj_set_style_text_color(uiLabel, color, LV_PART_MAIN);

    lv_bar_set_value(uiBar, v, LV_ANIM_ON);
}

void updateAirIn(int8_t value) {
    updateBar(ui_brAirIn, ui_lblAirIn, value);
}

void updateAirOut(int8_t value) {
    updateBar(ui_brAirOut, ui_lblAirOut, value);
}

void updateCoolantIn(int8_t value) {
    updateBar(ui_brCoolantIn, ui_lblCoolantIn, value);
}

void updateCoolantOut(int8_t value) {
    updateBar(ui_brCoolantOut, ui_lblCoolantOut, value);
}

void turnOnSync(lv_event_t *e, lv_obj_t *ui_sw) {
    if (lv_obj_has_state(ui_swSyncOn, LV_STATE_CHECKED)) {
        lv_obj_t *sw = lv_event_get_target(e);
        if (lv_obj_has_state(sw, LV_STATE_CHECKED)) {
            lv_obj_add_state(ui_sw, LV_STATE_CHECKED);
        } else {
            lv_obj_clear_state(ui_sw, LV_STATE_CHECKED);
        }
    }
}

void swStateToSerial(bool swState, const String swName) {
    if (verbose) {
        if (swState) {
            Serial.printf("%s ON\n", swName.c_str());
        } else {
            Serial.printf("%s OFF\n", swName.c_str());
        }
    }
}

void turnOnFrontRight(lv_event_t *e) {
    turnOnSync(e, ui_swFrontLeft);
    bool state = lv_obj_has_state(ui_swFrontRight, LV_STATE_CHECKED);
    swStateToSerial(state, "Front Right");
    lightSwitch.frontRight = state;
    lightSwitch.updated = true;
}

void turnOnFrontLeft(lv_event_t *e) {
    turnOnSync(e, ui_swFrontRight);
    bool state = lv_obj_has_state(ui_swFrontRight, LV_STATE_CHECKED);
    swStateToSerial(state, "Front Left");
    lightSwitch.frontLeft = state;
    lightSwitch.updated = true;
}

void turnOnHeadRight(lv_event_t *e) {
    turnOnSync(e, ui_swHeadLeft);
    bool state = lv_obj_has_state(ui_swHeadRight, LV_STATE_CHECKED);
    swStateToSerial(state, "Head Right");
    lightSwitch.headRight = state;
    lightSwitch.updated = true;
}

void turnOnHeadLeft(lv_event_t *e) {
    turnOnSync(e, ui_swHeadRight);
    bool state = lv_obj_has_state(ui_swHeadLeft, LV_STATE_CHECKED);
    swStateToSerial(state, "Head Left");
    lightSwitch.headLeft = state;
    lightSwitch.updated = true;
}
