#include "stats_manager.h"

Stats_Manager::Stats_Manager(Core* system_core):_system_core(system_core) {

}

void Stats_Manager::begin() {
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(100));
        reportStats();
    }
}

void Stats_Manager::reportStats() {
    systemDebug("Current PSRAM used: "+std::to_string(ESP.getPsramSize()-ESP.getFreePsram()),_system_core->queues.debug_manager);
}