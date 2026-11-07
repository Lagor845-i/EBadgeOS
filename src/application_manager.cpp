#include "application_manager.h"

extern "C" {
  void* os_api = nullptr;
}

Application_Manager::Application_Manager(systemQueues* system_queues):_system_queues(system_queues) {
  printToConsole("Starting Application Manager");
  register_custom_elf_symbols();
}

void Application_Manager::Start() {
  requestELFFile(BOOT_APP);
  sendDebug("Requested ELF file: " + std::string(BOOT_APP),_system_queues->debug_manager);
  bool first = true;
  bool running = true;
  while (running) {
    if (first) {
      do {
        uint8_t* return_buffer = recieveElfFile();
        _elf_buffer = return_buffer;
        if (return_buffer == nullptr) {
          continue;
        } else {
          printToConsole("Attempting to boot app");
          if (bootFile(_elf_buffer)) {
            printToConsole("Boot successful");
          } else {
            printToConsole("Boot Failed!!!");
          }
          break;
        }
      } while (true);
      first = false;
    }
  }
}

bool Application_Manager::isElf(File file) {
  if (String(file.name()).endsWith(".app")) {return true;}
  return false;
}

bool Application_Manager::requestELFFile(String file_name) {
  String temp = String(APP_FOLDER + file_name);
  _cross_core_buffers->request_elf_file.file_name = temp;
  _cross_core_buffers->request_elf_file.new_request = true;
  return true;
}

uint8_t* Application_Manager::recieveElfFile() {
  if (_cross_core_buffers->recieve_buffer.elf_ready) {
    _cross_core_buffers->recieve_buffer.elf_ready = false;
    return _cross_core_buffers->recieve_buffer.elf_buffer;
  }
  return nullptr;
}

//Used chatgpt on this function for assistance with the ELF loading.
bool Application_Manager::bootFile(uint8_t* file_bytes) {
  if (esp_elf_init(&current_app) != ESP_OK) {
    return false;
  }

  if (esp_elf_relocate(&current_app,file_bytes) != ESP_OK) {
    printToConsole("Invalid Elf Configuration");
    return false;
  }

  //Sets the entry for the ELF application. Had to convert it in order for it to be able to plug into a void* function pointer
  if (esp_elf_request(&current_app,0,0,nullptr)) {
    printToConsole("Failed to Boot ELF");
    return false;
  }
  return true;
}

bool Application_Manager::quitApplication() {
  esp_elf_deinit(&current_app);
  heap_caps_free(_elf_buffer);
  return true;
}