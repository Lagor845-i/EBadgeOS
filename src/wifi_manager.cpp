#include "wifi_manager.h"

Wifi_Manager::Wifi_Manager(Core* system_core):_system_core(system_core) {

};

bool Wifi_Manager::startDownload(downloadRequest* request) {
    request->link;
    request->download_location;
    return true;
}

bool Wifi_Manager::doingCurrentDownload() {
    return _downloading;
}