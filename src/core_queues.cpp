#include "core_queues.h"

void systemDebug(std::string text,QueueHandle_t debug_queue) {
    queuePacket* packet;
    std::string* temp = new std::string(text);
    packet->operation = Print_System_Debug;
    packet->data = temp;
    xQueueSend(debug_queue,packet,0);
}