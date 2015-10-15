#include "tm1638.h"
#include <FreeRTOS.h>
#include <task.h>

// rough microsecond delay (poll)
void delay_us( unsigned int us )
{
    // dummy volatile variable to prevent this function from being optimized into a nop
    volatile unsigned int loop_count;

    // clock is 700mhz, 700 cycles per microsecond, x cycles per loop
    //loop_count = us * (700/10);
	// that was the idea anyway, now just set numbers empirically
	loop_count = us * 7;
    while( loop_count-- );
}

void disp_delay()
{
#if 1
	vTaskDelay(1);
#else
	delay_us(DISP_DELAY);
#endif
}

// Get 7-seg code for a given letter
// Bit positions on display:
//  -0-
// 5   1
//  -6-
// 4   2
//  -3-  .7
byte tm1638_charval(char letter)
{
	byte retval;
	switch(letter)
	{
		case 0x20: retval = 0x00; break;
		case 0x21: retval = 0x82; break;
		case 0x22: retval = 0x22; break;
		case 0x23: retval = 0x49; break;
		case 0x24: retval = 0x5a; break;
		case 0x25: retval = 0x5d; break;
		case 0x26: retval = 0x7b; break;
		case 0x27: retval = 0x02; break;
		case 0x28: retval = 0x31; break;
		case 0x29: retval = 0x07; break;
		case 0x2a: retval = 0x63; break;
		case 0x2b: retval = 0x70; break;
		case 0x2c: retval = 0x84; break;
		case 0x2d: retval = 0x40; break;
		case 0x2e: retval = 0x80; break;
		case 0x2f: retval = 0x52; break;
		case 0x30: retval = 0x3f; break;
		case 0x31: retval = 0x06; break;
		case 0x32: retval = 0x5b; break;
		case 0x33: retval = 0x4f; break;
		case 0x34: retval = 0x66; break;
		case 0x35: retval = 0x6d; break;
		case 0x36: retval = 0x7d; break;
		case 0x37: retval = 0x07; break;
		case 0x38: retval = 0x7f; break;
		case 0x39: retval = 0x6f; break;
		case 0x3a: retval = 0x48; break;
		case 0x3b: retval = 0xc8; break;
		case 0x3c: retval = 0x61; break;
		case 0x3d: retval = 0x41; break;
		case 0x3e: retval = 0x43; break;
		case 0x3f: retval = 0x53; break;
		case 0x40: retval = 0x3b; break;
		case 0x41: retval = 0x77; break;
		case 0x42: retval = 0x7c; break;
		case 0x43: retval = 0x39; break;
		case 0x44: retval = 0x5e; break;
		case 0x45: retval = 0x79; break;
		case 0x46: retval = 0x71; break;
		case 0x47: retval = 0x3d; break;
		case 0x48: retval = 0x76; break;
		case 0x49: retval = 0x30; break;
		case 0x4a: retval = 0x1e; break;
		case 0x4b: retval = 0x75; break;
		case 0x4c: retval = 0x38; break;
		case 0x4d: retval = 0x37; break;
		case 0x4e: retval = 0x54; break;
		case 0x4f: retval = 0x3f; break;
		case 0x50: retval = 0x73; break;
		case 0x51: retval = 0x67; break;
		case 0x52: retval = 0x50; break;
		case 0x53: retval = 0x6d; break;
		case 0x54: retval = 0x78; break;
		case 0x55: retval = 0x3e; break;
		case 0x56: retval = 0x0c; break;
		case 0x57: retval = 0x7e; break;
		case 0x58: retval = 0x46; break;
		case 0x59: retval = 0x6e; break;
		case 0x5a: retval = 0x5b; break;
		case 0x5b: retval = 0x39; break;
		case 0x5c: retval = 0x64; break;
		case 0x5d: retval = 0x0f; break;
		case 0x5e: retval = 0x23; break;
		case 0x5f: retval = 0x08; break;
		case 0x60: retval = 0x03; break;
		case 0x61: retval = 0x77; break;
		case 0x62: retval = 0x7c; break;
		case 0x63: retval = 0x58; break;
		case 0x64: retval = 0x5e; break;
		case 0x65: retval = 0x79; break;
		case 0x66: retval = 0x71; break;
		case 0x67: retval = 0x3d; break;
		case 0x68: retval = 0x74; break;
		case 0x69: retval = 0x04; break;
		case 0x6a: retval = 0x0e; break;
		case 0x6b: retval = 0x7a; break;
		case 0x6c: retval = 0x38; break;
		case 0x6d: retval = 0x37; break;
		case 0x6e: retval = 0x54; break;
		case 0x6f: retval = 0x5c; break;
		case 0x70: retval = 0x73; break;
		case 0x71: retval = 0x67; break;
		case 0x72: retval = 0x50; break;
		case 0x73: retval = 0x6d; break;
		case 0x74: retval = 0x78; break;
		case 0x75: retval = 0x1c; break;
		case 0x76: retval = 0x0c; break;
		case 0x77: retval = 0x7e; break;
		case 0x78: retval = 0x46; break;
		case 0x79: retval = 0x6e; break;
		case 0x7a: retval = 0x5b; break;
		case 0x7b: retval = 0x46; break;
		case 0x7c: retval = 0x30; break;
		case 0x7d: retval = 0x70; break;
		case 0x7e: retval = 0x01; break;
		case 0x7f: retval = 0x00; break;
		default:   retval = 0x00;		// empty space for non-printing character
	}
	return retval;
}

