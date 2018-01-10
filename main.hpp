#include <SFML/Graphics.hpp>

struct entity{
    int x;
    int y;
    int vx;
    int vy;
    char data[16];
    int type; // 0 = station, 1 = asteroid, 2 = enemy, 3 = debris, 4 = ice station, 6 = planet, 5 = rocket (player), 6 = rocket (other)
    int id;
};

#define CONFIG_INCREMENT_AMOUNT 50

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
#define TIME_ROCKET 200

// max entities
#define MAX_ENTITIES 64

// timing
extern double timerval;
extern double time_character;
extern double time_entity;
extern double time_rocket;

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

extern bool tilted;

// engine data
extern int flux;
extern int fuel_r;
extern int durability;
extern int respons;
extern int flux_clamp;
extern int emission_clamp;
extern int themal_clamp;

// ship data
extern float vx;
extern float vy;
extern float vz;
extern float x;
extern float y;
extern float z;
extern int thrust_clamp;
extern int afterburn_clamp;
extern float thrust;

extern int selected_object;

// main window texture handle
extern sf::RenderTexture windowTexture;

// game state
extern int state;

// engine stuff
extern int e1_g;
extern int e1_y;
extern int e2_g;
extern int e2_y;
extern int e3_g;
extern int e3_y;
extern int e4_g;
extern int e4_y;
