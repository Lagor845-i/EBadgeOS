#pragma once
#include <arduino.h>

#include "core_queues.h"

class Audio_Manager {
    public:
        Audio_Manager(systemQueues* system_queues);
        void playTone(uint8_t frequency);

    private:
        systemQueues* _system_queues;
};