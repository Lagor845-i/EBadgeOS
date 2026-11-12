#pragma once

#include "core.h"

class Input_Manager {
    public:
        Input_Manager(Core* system_core);
        void sysGetInput();
        void begin();

    private:
        void readAccelerometer(float *buffer);
        Input stuff;
        Core* _system_core;
};