#pragma once
#include <NimBLEDevice.h>

#include "core.h"

class Bluetooth_Manager {
  public:
    Bluetooth_Manager(Core* system_core);

  private:
    Core* _system_core;
};