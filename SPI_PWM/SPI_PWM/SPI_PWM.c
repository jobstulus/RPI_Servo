/*
 * SPI_PWM.c
 *
 * Created: 28.11.2012 07:56:43
 *  Author: sjobstm
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#define PORTD_MASK ((1 << PD5)|(1 << PD6))

#define CH0_SET (pinlevelD |= (1 << PD5)) // map CH0 to PD5
#define CH1_SET (pinlevelD |= (1 << PD6)) // map CH1 to PD6

//! global buffers
uint16_t compare[2];
volatile uint16_t compbuff[2];


union unifier{
	uint16_t whole_input;
	uint8_t  spare_input[2];
} ;
	
typedef struct {
	union unifier val;
	uint8_t channel;
}
input_t;


int main(void)
{
	//initiating PWM-Timer-Outputs and SPI PINS
	DDRB |=
	(1<<PB4) ;	// MISO
	
	DDRB &=
	~(1<<PB5) &	// SCK
	~(1<<PB3) &	// MOSI
	~(1<<PB2);	// *SS
	
	
	DDRD |= PORTD_MASK;
	
	//initiating SPI-Bus
	
	SPCR |= 
	(1<<SPIE) |	//Interrupt Enable
	(1<<SPE);	//Enable SPI
	
	//initiating Timers
	
	
	
	//enable all interrupts
	sei();
	 
	//init
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

ISR(SPI_STC_vect)
{
	input_t receive;
	static uint8_t word_check = 2;
	uint8_t fetch = 0;
	
	//if(word_check <= 1)
	//receive.val.spare_input[word_check] = SPDR;
	//
	//if(word_check == 2)
	//
	//
		//
	//if(word_check > 2)
	//{
		//fetch = SPDR;
		//if(fetch == 0xAA)
		//word_check = 0;
	//}
	//
	switch (word_check)
	{
	case 0:
		receive.val.spare_input[0] = SPDR;
		word_check++;
		break;
	case 1:
		receive.val.spare_input[1] = SPDR;
		word_check++;
		break;
	case 2:
		receive.channel = SPDR;
		word_check++;
		break;
	default:
		fetch = SPDR;
		if(fetch == 0xAA)
		word_check = 0;
	}
	
}

ISR(TIMER0_OVF_vect)
{
	static uint8_t pinlevelD = 0x00;
	static uint16_t softcounter = 625;
	
	PORTD = pinlevelD;            // update outputs
	
	if(--softcounter == 0)
	{
		compare[0] = compbuff[0];
		compare[0] = compbuff[1];
	
		pinlevelD &= ~PORTD_MASK;     // set all port pins high	
		
		softcounter = 625;
	}
	
	// clear port pin on compare match (executed on next interrupt)
	if(compare[0] == softcounter) CH0_SET;
	if(compare[1] == softcounter) CH1_SET;
}