#include "Encoder.h"

void initEncoder(){


}

int Encoder_Read(){
	static uint32_t prev = 0;
	static uint32_t curr = 0;
	curr = (TIM3->CNT)>>2;
	static int dir = 0;
	dir = prev-curr;
	prev = curr;
	if (dir > 3 || dir < -3){
			return 0;
	}
	else return dir;
}

bool Encoder_Tapped(){
	static bool debouncing = false;
	static GPIO_PinState prev = GPIO_PIN_SET;
	static GPIO_PinState current = GPIO_PIN_SET;
	current = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
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
