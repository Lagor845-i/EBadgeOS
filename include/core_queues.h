#pragma once

#include "config.h"
#include "api_data_types.h"
#include <string.h>
#include <Arduino.h>

//Debug Operations

#define Print_System_Debug 0
#define Print_App_Debug 1
#define Toggle_Debug 2

//Display Operations



//Input Operations

struct queuePacket {
    uint8_t operation;
    void* data;
};

struct systemQueues {
    QueueHandle_t application_manager = xQueueCreate(10,sizeof(queuePacket));
    QueueHandle_t audio_manager = xQueueCreate(10,sizeof(queuePacket));
    QueueHandle_t bluetooth_manager = xQueueCreate(10,sizeof(queuePacket));
    QueueHandle_t debug_manager = xQueueCreate(10,sizeof(queuePacket));
    QueueHandle_t display_manager = xQueueCreate(10,sizeof(queuePacket));
    QueueHandle_t file_system_manager = xQueueCreate(10,sizeof(queuePacket));
    QueueHandle_t input_manager = xQueueCreate(10,sizeof(queuePacket));
    QueueHandle_t led_manager = xQueueCreate(10,sizeof(queuePacket));
    QueueHandle_t stats_manager = xQueueCreate(10,sizeof(queuePacket));
    QueueHandle_t wifi_manager = xQueueCreate(10,sizeof(queuePacket));
};

void sendDebug(std::string text,QueueHandle_t debug_queue) {
    queuePacket* packet;
    std::string* temp = new std::string(text);
    packet->operation = Print_System_Debug;
    packet->data = temp;
    xQueueSend(debug_queue,packet,0);
}