#include "services.h"
#include "managers.h"
#include "core_queues.h"

void startelflauncher(void* task_queues) {
  Application_Manager* application_manager = new Application_Manager(static_cast<systemQueues*>(task_queues));
}

void startDebugManager(void* task_queues) {
  Debug_Manager* debug_manager = new Debug_Manager(static_cast<systemQueues*>(task_queues));
}

void startDisplay(void* task_queues) {
  Display_Manager* display_manager = new Display_Manager(static_cast<systemQueues*>(task_queues));
}

void startLedManager(void* task_queues) {
  Led_Manager* led_manager = new Led_Manager(static_cast<systemQueues*>(task_queues));
}

void startWifiManager(void* task_queues) {
  Wifi_Manager* wifi_manager = new Wifi_Manager(static_cast<systemQueues*>(task_queues));
}

void startInputManager(void* task_queues) {
  Input_Manager* input_manager = new Input_Manager(static_cast<systemQueues*>(task_queues));
}

void startFileSystemManager(void* task_queues) {
  File_System_Manager* file_system_manager = new File_System_Manager(static_cast<systemQueues*>(task_queues));
}

void startAudioManager(void* task_queues) {
  Audio_Manager* audio_manager = new Audio_Manager(static_cast<systemQueues*>(task_queues));
}

void startBluetoothManager(void* task_queues) {
  Bluetooth_Manager* bluetooth_manager = new Bluetooth_Manager(static_cast<systemQueues*>(task_queues));
}

void startStatsManager(void* task_queues) {
  Stats_Manager* stats_manager = new Stats_Manager(static_cast<systemQueues*>(task_queues));
}

void setup() {
  systemQueues* queues;
  xTaskCreatePinnedToCore(startelflauncher,"ElfLauncher",4096,queues,3,nullptr,1);
  xTaskCreate(startDisplay,"Display",4096,queues,3,nullptr);
  xTaskCreate(startDebugManager,"Display",4096,queues,3,nullptr);
  xTaskCreate(startLedManager,"Display",4096,queues,3,nullptr);
  xTaskCreate(startWifiManager,"Display",4096,queues,3,nullptr);
  xTaskCreate(startInputManager,"Display",4096,queues,3,nullptr);
  xTaskCreate(startFileSystemManager,"Display",4096,queues,3,nullptr);
  xTaskCreate(startAudioManager,"Display",4096,queues,3,nullptr);
  xTaskCreate(startBluetoothManager,"Display",4096,queues,3,nullptr);
  xTaskCreate(startStatsManager,"Display",4096,queues,3,nullptr);
}

void loop() {
  
}