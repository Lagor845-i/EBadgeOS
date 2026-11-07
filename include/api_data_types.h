#pragma once

#include <string.h>

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

struct Input {
    int a;
    int b;
    int u;
    int d;
    int l;
    int r;
    float jsx;
    float jsy;
    float accel_x;
    float accel_y;
    float accel_z;
};