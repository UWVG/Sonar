#pragma once
#include <stdint.h>
void loop();
void msgCallBack(uint8_t* data, int len);
extern void sonar_write(uint8_t* data, int len);