static byte tm1638_numval(byte num)
{
	byte retval;
	switch(num)
	{
		case 0x0: retval = 0x3f; break;
		case 0x1: retval = 0x06; break;
		case 0x2: retval = 0x5b; break;
		case 0x3: retval = 0x4f; break;
		case 0x4: retval = 0x66; break;
		case 0x5: retval = 0x6d; break;
		case 0x6: retval = 0x7d; break;
		case 0x7: retval = 0x07; break;
		case 0x8: retval = 0x7f; break;
		case 0x9: retval = 0x6f; break;
		case 0xa: retval = 0x77; break;
		case 0xb: retval = 0x7c; break;
		case 0xc: retval = 0x58; break;
		case 0xd: retval = 0x5e; break;
		case 0xe: retval = 0x79; break;
		case 0xf: retval = 0x71; break;
		default:  retval = 0x49;		// three horizontal bars for error
	}
	return retval;
}

void tm1638_sendbyte( byte data )
{
    unsigned int index;

    //SetGpioFunction( DISP_DIO, GPIO_OUT );
    SetGpio( DISP_CLK, 1 );
    disp_delay();
    for( index=0; index<8; index++ )
    {
        SetGpio( DISP_DIO, data & 0x1 );
        SetGpio( DISP_CLK, 0 );
        disp_delay();
        SetGpio( DISP_CLK, 1 );
        disp_delay();
        data >>= 1;
    }
}

byte tm1638_readbyte()
{
    byte index;
    byte data;
    data = 0;
    
    SetGpioFunction( DISP_DIO, GPIO_IN );
    SetGpio( DISP_CLK, 1 );
    disp_delay();
    for( index=0; index<8; index++ )
    {
        data <<= 1;
        SetGpio( DISP_CLK, 0 );
        disp_delay();
        data |= ReadGpio( DISP_DIO );
        SetGpio( DISP_CLK, 1 );
        disp_delay();
    }
    return data;
}

void tm1638_init()
{
    SetGpioFunction( DISP_DIO, GPIO_OUT );
    SetGpio( DISP_DIO, 0 );
    SetGpioFunction( DISP_CLK, GPIO_OUT );
    SetGpio( DISP_CLK, 1 );
    SetGpioFunction( DISP_STB, GPIO_OUT );
    SetGpio( DISP_STB, 1 );
    disp_delay();

	tm1638_beginsend();
	tm1638_sendbyte( 0b01000000 ); // Data instruction, data write, autoincrement, not test mode
	tm1638_endsend();
	tm1638_beginsend();
    tm1638_sendbyte( 0b10001010 ); // Display control, display on, brightness 4/16
	tm1638_endsend();
}

void tm1638_beginsend()
{
    SetGpio( DISP_STB, 0 );
    disp_delay();
}

void tm1638_endsend()
{
	SetGpio( DISP_STB, 1 );
    disp_delay();
}

// Displays a number, left-justified, no leading zeros, beginning at specified
// position and extending to the right
void tm1638_displaynumber(unsigned int num, unsigned int pos)
{
	byte control_byte;
	unsigned int nums_to_send;
	
	nums_to_send = 8;
	// Shift left to skip leading zeros
	while( ((num & 0xf0000000) == 0) && (num != 0) )
	{
		num <<= 4;
		nums_to_send--;
	}
	
	if( pos >= 8 )
	{
		pos = 0;
	}
	if( nums_to_send == 0 )
	{
		nums_to_send = 1;
	}
	
	// Use do-while loop to make sure we send one character even if the input is zero
	do
	{
		tm1638_beginsend();
		// Double pos because 7-segment displays are on even addresses
		control_byte = 0xc0 | ((pos * 2) & 0xf);
		tm1638_sendbyte( control_byte );
		tm1638_sendbyte( tm1638_numval( num >> 28 ) );
		tm1638_endsend();
		
		num <<= 4;
		pos++;
		nums_to_send--;
	}while( (pos <= 8*2) && (nums_to_send > 0) ); 
}

void tm1638_clear()
{
	tm1638_displaystring("        ", 0);
}

// Displays a string, left-justified, beginning at specified position and
// extending to the right
void tm1638_displaystring(char* data, unsigned int pos)
{
	byte control_byte;
	
	if( pos >= 8 )
	{
		pos = 0;
	}
	
	while( (data[pos] != '\0') && (pos <= 8) )
	{
		tm1638_beginsend();
		// Double pos because 7-segment displays are on even addresses
		control_byte = 0xc0 | ((pos * 2) & 0xf);
		tm1638_sendbyte( control_byte );
		tm1638_sendbyte( tm1638_charval( data[pos] ) );
		tm1638_endsend();

		pos++;
	}
}

































