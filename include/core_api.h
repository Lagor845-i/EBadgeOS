#pragma once

#include <string>

struct Wifi {
    bool connected = false;
    std::string SSID = 0;
    float signal_strenth;
    std::string* current_downloads[5];
};

struct Application {

};

struct Stats {
    float core_usage = 0;
    float ram_usage = 0;
};

struct Display {

};

struct File_System {
    bool SD_installed = false;
    float SD_size = 0;
    float SD_used_storage = 0;

    float Internal_size = 0;
    float Internal_used = 0;
};

struct Bluetooth {

};

struct LEDs {

};

struct Input {
    int a = 0;
    int b = 0;
    int u = 0;
    int d = 0;
    int l = 0;
    int r = 0;
    float jsx = 0.0;
    float jsy = 0.0;
    float accel_x = 0.0;
    float accel_y = 0.0;
    float accel_z = 0.0;
};

struct systemApi {
    Wifi api;
    Application current_application;
    Stats statistics;
    Display display;
    File_System file_system;
    Bluetooth bluetooth;
    LEDs leds;
    Input input;
};