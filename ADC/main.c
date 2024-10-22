#include "adc_drive.h"
#include "help_func.h"
#include "uart_drive.h"

//char num[10];
//int analog_rx = 0;

#define VREF 3.3             // Reference voltage (V)
#define ADC_RESOLUTION 4096  // 12-bit ADC resolution

char temp_str[10];  // String buffer to store temperature as a string
int adc_value = 0;
float temperature = 0.0;


int main(void) {
  // Initialize the ADC
  systick_init();
  UART_init(2, 115200);
  adc_init(adc1, PA, 0);
  adc_init(adc2, PA, 1);
  while (1) {
    if (adc_check(adc1, PA, 0)) {
      /*analog_rx = adc_rx(adc1, PA, 0) * 330;
		analog_rx = analog_rx / 100;
    UART_SEND(2,"ADC1: ");
		int2char(analog_rx,num);
		UART_SEND(2,num); 
    str_empty(num);
		UART_TX(2,'\n');
    */

      adc_value = adc_rx(adc1, PA, 0);  // Read the ADC value from PA0

      // Calculate the temperature in Celsius
      // (adc_value / ADC_RESOLUTION) * VREF = Voltage from LM35
      float voltage = (adc_value * VREF);
      temperature = voltage / 10;  // LM35 gives 10mV/°C, so multiply by 100

      temperature = temperature * 0.615;


      UART_SEND(2, "Temperature: ");
      float2char(temperature, temp_str, 2);  // Convert float temperature to string
      UART_SEND(2, temp_str);
      UART_SEND(2, "  deg C");

      str_empty(temp_str);
      UART_TX(2, '\n');
    }
  }
}