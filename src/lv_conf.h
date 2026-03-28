#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

#define LV_COLOR_DEPTH 16
#define LV_COLOR_16_SWAP 0

#define LV_HOR_RES_MAX 480
#define LV_VER_RES_MAX 272

// Память под буфер (используем PSRAM)
#define LV_MEM_CUSTOM 0
#define LV_MEM_SIZE (64 * 1024U)

// Включить PSRAM для буферов
#define LV_ATTRIBUTE_MEM_ALIGN_SIZE 16
#define LV_ATTRIBUTE_FAST_MEM IRAM_ATTR

// Шрифты
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_20 0
#define LV_FONT_DEFAULT &lv_font_montserrat_14

// Tick
#define LV_TICK_CUSTOM 1
#define LV_TICK_CUSTOM_INCLUDE "Arduino.h"
#define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())

// Логирование
#define LV_USE_LOG 1
#define LV_LOG_LEVEL LV_LOG_LEVEL_WARN

// Виджеты
#define LV_USE_BTN    1
#define LV_USE_LABEL  1
#define LV_USE_SLIDER 1
#define LV_USE_BAR    1
#define LV_USE_ARC    1
#define LV_USE_SWITCH 1

#endif
