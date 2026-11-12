#pragma once

#include "config.h"
#include "api_data_types.h"
#include <string.h>
#include <Arduino.h>

//Application Manager Operations

#define BOOT_APP_FILE 0  

//Debug Operations

#define Print_System_Debug 0
#define Print_App_Debug 1
#define Toggle_Debug 2

//Display Operations

#define Reset_Display 1
#define Update_Display 2
#define Draw_Line 3
#define Draw_Pixel 4
#define Draw_Pixels 5
#define Draw_Circle 6
#define Draw_Rectangle 7
#define Draw_Arc 8
#define Draw_Ellipse 9
#define Draw_PNG 10
#define Draw_JPG 11
#define Draw_Gradient_Line 12

#define Draw_Float 20
#define Draw_String 21

#define Display_Notification 25

//Input Operations

#define Change_Input_Polling_Rate 0

//File System Operations

#define READ_FILE 0
#define WRITE_TO_FILE 1
#define APPEND_TO_FILE 2
#define GET_CARD_SIZE 3
#define RECEIVE_FILE_OUTGOING 4

struct queuePacket {
    QueueHandle_t sender;
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

void systemDebug(std::string text,QueueHandle_t debug_queue);