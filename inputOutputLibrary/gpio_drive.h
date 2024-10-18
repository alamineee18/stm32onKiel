#ifndef GPIO_DRIVE_H
#define GPIO_DRIVE_H

// Port Definitions (renamed to avoid conflict)
#define PORTA 1
#define PORTB 2
#define PORTC 3

// Directions
#define IN 0
#define OUT10 1
#define OUT2  2
#define OUT50 3

// Input Options
#define I_AN 0  // Analog mode
#define I_F  1  // Floating input
#define I_PP 2  // Input pull-up/pull-down

// Output Options
#define O_GP_PP 0  // General purpose output push-pull
#define O_GP_OD 1  // General purpose output open-drain
#define O_AF_PP 2  // Alternate function push-pull
#define O_AF_OD 3  // Alternate function open-drain

// Pin States
#define LOW  0
#define HIGH 1

// Function Declarations
void init_GP(unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt);
int R_GP(unsigned short port, unsigned short pin);
void W_GP(unsigned short port, unsigned short pin, unsigned short state);
void toggle_GP(unsigned short port, unsigned short pin);

#endif // GPIO_DRIVE_H
