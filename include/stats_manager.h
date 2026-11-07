#include <Arduino.h>

#include "core_queues.h"

class Stats_Manager {
    public:
        Stats_Manager(systemQueues* system_queues);
        void reportStats();
        void displayStats();

    private:
        systemQueues* _system_queues;
};