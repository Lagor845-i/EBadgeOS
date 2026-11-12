#include "debug_manager.h"

Debug_Manager::Debug_Manager(Core* system_core):_system_core(system_core) {
    
};

void Debug_Manager::begin() {
    Serial.begin(DEBUG_RATE);
    _on = DEBUG;
    while (true) {
        queuePacket* packet = nullptr;
        xQueueReceive(_system_core->queues.debug_manager,packet,portMAX_DELAY);
        switch (packet->operation) {
            case Print_System_Debug:
                systemLog(String(*static_cast<std::string*>(packet->data)->c_str()));
                break;
            case Print_App_Debug:
                applicationLog(String(*static_cast<std::string*>(packet->data)->c_str()));
                break;
            case Toggle_Debug:
                set(*static_cast<bool*>(packet->data));
                break;
        }
    }
}

void Debug_Manager::stop() {
    _on = false;
    Serial.println("[System] Debug ending");
    Serial.end();
}

void Debug_Manager::set(bool debug_value) {
    _on = debug_value;
    if (_on) {
        Serial.println("[System] Debug on");
    } else {
        Serial.println("[System] Debug off");
    }
}

void Debug_Manager::systemLog(String msg) {
    if (_on) {
        Serial.println("[System] " + msg);
    }
};

void Debug_Manager::applicationLog(String msg) {
    if (_on) {
        Serial.println("[Application] "+msg);
    }
};