#include "Encoder.h"

void initEncoder(){


}

int Encoder_Read(){

	static GPIO_PinState aState = GPIO_PIN_SET;
	static GPIO_PinState bState = GPIO_PIN_SET;
	static GPIO_PinState aLastState = GPIO_PIN_SET;

	aState = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
	bState = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);

	if (aState == GPIO_PIN_RESET && aState != aLastState){
		if (bState == aState){
			aLastState = aState;
			return 1;
		}
		else {
			aLastState = aState;
			return -1;
		}
	}
	aLastState = aState;
	HAL_Delay(1);
	return 0;
}

bool Encoder_Tapped(){
	static bool debouncing = false;
	static GPIO_PinState prev = GPIO_PIN_SET;
	static GPIO_PinState current = GPIO_PIN_SET;
	current = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);
	bool tapped = false;

	if (debouncing){
		HAL_Delay(1000);
		debouncing = false;
	}

	if (!debouncing && prev == GPIO_PIN_SET && current == GPIO_PIN_RESET){
		tapped = true;
		debouncing = true;
	}

	prev = current;
	return tapped;

}
Encoder updateEncoder(){
	Encoder enc;
	enc.tapped = Encoder_Tapped();
	enc.direction = Encoder_Read();

	return enc;
}
