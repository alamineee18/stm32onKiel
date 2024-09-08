#include "stm32f10x.h"                  // Device header

void Delay(int time);

int main(void)
{
	RCC->APB2ENR |= 4;			//Enabling port A
	RCC->APB2ENR |= 0x10;		//Enable Port C
	
	GPIOA->CRL &= 0xFFFFFFF0;		// Reset the port A pin 0
	GPIOA->CRL |= 0x8;					// Set port A pin 0 as input push pull
	
	GPIOC->CRH &= 0xFF0FFFFF;
	GPIOC->CRH |= 0x00300000;
	
	while(1)
	{
		if(GPIOA->IDR & 0x00000001)
		{
			Delay(10);
			GPIOC->ODR ^=0x2000;
			Delay(10);
		}
	}
}

void Delay (int time){
	int t;
	for(; time>0; time--)
	{
		for(t = 0; t<100000; t++)
		{}
	}
}