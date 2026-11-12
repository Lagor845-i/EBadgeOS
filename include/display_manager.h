#pragma once

#include <Arduino.h>
#include <string.h>

#include "display_config.h"
#include "core.h"

class Display_Manager {
public:
    
    Display_Manager(Core* system_core);

    void begin();
    void forceLovyanGFXSymbols();

    //Display info
    int getDisplayWidth();
    int getDisplayHeight();

    //Display operations

    void fill(uint16_t color);
    void setDisplayBuffer(LGFX_Sprite* sprite);
    void updateDisplay();
    void sendNotification(std::string notification);
    bool displayingNotification();
    void displayNotification();
    void error(std::string error);
    bool setBackground(LGFX_Sprite sprite);

private:
    void printToLog(std::string text);
    void drawTextToDisplay(std::string text,int forground,int x,int y);
    void drawNotificationText();

    //Window width and height
    uint16_t _width;
    uint16_t _height;

    //Allows this to call functions from around the system if needed
    Core* _system_core;

    LGFX_Sprite* _display_buffer;

    //Notification display data
    bool _notification;
    std::string _notification_text;
    time_t _notification_timer_start = 0;
    LGFX_Sprite _notification_sprite;
    int _notification_time_limit;
};
