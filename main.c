#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <stdint.h>

//LEDS
#define R PB0
#define B PB1
#define G PB2
#define Y PB4

uint8_t ledport[56] = { 0 };
uint8_t reg = 125;
uint8_t led = 126;
uint8_t mod = 1;

int main (void){

	ADCSRA = 0;
	power_all_disable();

	//set port dir
	DDRB |= _BV(R);
	DDRB |= _BV(B);
	DDRB |= _BV(G);
	DDRB |= _BV(Y);

	for(;;){
		for(uint8_t i=0; i<56; i++){
			PORTB = ledport[i];
			_delay_us(3);
			
		}
		PORTB=0;
		_delay_ms(6);
		mod++;
		if(!mod){
			reg ^= (reg << 7);
			reg ^= (reg >> 5);
			reg ^= (reg << 3);
			led ^= (led << 7);
			led ^= (led >> 5);
			led ^= (led << 3);
			ledport[reg%48] = ledport[reg%48] ^ (1 << (led%5));
		}
	}
}

