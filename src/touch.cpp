#include "touch.h"
#include <Wire.h>

#define TOUCH_SDA  8
#define TOUCH_SCL  4
#define TOUCH_RST  38
#define GT911_ADDR 0x5D

void touch_init() {
    Wire.begin(TOUCH_SDA, TOUCH_SCL);
    pinMode(TOUCH_RST, OUTPUT);
    digitalWrite(TOUCH_RST, LOW);  delay(10);
    digitalWrite(TOUCH_RST, HIGH); delay(100);
}

static bool gt911_read(uint16_t *x, uint16_t *y) {
    Wire.beginTransmission(GT911_ADDR);
    Wire.write(0x81);
    Wire.write(0x4E);
    if (Wire.endTransmission(false) != 0) return false;

    Wire.requestFrom(GT911_ADDR, (uint8_t)7);
    if (Wire.available() < 7) return false;

    uint8_t status = Wire.read();
    if (!(status & 0x80) || (status & 0x0F) == 0) {
        Wire.beginTransmission(GT911_ADDR);
        Wire.write(0x81); Wire.write(0x4E); Wire.write(0x00);
        Wire.endTransmission();
        return false;
    }

    Wire.read();
    uint8_t x_low  = Wire.read();
    uint8_t x_high = Wire.read();
    uint8_t y_low  = Wire.read();
    uint8_t y_high = Wire.read();
    Wire.read();

    *x = (uint16_t)(x_high << 8) | x_low;
    *y = (uint16_t)(y_high << 8) | y_low;

    Wire.beginTransmission(GT911_ADDR);
    Wire.write(0x81); Wire.write(0x4E); Wire.write(0x00);
    Wire.endTransmission();

    return true;
}

void touch_cb(lv_indev_drv_t *drv, lv_indev_data_t *data) {
    uint16_t x, y;
    if (gt911_read(&x, &y)) {
        data->state   = LV_INDEV_STATE_PRESSED;
        data->point.x = x;
        data->point.y = y;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}
