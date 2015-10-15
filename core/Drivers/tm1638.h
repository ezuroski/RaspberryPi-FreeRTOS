#include "types.h"

// set to 0 to use old library, set to 1 to use freertos library
#if 1
#include "gpio.h"
#else
#include "gpio2.h"
#define SetGpioFunction(a,b) setup_gpio(a,b)
#define SetGpio(a,b) set_gpio(a,b)
#define ReadGpio(a) get_gpio(a)
#define GPIO_IN GPIO_INPUT
#define GPIO_OUT GPIO_OUTPUT
#endif

// GPIOs used for TM1638 display module
#define DISP_DIO 19
#define DISP_CLK 20
#define DISP_STB 21

#define DISP_DELAY 10
// rough microsecond delay (poll)
void delay_us( unsigned int us );
void tm1638_sendbyte( byte data );
byte tm1638_readbyte();
byte tm1638_segval(char letter);
void tm1638_init();
void tm1638_beginsend();
void tm1638_endsend();
void tm1638_displaynumber(unsigned int num, unsigned int pos);
void tm1638_displaystring(char* data, unsigned int pos);
void tm1638_clear();
