#include <SFML/Graphics.hpp>

struct entity{
    int x;
    int y;
    int vx;
    int vy;
    char data[16];
    int type; // 0 = station, 1 = asteroid, 2 = enemy, 3 = debris, 4 = ice station, 6 = planet
    int id;
};

#define PAD_LEFT 128
#define PAD_RIGHT 128
#define PAD_BOTTOM 128
#define PAD_TOP 128

// map sizing
#define WIDTH 50
#define HEIGHT 35

// screen sizing
#define S_WIDTH 1024
#define S_HEIGHT 576

// entity timing constants milliseconds)
#define TIME_CHARACTER 760
#define TIME_ENTITY 1000

// max entities
#define MAX_ENTITIES 64

// timing
extern double timerval;
extern double time_character;
extern double time_entity;

// entity defs
extern entity entities[MAX_ENTITIES];
extern int num_entities;
extern int id_entity_last;

// maps
extern int mapdata[HEIGHT][WIDTH];
extern int screen[];

// character attrs
extern int character_x;
extern int character_y;
extern int dx; // for moving towards the edge of the screen
extern int dy; // for moving towards the edge of the screen
extern int facing;
extern int health;
extern float experience;
extern int fuel;
extern int rockets;
extern int rounds;
extern int credits;
extern int sector_x;
extern int sector_y;
extern int sector_s;
extern int level;


// main window texture handle
extern sf::RenderTexture windowTexture;

// game state
extern int state;
