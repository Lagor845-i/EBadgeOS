#include "managers.h"
#include "core.h"

void startelflauncher(void* core) {
  Application_Manager* application_manager = new Application_Manager(static_cast<Core*>(core));
  application_manager->Begin();
}

void startDebugManager(void* core) {
  Debug_Manager* debug_manager = new Debug_Manager(static_cast<Core*>(core));
  debug_manager->begin();
}

void startDisplay(void* core) {
  Display_Manager* display_manager = new Display_Manager(static_cast<Core*>(core));
  display_manager->begin();
}

void startLedManager(void* core) {
  Led_Manager* led_manager = new Led_Manager(static_cast<Core*>(core));
  led_manager->begin();
}

void startWifiManager(void* core) {
  Wifi_Manager* wifi_manager = new Wifi_Manager(static_cast<Core*>(core));
}

void startInputManager(void* core) {
  Input_Manager* input_manager = new Input_Manager(static_cast<Core*>(core));
  input_manager->begin();
}

void startFileSystemManager(void* core) {
  File_System_Manager* file_system_manager = new File_System_Manager(static_cast<Core*>(core));
  file_system_manager->begin();
}

void startAudioManager(void* core) {
  Audio_Manager* audio_manager = new Audio_Manager(static_cast<Core*>(core));
}

void startBluetoothManager(void* core) {
  Bluetooth_Manager* bluetooth_manager = new Bluetooth_Manager(static_cast<Core*>(core));
}

void startStatsManager(void* core) {
  Stats_Manager* stats_manager = new Stats_Manager(static_cast<Core*>(core));
  stats_manager->begin();
}

void setup() {
  Core* system_core;
  xTaskCreatePinnedToCore(startelflauncher,"ElfLauncher",4096,system_core,3,nullptr,1);
  xTaskCreate(startDisplay,"Display",4096,system_core,3,nullptr);
  xTaskCreate(startDebugManager,"Display",4096,system_core,3,nullptr);
  xTaskCreate(startLedManager,"Display",4096,system_core,3,nullptr);
  xTaskCreate(startWifiManager,"Display",4096,system_core,3,nullptr);
  xTaskCreate(startInputManager,"Display",4096,system_core,3,nullptr);
  xTaskCreate(startFileSystemManager,"Display",4096,system_core,3,nullptr);
  xTaskCreate(startAudioManager,"Display",4096,system_core,3,nullptr);
  xTaskCreate(startBluetoothManager,"Display",4096,system_core,3,nullptr);
  xTaskCreate(startStatsManager,"Display",4096,system_core,3,nullptr);
}

void loop() {
  
}

