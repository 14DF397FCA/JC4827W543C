//
// Created by Gennadii Ilyashenko on 27.03.2026.
//

#pragma once
#include <Arduino.h>
#include <esp_now.h>

void SetupEspNow();
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int data_len);
