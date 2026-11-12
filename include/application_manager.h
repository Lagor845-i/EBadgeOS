#pragma once

#include <esp_elf.h>
#include <Arduino.h>
#include <string.h>

#include "core.h"
#include "elf_symbols.h"

class Application_Manager {
  public:
    Application_Manager(Core* system_core);
    void Begin();
  
  private:
    bool requestELFFile(std::string file_name);
    bool quitApplication();
    bool bootFile(uint8_t* file_bytes);
    bool sendAppApi();


    Core* _system_core;
    String app_folder;
    esp_elf_t current_app;
    String _change_app_to;
    uint8_t* _elf_buffer;
};