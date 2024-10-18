#include "gpio_drive.h"

// Base addresses for GPIO ports
#define RCC_APB2ENR     (*((volatile unsigned long *) 0x40021018))
#define GPIO_A          0x40010800
#define GPIO_B          0x40010C00
#define GPIO_C          0x40011000

// Function to initialize GPIO pin
void init_GP(unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt)
{
    volatile unsigned long *CR;
    unsigned short tPIN = pin;
    unsigned short offset = 0x00;

    if (pin > 7)
    {
        tPIN -= 8;
        offset = 0x01;
    }

    if (port == PORTA) // Port A
    {
        RCC_APB2ENR |= 4; // Enable PORT A clock
        CR = (volatile unsigned long *)(GPIO_A + (offset ? 0x04 : 0x00)); // CRH or CRL
    }
    else if (port == PORTB) // Port B
    {
        RCC_APB2ENR |= 8; // Enable PORT B clock
        CR = (volatile unsigned long *)(GPIO_B + (offset ? 0x04 : 0x00)); // CRH or CRL
    }
    else if (port == PORTC) // Port C
    {
        RCC_APB2ENR |= 0x10; // Enable PORT C clock
        CR = (volatile unsigned long *)(GPIO_C + (offset ? 0x04 : 0x00)); // CRH or CRL
    }

    *CR &= ~(0xf << (tPIN * 4)); // Reset the target pin
    *CR |= ((dir << (tPIN * 4)) | (opt << (tPIN * 4 + 2))); // Set direction and option
}

// Function to read GPIO pin state
int R_GP(unsigned short port, unsigned short pin)
{
    volatile unsigned long *IDR;
    unsigned long offset = 0x08;
    int state;

    if (port == PORTA)
    {
        IDR = (volatile unsigned long *)(GPIO_A + offset);
    }
    else if (port == PORTB)
    {
        IDR = (volatile unsigned long *)(GPIO_B + offset);
    }
    else if (port == PORTC)
    {
        IDR = (volatile unsigned long *)(GPIO_C + offset);
    }

    state = ((*IDR & (1 << pin)) >> pin); // Read pin state
    return state;
}

// Function to write GPIO pin state
void W_GP(unsigned short port, unsigned short pin, unsigned short state)
{
    volatile unsigned long *ODR;
    unsigned long offset = 0x0C;

    if (port == PORTA)
    {
        ODR = (volatile unsigned long *)(GPIO_A + offset);
    }
    else if (port == PORTB)
    {
        ODR = (volatile unsigned long *)(GPIO_B + offset);
    }
    else if (port == PORTC)
    {
        ODR = (volatile unsigned long *)(GPIO_C + offset);
    }

    if (state == HIGH)
    {
        *ODR |= (1 << pin); // Set pin HIGH
    }
    else
    {
        *ODR &= ~(1 << pin); // Set pin LOW
    }
}

// Function to toggle GPIO pin state
void toggle_GP(unsigned short port, unsigned short pin)
{
    if (R_GP(port, pin)) // If pin is HIGH
    {
        W_GP(port, pin, LOW); // Set it to LOW
    }
    else
    {
        W_GP(port, pin, HIGH); // Set it to HIGH
    }
}
