/*
    Kernel for CASSIE-1 Version 0
    s_init() must be first call
*/

#include <stdint.h>
#include <stdbool.h>

#define S_WIDTH 1024
#define S_HEIGHT 576
#define NUM_K_TEXTURES 66

#ifndef SDCC
    #include <SFML/Graphics.h>
    sfTexture * k_textures[NUM_K_TEXTURES];
#endif // SDCC

// wrapper calls
void k_put_text(char * stringin, int x, int y);
void k_put_rect(int tex_id, int x, int y);
void k_put_rects(int tex_id, int x, int y, int w, int h);
void k_init_gfx();
bool k_this_close_request();
void k_refresh_display();
bool k_get_events();
void k_display();
int k_get_key();

// private calls
void _call( uint8_t address );
void _set_bank( uint8_t address );
void _write_io( uint8_t address, uint8_t data );
uint8_t _read_io( uint8_t address );
void _idle( uint8_t interrupt, bool go_to_bank_zero );    // enters into infinite loop with interrupt at supplied address
void _disk_write( long data );

// kernel state calls
void s_init( void );
void s_exit( void );
void s_call_program( uint8_t address );

// configure calls
void s_int_uart( bool yes );
void s_int_keyboard( bool yes );
void s_int_disk( bool yes );
void s_start_command( bool yes );

// display calls
uint8_t s_get_key( void );
void s_putc( char c );
void s_puts( char * s, uint8_t lenght );
void s_putsln( char * s, uint8_t lenght );

// video calls
void s_vidc( char c );
void s_vids( char * s, uint8_t lenght );
void s_vidsln( char * s, uint8_t lenght );
void s_set_font( uint8_t font );

// disk calls
void s_disk_write_1k( uint8_t pointer, char * filename);
void s_disk_read_1k( uint8_t pointer, char * filename);
void s_disk_write_2k( uint8_t pointer, char * filename);
void s_disk_read_2k( uint8_t pointer, char * filename);
void s_disk_write_bank( uint8_t bank, char * filename);
void s_disk_read_bank( uint8_t bank, char * filename);
void s_disk_rename( char * filename, char * newname);

// uart calls
void s_tx ( uint8_t data );
uint8_t s_rx ( uint8_t data );

// time calls
bool s_is_vsync( void );
bool s_is_hsync( void );
uint16_t s_systime ( void );
void s_config_timer( bool interrupt, uint8_t delay );
uint16_t s_timer ( void );
void s_reset_timer ( void );

// random generation calls
uint8_t s_rand( void );
void s_pseed ( long seed );
uint8_t s_prand ( void );
