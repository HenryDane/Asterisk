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
