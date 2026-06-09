//
// Created by Gennadii Ilyashenko on 09.06.2026.
//

#include <Arduino.h>
#include "lights.h"
#include <lvgl.h>
#include "ui/ui.h"
#include "data.h"

void turnOnSync(lv_event_t *e, lv_obj_t *ui_sw) {
    if (isSwitchChecked(ui_swSyncOn)) {
        lv_obj_t *sw = lv_event_get_target(e);
        if (isSwitchChecked(sw)) {
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
    // bool state = isSwitchChecked(ui_swFrontRight);
    // swStateToSerial(state, "Front Right");
    // lightSwitch.frontRight = state;
    // lightSwitch.updated = true;
}

void turnOnFrontLeft(lv_event_t *e) {
    turnOnSync(e, ui_swFrontRight);
    // bool state = isSwitchChecked(ui_swFrontRight);
    // swStateToSerial(state, "Front Left");
    // lightSwitch.frontLeft = state;
    // lightSwitch.updated = true;
}

void turnOnHeadRight(lv_event_t *e) {
    turnOnSync(e, ui_swHeadLeft);
    // bool state = isSwitchChecked(ui_swHeadRight);
    // swStateToSerial(state, "Head Right");
    // lightSwitch.headRight = state;
    // lightSwitch.updated = true;
}

void turnOnHeadLeft(lv_event_t *e) {
    turnOnSync(e, ui_swHeadRight);
    // bool state = isSwitchChecked(ui_swHeadLeft);
    // swStateToSerial(state, "Head Left");
    // lightSwitch.headLeft = state;
    // lightSwitch.updated = true;
}

bool isSwitchChecked(const lv_obj_t * obj) {
    return lv_obj_has_state(obj, LV_STATE_CHECKED);
}

bool isSwitchUpdated(const lv_obj_t * obj, const bool curState) {
    if (curState != isSwitchChecked(obj)) {
        return true;
    }
    return false;
}

LightSwitch getLightSwitch() {
    if (isSwitchUpdated(ui_swFrontLeft, lightSwitch.frontLeft)) {
        lightSwitch.frontLeft = isSwitchChecked(ui_swFrontLeft);
        lightSwitch.updated = true;
    }
    if (isSwitchUpdated(ui_swFrontRight, lightSwitch.frontRight)) {
        lightSwitch.frontRight = isSwitchChecked(ui_swFrontRight);
        lightSwitch.updated = true;
    }
    if (isSwitchUpdated(ui_swHeadLeft, lightSwitch.headLeft)) {
        lightSwitch.headLeft = isSwitchChecked(ui_swHeadLeft);
        lightSwitch.updated = true;
    }
    if (isSwitchUpdated(ui_swHeadRight, lightSwitch.headRight)) {
        lightSwitch.headRight = isSwitchChecked(ui_swHeadRight);
        lightSwitch.updated = true;
    }
    return lightSwitch;
}
