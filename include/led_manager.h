#pragma once
#include <Adafruit_NeoPixel.h>

#include "core.h"

#define LED_PIN 7
#define LED_COUNT 23

extern Adafruit_NeoPixel led_strip; 

class Led_Manager {
    public:
        Led_Manager(Core* system_core);
        void begin();
        void setLeds(uint8_t colors[LED_COUNT][3]);
        void clearLeds();

    private:
        Core* _system_core;
};