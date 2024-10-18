#include "gpio_drive.h"

int main(void)
{
// Initialize PA5 as output (e.g., control an LED)
	init_GP(PORTA, 5, OUT50, O_GP_PP);  // PA5 as output, 50 MHz, general-purpose push-pull

  // Initialize PC12 as input (e.g., read from a button)
  init_GP(PORTA, 11, IN, I_PP);  // PC12 as input, with pull-up resistor

  while(1)
  {
		// Read the state of the button on PC12
    int buttonState = R_GP(PORTA, 11);

    // If button is pressed (active-low), turn on the LED connected to PA5
    if (buttonState == LOW)  // Assuming the button pulls the pin to LOW when pressed
    {
			W_GP(PORTA, 5, HIGH);  // Turn on LED (PA5)
    }
    else
    {
			W_GP(PORTA, 5, LOW);  // Turn off LED (PA5)
    }
  }

	return 0;
}
