#include "kernel.h"

int main() {
	s_init();
	
	s_putsln('CASSIE KERNEL V1',16);

	while( 1 ){
		uint8_t k = s_get_key();
		switch (k){
			case 0:
				break;
			case 1:
				s_call_program( 0x1000 );
			default:
				// do nothing
		}
	}
}

void s_init(){
	// do nothing
}

void s_puts( char c ){
	// write character
}

void s_putsln( char * string, uint8_t len ){
	for (uint8_t i = 0; i < len; i++){
		s_puts( string[i] );
	}
}

uint8_t s_get_key {
	// read key from port zero 
	// return key
	return 0;
}

void s_call_program( uint8_t address ){
	// jump to address
}