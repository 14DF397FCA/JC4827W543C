//
// Created by Gennadii Ilyashenko on 28.03.2026.
//

#include "callbacks.h"

static void slider_event_cb(lv_event_t *e) {
    lv_obj_t *slider = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(slider);
    int32_t rnd   = random(0, 11);

    char buf[32];
    snprintf(buf, sizeof(buf), "%d %d", value, rnd);
}

