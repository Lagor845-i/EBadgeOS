#pragma once
#include <arduino.h>

#include "core.h"

class Audio_Manager {
    public:
        Audio_Manager(Core* system_core);
        void playTone(uint8_t frequency);

    private:
        Core* _system_core;
};