#include "Encoder.h"


void Encoder_Init(Encoder *enc, GPIO_TypeDef *GPIOx, uint16_t GPIO_PinA, uint16_t GPIO_PinB){

	enc->pinA = GPIO_PinA;
	enc->pinB = GPIO_PinB;
	enc->aLastState = HAL_GPIO_ReadPin(GPIOx, enc->pinA);
}

int Encoder_Read(Encoder *enc, GPIO_TypeDef *GPIOx){

	enc->aState = HAL_GPIO_ReadPin(GPIOx, enc->pinA);
	enc->bState = HAL_GPIO_ReadPin(GPIOx, enc->pinB);
	if (enc->aState != enc->aLastState){
		if (enc->bState != enc->aState){
			if (enc->aState == 0 && enc->bState == 1){
				enc->aLastState = enc->aState;
				return 1;
			}
		}
		else {
			if (enc->aState == 0 && enc->aState == 0){
				enc->aLastState = enc->aState;
				return -1;
			}
		}
	}
	enc->aLastState = enc->aState;
	return 0;
}
