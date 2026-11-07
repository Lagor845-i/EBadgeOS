#include "file_system_manager.h"

#define SD_CS 40
#define SD_MOSI 39
#define SD_CLK 38
#define SD_MISO 37

SPIClass sdSPI(FSPI);

File_System_Manager::File_System_Manager(systemQueues* system_queues):_system_queues(system_queues) {
    sdSPI.begin(
        SD_CLK,
        SD_MISO,
        SD_MOSI,
        SD_CS
    );
    if (!SD.begin(SD_CS,sdSPI,10000000,"/sd",30,true)) {
        _system_queues->debug_manager
        _system_services.systemLog("No SD card installed...");
        _system_services.error("No SD Card Installed");
    } else {
        _system_services.systemLog("SD card detected with "+String(SD.cardSize())+" Bytes");
        sd_card_installed = true;
        if (!SD.open("/apps")) {
            SD.mkdir("/apps");
        }
    }
};

void File_System_Manager::begin() {
    while (true) {
        queuePacket* packet = nullptr;
        xQueueReceive(_system_queues->file_system_manager,packet,portMAX_DELAY);
        switch (packet->operation) {
            case 0:

                break;
            case 1:
                
                break;
        }
    }
}


void File_System_Manager::saveToFile(std::string file_name,uint8_t* bytes,std::string loc) {
    std::string file = loc + file_name;
    File file_handle = SD.open(file.c_str(),FILE_WRITE);
    file_handle.write(*bytes);
    file_handle.close();
}

File File_System_Manager::getFile(String file_loc) {
    return SD.open(file_loc);
};

bool File_System_Manager::fileExistsByName(String file_loc) {
    if (SD.exists(file_loc)) {
        return true;
    }
    return false;
}

bool File_System_Manager::fileExistsByFile(File file) {
    if (!file) {
        return false;
    }
    return true;
};

void File_System_Manager::getAppFiles(char apps[MAX_ELF_FILES][FILENAME_MAX]) {
    File apps_folder = SD.open("/Apps");
    if (!apps_folder) {
        _system_services.systemLog("Apps folder not found");
    }
    File file = apps_folder.openNextFile();
    int i = 0;
    while (file && i < MAX_ELF_FILES) {
        if (!file.isDirectory()) {
            String file_name = file.name();
            if (file_name.endsWith(".elf")) {
                file_name.remove(file_name.length()-4);
                file_name.toCharArray(apps[i],FILENAME_MAX);
                i++;
            }
        }
        file.close();
        file = file.openNextFile();
    }
}