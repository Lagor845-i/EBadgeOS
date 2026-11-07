#include "stats_manager.h"

Stats_Manager::Stats_Manager(systemQueues* system_queues):_system_queues(system_queues) {

}

void Stats_Manager::reportStats() {
    ESP.getFreeHeap();
    _system_services.systemLog("Current PSRAM used"+String(ESP.getPsramSize()-ESP.getFreePsram()));
}