#include "systick_time.h"
#include "gp_drive.h"  // Your custom GPIO library
#include "i2c_drive.h"
#include "oled_drive.h"


volatile uint16_t adcValue = 0;
volatile float temperature = 0; 
char charTemp[6];

void ADC_Init(void);
void ADC1_IRQHandler(void);
float ConvertTemperature(uint16_t adcValue);
void floatToStr(float temp, char* str);

void DelayMs(unsigned long t);
void DelayMillis(void);
void systick_init(void);


int main(void)
{
  // Initialize GPIO for ADC pin (PA0) using gpio_drive library
  init_GP(PA, 0, IN, I_AN);  // PA0 set to analog input (for LM35)
  
  // Initialize ADC
  ADC_Init();
	// Systick Initialize
	systick_init();
  
  //OLED initialize for I2C channel 1
	oled_init_64(1);
  
	oled_blank(1);
	//oled_msg(1,2,37,"Hello");
  //oled_msg(1,3,25,"Al-Amin Kabir");
	
	while(1)
	{
    // Display the temperature on the OLED
    //OLED_Clear();
    //OLED_DisplayTemperature(temperature);  // Display temperature on OLED
    
    // Manually convert float to string
    floatToStr(temperature, charTemp);
    
    oled_msg(1,2,20,"Temperature");
    oled_msg(1,4,20,charTemp);
    //oled_msg(1,2,26,"C");

	}
	
}


void ADC_Init(void) {
  // Enable clock for ADC1 and GPIOA
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // Enable GPIOA clock
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;  // Enable ADC1 clock

  // Configure ADC1 for channel 0 (PA0)
  ADC1->SQR1 = 0;              // Only one conversion
  ADC1->SQR3 = 0;              // First conversion in regular sequence is channel 0
  ADC1->CR1 |= ADC_CR1_EOCIE;  // Enable end-of-conversion interrupt
  ADC1->CR2 |= ADC_CR2_ADON;   // Enable ADC1

  // Enable ADC1 interrupt in NVIC
  NVIC_EnableIRQ(ADC1_2_IRQn);

  // Start ADC conversion
  ADC1->CR2 |= ADC_CR2_SWSTART;
}

void ADC1_IRQHandler(void) {
  if (ADC1->SR & ADC_SR_EOC) {
    adcValue = ADC1->DR;                         // Read the converted value
    temperature = ConvertTemperature(adcValue);  // Convert ADC to temperature
    ADC1->SR &= ~ADC_SR_EOC;                     // Clear the EOC flag
  }
}

float ConvertTemperature(uint16_t adcValue) {
  // Assuming 12-bit ADC and 3.3V reference
  float voltage = (adcValue * 3.3f) / 4096.0f;
  return voltage * 100.0f;  // LM35 gives 10mV/°C
}

void floatToStr(float temp, char* str)
{
    // Extract the integer part
    int intPart = (int)temp; 
    // Extract the fractional part (2 decimal places)
    int fracPart = (int)((temp - intPart) * 100);

    // Convert integer part to string and fractional part to string
    str[0] = (intPart / 10) + '0';      // Tens digit of integer part
    str[1] = (intPart % 10) + '0';      // Ones digit of integer part
    str[2] = '.';                       // Decimal point
    str[3] = (fracPart / 10) + '0';     // Tens digit of fractional part
    str[4] = (fracPart % 10) + '0';     // Ones digit of fractional part
    str[5] = '\0';                      // Null terminator to end the string
}

