#include <SFML/Graphics.hpp>

struct item_npc{
    int id;
    int type;
    char * data;
    int data_len;
};

struct NPC{
    int id;
    int health; // of 1000
    int type;
    int inventory_size;
    const item_npc * inventory; // make to a fixed size? npcs probably dont need to have working inventories
    bool is_merchant;
    bool is_ablaze;
    bool is_alive;
};

struct map_tile{
    int type;
    bool fire;
    bool has_NPC;
    NPC resident;
};

// flavor text
struct flavor_text {
    char personnell[16];
    int weight;
    char alignment[16];
};

// for flight level view
struct level_data {
    int x;
    int y;
    char data[16];
    bool persistent;
    int type;
    unsigned int num;
    bool map_exists;
    int map_id;
    int map_w;
    int map_h;
};

// for info on each tile in sector
struct tile_data {
    int x;
    int y;
    char data[16];
    int num_level_data;
    const level_data * flight_data;
};

struct entity{
    int x;
    int y;
    int vx;
    int vy;
    char data[16];
    int type; // 0 = station, 1 = asteroid, 2 = enemy, 3 = debris, 4 = ice station, 6 = planet, 5 = rocket (player), 6 = rocket (other)
    int id;
};

struct item{
    int id;
    int type;
    bool unuseable;
    char data[10];
    int data_len;
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
extern int ship_x;
extern int ship_y;
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
extern int level; // level id for space view
extern int location; // location on level for rouge: -1 for none loaded
extern item inventory[]; // inventory list
extern int num_items;    // number of items

// check for angled movement
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

// ???
extern int selected_object;

// main window texture handle
extern sf::RenderTexture windowTexture;

// main font handle
extern sf::Font font;

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

// map definitions
extern const int level_0_0[10][10];
extern const tile_data level_0_0_tile_data[10];
extern const int level_0_1[10][10];
extern const tile_data level_0_1_tile_data[10];
extern const int level_0_2[10][10];
extern const tile_data level_0_2_tile_data[10];
extern const int level_0_3[10][10];
extern const tile_data level_0_3_tile_data[10];

extern const int map_test[32][32];
