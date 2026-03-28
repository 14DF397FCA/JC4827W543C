//
// Created by Gennadii Ilyashenko on 27.03.2026.
//

#include <WiFi.h>
#include <esp_now.h>
#include "espnow.h"
#include "data.h"

void SetupEspNow() {
    // Устанавливаем режим Wi-Fi
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    //    Ждём поднятия WiFi
    uint32_t timeout = millis();
    while (WiFi.macAddress() == "00:00:00:00:00:00") {
        if (millis() - timeout > 3000) {
            Serial.println("WiFi init timeout!");
            break;
        }
        delay(10);
    }
    // Печатаем свой MAC-адрес
    Serial.print("Receiver MAC: ");
    Serial.println(WiFi.macAddress());

    // Инициализируем ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        delay(3000);
        ESP.restart();
    }

    // Регистрируем callback приема
    esp_now_register_recv_cb(OnDataRecv);

    Serial.println("Receiver initialized. Waiting for data...");
}

void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int data_len) {
    const uint8_t *mac_addr = recv_info->src_addr;

    memcpy(&intercooler, data, sizeof(intercooler));

    if (verbose) {
        Serial.printf("Received %d bytes from MAC: ", data_len);
        for (int i = 0; i < 6; i++) {
            Serial.print(mac_addr[i], HEX);
            if (i < 5)
                Serial.print(":");
        }
        Serial.println("");
    }
}
