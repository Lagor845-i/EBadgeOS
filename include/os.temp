#pragma once

#include <string.h>

#include "api_data_types.h"
#include "core_queues.h"

class os {
    public:
        os(systemQueues* system_queues);
        float getOSAPIVersion(); //

        //Switching App Commands

        void startApp(std::string app_name); //
        void quitApp(); //

        //Wifi Commands

        std::string getCurrentWifiNetwork();
        void connectToWifi(std::string SSID, std::string password);
        void sendTCPData(std::string ip_address,int port);
        SSIDS getSSIDS();
        uint8_t downloadFromLink(std::string link);

        //Debug Commands

        bool toggleDebug();
        bool debugState();
        void setdebugBaudRate(int baud);
        bool log(std::string text);

        //Display Commands

        void getDisplayInfo(int data[2]);
        void updateDisplay();
        bool sendNotification(std::string text);

        //IO Commands

        Input getInput(); //
        
        void setALEDS(uint8_t color[23][3]);
        void setALED(uint8_t led_num,uint8_t color[3]);

        void getSDCardInfo();
    
    private:
        systemQueues* system_queues;
};