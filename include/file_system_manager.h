#include "services.h"
#include "core_queues.h"

#include <SD.h>
#include <SPI.h>
#include <string>
#include <Arduino.h>

#define MAX_ELF_FILES 32
#define FILENAME_SIZE 12

class File_System_Manager {
  public:
    File_System_Manager(systemQueues* system_queues);
    void begin();

  private:
    File getFile(String file_loc);
    void saveToFile(std::string file_name,uint8_t* bytes,std::string loc);
    void getAppFiles(char apps[MAX_ELF_FILES][FILENAME_MAX]);
    bool fileExistsByName(String file_loc);
    bool fileExistsByFile(File file);

    bool sd_card_installed = false;
    systemQueues* _system_queues;
};