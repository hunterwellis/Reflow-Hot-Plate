#ifndef ENCODER_H
#define ENCODER_H

#include "stm32f103x6.h"
#include "stm32f1xx_hal.h"

#define BITMASK 0b00001111;

typedef struct{
	uint16_t pinA;
	uint16_t pinB;

	int aState;
	int bState;
	int aLastState;
}Encoder;

void Encoder_Init(Encoder *encoder, GPIO_TypeDef *GPIOx, uint16_t GPIO_PinA, uint16_t GPIO_PinB);
int Encoder_Read(Encoder *encoder, GPIO_TypeDef *GPIOx);


#endif
