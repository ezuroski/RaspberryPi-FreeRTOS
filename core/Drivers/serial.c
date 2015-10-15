#include "serial.h"

typedef struct {
	unsigned long	AUX_ENB;	//0x20215004
	unsigned long	Reserved_1[14];
	unsigned long	AUX_MU_IO; 	//0x20215040
	unsigned long	Reserved_2[2];
	unsigned long	AUX_MU_LCR;	//0x2021504c
	unsigned long	Reserved_3;
	unsigned long	AUX_MU_LSR;	//0x20215054
	unsigned long	Reserved_4[2];
	unsigned long	AUX_MU_CNTL;//0x20215060
	unsigned long	Reserved_5;
	unsigned long	AUX_MU_BAUD;//0x20215068
} BCM2835_SERIAL_REGS;

static volatile BCM2835_SERIAL_REGS * const pRegs = (BCM2835_SERIAL_REGS *) (0x20215004);


void serial_printtext( char* data )
{
	char* ptr = data;
	while( *ptr )
	{
		// Wait until the tx fifo is not full
		while( (pRegs->AUX_MU_LSR & (1<<5)) == 0 );
		pRegs->AUX_MU_IO = *ptr;
		ptr++;
	}
}

void serial_printnum( unsigned int data )
{
	// Keeping this one simple
	// Approximating printf %x
	unsigned int send_count;
	unsigned char send_data;
	send_count = 0;
	
	// Sending the most significant nibble first
	// Shift left to skip leading zeros
	while( ((data & 0xf0000000) == 0) && (send_count < 8) )
	{
		data <<= 4;
		send_count++;
	}

	// Use do-while loop to make sure we send one character even if the input is zero
	do
	{
		send_data = (data >> 28) & 0xf;
		
		// Wait until the tx fifo is not full
		while( (pRegs->AUX_MU_LSR & (1<<5)) == 0 );
		
		if( send_data < 10 )
		{
			pRegs->AUX_MU_IO = (send_data + '0');
		}
		else
		{
			pRegs->AUX_MU_IO = (send_data - 10 + 'a');
		}
		
		send_count++;
		data <<= 4;
	}while( send_count < 8 );
}
