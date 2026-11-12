#include "config.h"
#include "core.h"

#include <SD.h>
#include <SPI.h>
#include <string>
#include <Arduino.h>
#include <LittleFS.h>

#define MAX_ELF_FILES 32
#define FILENAME_SIZE 12

class File_System_Manager {
  public:
    File_System_Manager(Core* system_core);
    void begin();

  private:
    uint8_t* readFile(std::string loc);
    void writeToFile(std::string loc,uint8_t* bytes);
    void getAppFiles(char apps[MAX_ELF_FILES][FILENAME_MAX]);
    bool fileExistsByName(String file_loc);
    bool fileExistsByFile(File file);
    int getCardSize();
    void appendToFile(std::string loc,uint8_t* bytes);

    bool sd_card_installed = false;
    Core* _system_core;
};