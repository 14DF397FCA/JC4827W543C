//
// Created by Gennadii Ilyashenko on 09.06.2026.
//

#include <Arduino.h>
#include "lights.h"
#include <lvgl.h>
#include "ui/ui.h"
#include "data.h"

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
