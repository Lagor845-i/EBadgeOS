#pragma once

#include <Arduino.h>
#include <string>

struct SSIDS {
    std::string* ssids[10];
    int amount;
};

struct packet {
    std::string Ip_address = "";
    int port;
};

struct downloadRequest {
    std::string link;
    std::string download_location;
};

struct queueFile {
    std::string file_name;
    uint8_t* data;
};