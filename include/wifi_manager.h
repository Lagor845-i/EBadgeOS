#pragma once
#include <WiFi.h>

#include "core.h"

class Wifi_Manager {
  public:
    Wifi_Manager(Core* system_core);
    bool connectToNetwork(std::string ssid,std::string password);
    bool getWifiInfo();

    bool startDownload(downloadRequest* request);
    bool doingCurrentDownload();
  
  private:
    bool _downloading = false;
    Core* _system_core;
};