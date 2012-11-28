/*
 * SPI_PWM.c
 *
 * Created: 28.11.2012 07:56:43
 *  Author: sjobstm
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	//initiating PWM-Timer-Outputs and SPI PINS
	DDRB |=
	(1<<PB4) |	// MISO
	(1<<PB1);	// OC1A
	
	DDRB &=
	~(1<<PB5) &	// SCK
	~(1<<PB3) &	// MOSI
	~(1<<PB2);	// *SS
	
	
	DDRD |=
	(1<<PD6) |	// OC0A
	(1<<PD5) |	// OC0B
	(1<<PD3);	// OC2B
	
	//initiating SPI-Bus
	
	SPCR |= 
	(1<<SPIE) |	//Interrupt Enable
	(1<<SPE);	//Enable SPI
	
	//initiating Timers

	
	
	
	
	
	//init
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

ISR(SPI_STC_vect)
{
	uint8_t test;
}

