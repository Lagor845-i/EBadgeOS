#pragma once

#include "core_queues.h"

class Input_Manager {
    public:
        Input_Manager(systemQueues* system_queues);
        Input sysGetInput();
        void begin();

    private:
        Input stuff;
        systemQueues* _system_queues;
};