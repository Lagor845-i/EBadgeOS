#include "application_manager.h"

extern "C" {
  void* os_api = nullptr;
}

Application_Manager::Application_Manager(Core* system_core):_system_core(system_core) {
  systemDebug("Starting Application Manager",_system_core->queues.debug_manager);
  register_custom_elf_symbols();
}

void Application_Manager::Begin() {
  requestELFFile(BOOT_APP);
  systemDebug("Requested ELF file at: " + BOOT_APP,_system_core->queues.debug_manager);
  os_api = _system_core;
  while (true) {
    queuePacket* packet;
    if (xQueueReceive(_system_core->queues.application_manager,packet,portMAX_DELAY) == pdTRUE) {
      switch (packet->operation) {
        case RECEIVE_FILE_OUTGOING:
          bootFile(static_cast<queueFile*>(packet->data)->data);
          break;

        case BOOT_APP_FILE:
          requestELFFile(*static_cast<std::string*>(packet->data));
          break;
      }
      
      if (packet->data) {
        delete packet->data;
      }
      delete packet;
    }
  }
}

bool Application_Manager::requestELFFile(std::string file_name) {
  queuePacket* packet;
  packet->sender = _system_core->queues.application_manager;
  packet->operation = READ_FILE;
  std::string* temp = new std::string(file_name);
  packet->data = temp;
  if (xQueueSend(_system_core->queues.file_system_manager,packet,1) == pdTRUE) {
    return true;
  }
  return false;
}

//Used chatgpt on this function for assistance with the ELF loading.
bool Application_Manager::bootFile(uint8_t* file_bytes) {
  if (esp_elf_init(&current_app) != ESP_OK) {
    return false;
  }

  if (esp_elf_relocate(&current_app,file_bytes) != ESP_OK) {
    systemDebug("Invalid Elf Configuration",_system_core->queues.debug_manager);
    return false;
  }

  //Sets the entry for the ELF application. Had to convert it in order for it to be able to plug into a void* function pointer
  if (esp_elf_request(&current_app,0,0,nullptr)) {
    systemDebug("Failed to Boot ELF",_system_core->queues.debug_manager);
    return false;
  }
  return true;
}

bool Application_Manager::quitApplication() {
  esp_elf_deinit(&current_app);
  heap_caps_free(_elf_buffer);
  return true;
}