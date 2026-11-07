#pragma once

#include <esp_elf.h>
#include <Arduino.h>
#include <string.h>

#include "core_queues.h"
#include "elf_symbols.h"

class Application_Manager {
  public:
    Application_Manager(systemQueues* system_queues);
    void Start();
    
    //Api calls from application
    bool requestELFFile(String file_loc);
    bool quitApplication();
    bool printToConsole(String text);
    bool printToConsoleApp(String text);
  
  private:
    bool bootFile(uint8_t* file_bytes);
    uint8_t* recieveElfFile();
    bool sendAppApi();

    systemQueues* _system_queues;
    String app_folder;
    esp_elf_t current_app;
    String _change_app_to;
    uint8_t* _elf_buffer;
};