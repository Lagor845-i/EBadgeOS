#include "wifi_manager.h"

Wifi_Manager::Wifi_Manager(systemQueues* system_queues):_system_queues(system_queues) {

};

bool Wifi_Manager::startDownload(downloadRequest* request) {
    request->link;
    request->download_location;
    return true;
}

bool Wifi_Manager::doingCurrentDownload() {
    return _downloading;
}