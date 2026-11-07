#include <Arduino.h>

#include "core_queues.h"

#define DEBUG_ON true
#define DEBUG_OFF false

class Debug_Manager {
    public:
        Debug_Manager(systemQueues* system_queues);
        void begin();
        void stop();
        void set(bool debug_value);
        void systemLog(String msg);
        void applicationLog(String msg);
    
    private:
        bool _on = false;
        systemQueues* _system_queues;
};