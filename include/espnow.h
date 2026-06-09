//
// Created by Gennadii Ilyashenko on 27.03.2026.
//

#pragma once
#include <Arduino.h>
#include <esp_now.h>
#include "data.h"

void SetupEspNow();
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int data_len);
esp_err_t espSend(LightSwitch data);
