#pragma once
#include <WiFi.h>

#include "core_queues.h"

class Wifi_Manager {
  public:
    Wifi_Manager(systemQueues* system_queues);
    bool connectToNetwork(std::string ssid,std::string password);
    bool getWifiInfo();

    bool startDownload(downloadRequest* request);
    bool doingCurrentDownload();
  
  private:
    bool _downloading = false;
    systemQueues* _system_queues;
};