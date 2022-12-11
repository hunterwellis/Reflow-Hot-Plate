#ifndef ENCODER_H
#define ENCODER_H

#include "stm32f103x6.h"
#include "stm32f1xx_hal.h"
#include "stdbool.h"


#define BITMASK 0b00001111;

typedef struct{
	bool tapped;
	int direction;
}Encoder;

Encoder updateEncoder();

#endif
