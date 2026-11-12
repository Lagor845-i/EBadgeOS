#include <Arduino.h>
#include <string.h>

#include "core.h"

class Stats_Manager {
    public:
        Stats_Manager(Core* system_core);
        void begin();
        void reportStats();
        void displayStats();

    private:
        Core* _system_core;
};