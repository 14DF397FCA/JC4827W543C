//
// Created by Gennadii Ilyashenko on 27.03.2026.
//

#include <WiFi.h>
#include <esp_now.h>
#include "espnow.h"
#include "data.h"

uint8_t broadcastAddress[] = {0xA0, 0xB7, 0x65, 0x22, 0xF9, 0x2C};

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

    // Регистрируем callback
    esp_now_register_send_cb(OnDataSent);
    esp_now_register_recv_cb(OnDataRecv);

    // Добавляем broadcast peer
    esp_now_peer_info_t peerInfo;
    memset(&peerInfo, 0, sizeof(peerInfo));
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add broadcast peer");
        return;
    }

    Serial.println("Receiver initialized. Waiting for data...");
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Packet sent to: ");
    for (int i = 0; i < 6; i++) {
        Serial.print(mac_addr[i], HEX);
        if (i < 5)
            Serial.print(":");
    }

    Serial.printf(" at %d | Status: ", millis());
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success ✓" : "Fail ✗");
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

esp_err_t espSend(LightSwitch data) {
    Serial.println("Sending data");
    return esp_now_send(broadcastAddress,
                        (uint8_t *) &data,
                        sizeof(data));
}
