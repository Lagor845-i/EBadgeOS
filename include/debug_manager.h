#include <Arduino.h>

#include "core.h"

#define DEBUG_ON true
#define DEBUG_OFF false

class Debug_Manager {
    public:
        Debug_Manager(Core* system_core);
        void begin();
        void stop();
        void set(bool debug_value);
        void systemLog(String msg);
        void applicationLog(String msg);
    
    private:
        bool _on = false;
        Core* _system_core;
};