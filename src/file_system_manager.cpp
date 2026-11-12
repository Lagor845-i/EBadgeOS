#include "file_system_manager.h"

#define SD_CS 40
#define SD_MOSI 39
#define SD_CLK 38
#define SD_MISO 37

SPIClass sdSPI(FSPI);

File_System_Manager::File_System_Manager(Core* system_core):_system_core(system_core) {
    LittleFS.begin();
    sdSPI.begin(
        SD_CLK,
        SD_MISO,
        SD_MOSI,
        SD_CS
    );
    if (!SD.begin(SD_CS,sdSPI,10000000,"/sd",30,true)) {
        _system_core->queues.debug_manager;
        systemDebug("No SD card installed...",_system_core->queues.debug_manager);
    } else {
        systemDebug("SD card detected with " + std::to_string(getCardSize()) + " Bytes",_system_core->queues.debug_manager);
        sd_card_installed = true;
        if (!SD.open("/apps")) {
            SD.mkdir("/apps");
        }
    }
};

void File_System_Manager::begin() {
    while (true) {
        queuePacket* packet = nullptr;
        xQueueReceive(_system_core->queues.file_system_manager,packet,portMAX_DELAY);
        switch (packet->operation) {
            case READ_FILE: {
                queuePacket* new_packet = new queuePacket();
                new_packet->operation = RECEIVE_FILE_OUTGOING;
                new_packet->data = readFile(*static_cast<std::string*>(packet->data));
                xQueueSend(packet->sender,new_packet,1);
                break; 
            }
            case WRITE_TO_FILE: {
                queueFile* file = static_cast<queueFile*>(packet->data);
                writeToFile(file->file_name,file->data);
                delete file;
                delete packet; 
                break; 
            }
            case APPEND_TO_FILE:

                break;
        }
    }
}

int File_System_Manager::getCardSize() {
    return SD.cardSize();
}

void File_System_Manager::appendToFile(std::string loc,uint8_t* bytes) {

    std::string data = loc.substr(0, loc.find('/')+1);
    File file_handle;

    if (data == INTERNAL_STORAGE) {
        std::string file = loc.substr(std::string("local//").length());
        file_handle = LittleFS.open(file.c_str(),FILE_APPEND);
        

    } else if (data == EXTERNAL_STORAGE) {
        std::string file = loc.substr(std::string("SD//").length());
        file_handle = SD.open(file.c_str(),FILE_APPEND);
    }

    file_handle.write(*bytes);
    file_handle.close();
}

void File_System_Manager::writeToFile(std::string loc,uint8_t* bytes) {

    std::string data = loc.substr(0, loc.find('/')+1);
    File file_handle;

    if (data == INTERNAL_STORAGE) {
        std::string file = loc.substr(std::string("local//").length());
        file_handle = LittleFS.open(file.c_str(),FILE_WRITE);
        

    } else if (data == EXTERNAL_STORAGE) {
        std::string file = loc.substr(std::string("SD//").length());
        file_handle = SD.open(file.c_str(),FILE_WRITE);
    }

    file_handle.write(*bytes);
    file_handle.close();
    delete bytes;
}

uint8_t* File_System_Manager::readFile(std::string loc) {

    std::string file_drive = loc.substr(0, loc.find('/')+1);
    File file_handle;

    if (file_drive == INTERNAL_STORAGE) {
        std::string file = loc.substr(std::string("local//").length());
        file_handle = LittleFS.open(file.c_str(),FILE_WRITE);
    } else if (file_drive == EXTERNAL_STORAGE) {
        std::string file = loc.substr(std::string("SD//").length());
        file_handle = SD.open(file.c_str(),FILE_READ);
    }

    uint8_t* data = new uint8_t((uint8_t)file_handle.read());
    file_handle.close();
    return data;
};

bool File_System_Manager::fileExistsByName(String file_loc) {
    if (SD.exists(file_loc)) {
        return true;
    }
    return false;
}

void File_System_Manager::getAppFiles(char apps[MAX_ELF_FILES][FILENAME_MAX]) {
    File apps_folder = SD.open("/Apps");
    if (!apps_folder) {
        systemDebug("Apps folder not found",_system_core->queues.debug_manager);
    }
    File file = apps_folder.openNextFile();
    int i = 0;
    while (file && i < MAX_ELF_FILES) {
        if (!file.isDirectory()) {
            String file_name = file.name();
            if (file_name.endsWith(".app")) {
                file_name.remove(file_name.length()-4);
                file_name.toCharArray(apps[i],FILENAME_MAX);
                i++;
            }
        }
        file.close();
        file = file.openNextFile();
    }
}