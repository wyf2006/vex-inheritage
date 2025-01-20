#ifndef SERIAL_H_
#define SERIAL_H_
#include "robot-config.h"

uint8_t* Float2Byte(float f);
void Serial_Send(float data);
#endif