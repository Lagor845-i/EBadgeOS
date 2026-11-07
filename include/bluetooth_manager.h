#pragma once
#include <NimBLEDevice.h>

#include "core_queues.h"

class Bluetooth_Manager {
  public:
    Bluetooth_Manager(systemQueues* system_queues);

  private:
    systemQueues* _system_queues;
};