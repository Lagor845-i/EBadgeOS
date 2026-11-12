#include "input_manager.h"

#include <Wire.h>
#include <Arduino.h>

#define JOYSTICK_X_PIN 8
#define JOYSTICK_Y_PIN 9

#define A_BUTTON 34
#define B_BUTTON 33

#define U_BUTTON 11
#define D_BUTTON 47
#define L_BUTTON 21
#define R_BUTTON 10

const int PIN_I2C_SDA = 41;
const int PIN_I2C_SCL = 42;
const uint8_t ACCEL_ADDR = 0x1C;

// A few of the accelerometer's internal register addresses (from its datasheet).
const uint8_t REG_OUT_X_MSB = 0x01; // first of six data bytes (X,Y,Z)
const uint8_t REG_WHO_AM_I   = 0x0D; // ID register: should read 0x2A
const uint8_t REG_XYZ_CFG    = 0x0E; // sets the +/- g range
const uint8_t REG_PL_STATUS  = 0x10; // current orientation
const uint8_t REG_PL_CFG     = 0x11; // turn orientation detection on
const uint8_t REG_PULSE_CFG  = 0x21; // turn tap detection on
const uint8_t REG_PULSE_SRC  = 0x22; // reports a tap when it happens
const uint8_t REG_PULSE_THSX = 0x23; // tap strength needed on X
const uint8_t REG_PULSE_THSY = 0x24; // tap strength needed on Y
const uint8_t REG_PULSE_THSZ = 0x25; // tap strength needed on Z
const uint8_t REG_PULSE_TMLT = 0x26; // how long a tap can last
const uint8_t REG_PULSE_LTCY = 0x27; // wait time after a tap
const uint8_t REG_PULSE_WIND = 0x28; // window to catch a second tap
const uint8_t REG_CTRL_REG1  = 0x2A; // standby / active + speed

Input_Manager::Input_Manager(Core* system_core):_system_core(system_core) {
    pinMode(A_BUTTON,INPUT);
    pinMode(B_BUTTON,INPUT);
    pinMode(U_BUTTON,INPUT);
    pinMode(D_BUTTON,INPUT);
    pinMode(L_BUTTON,INPUT);
    pinMode(R_BUTTON,INPUT);
    pinMode(JOYSTICK_X_PIN,INPUT);
    pinMode(JOYSTICK_Y_PIN,INPUT);
    systemDebug("Inputs Initialized",_system_core->queues.debug_manager);
    
    Wire.begin(PIN_I2C_SDA,PIN_I2C_SCL,400000);
};

void Input_Manager::begin() {
    int delay = 30;
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(delay));
        sysGetInput();
        queuePacket* packet;
        if (xQueueReceive(_system_core->queues.input_manager,packet,0) == pdTRUE) {
            switch (packet->operation) {
                case Change_Input_Polling_Rate:
                    delay = *(int*)packet->data;
            }
            delete packet->data;
            delete packet;
        }

    }
}

void Input_Manager::readAccelerometer(float *buffer) {
  Wire.beginTransmission(ACCEL_ADDR);
  Wire.write(REG_OUT_X_MSB);
  Wire.endTransmission(false);
  Wire.requestFrom(ACCEL_ADDR, 6);
  for (uint8_t i = 0; i < 3; i++) {
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    int raw = ((int)msb << 8 | lsb) >> 4; // combine, then keep the top 12 bits
    if (raw > 2047) {
    raw = raw - 4096;                    // fix up negative numbers
    }
    buffer[i] = raw / 1024.0;
  }
}

void Input_Manager::sysGetInput() {
    stuff.a = digitalRead(A_BUTTON);
    stuff.b = digitalRead(B_BUTTON);
    stuff.u = digitalRead(U_BUTTON);
    stuff.d = digitalRead(D_BUTTON);
    stuff.l = digitalRead(L_BUTTON);
    stuff.r = digitalRead(R_BUTTON);
    stuff.jsx = analogRead(JOYSTICK_X_PIN);
    stuff.jsy = analogRead(JOYSTICK_Y_PIN);
    float buffer[3];
    readAccelerometer(buffer);
    stuff.accel_x = buffer[0];
    stuff.accel_y = buffer[1];
    stuff.accel_z = buffer[2];
}