//#include <SFML/Graphics.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} coord_t;

typedef struct {
    unsigned int w; // can be one byte
    unsigned int h; // can be one byte
    int tile_type [32 * 32]; // can be one byte (if negative then is portal to another area)
    bool on_fire [32 * 32];
    bool under_water [32 * 32];
} o_map_t;


typedef struct {
    const o_map_t mapdat;
    const coord_t coord;
} o_map_master;

// flavor text
struct {
    char personnell[16];
    int weight;
    char alignment[16];
} flavor_text;

// for flight level view
typedef struct {
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
} level_data;

// for info on each tile in sector
typedef struct {
    int x;
    int y;
    char data[16];
    int num_level_data;
    const level_data * flight_data;
} tile_data;

typedef struct {
    int id;
    int x;
    int y;
    int vx;
    int vy;
    int type;
} entity_t;

typedef struct {
    int x;
    int y;
    int vx;
    int vy;
    char data[16];
    int type; // 0 = station, 1 = asteroid, 2 = enemy, 3 = debris, 4 = ice station, 6 = planet, 5 = rocket (player), 6 = rocket (other)
    int id;
} o_entity_t;

typedef struct {
    int id;
    int type;
    bool unuseable;
    char data[16];
    int data_len;
} item_t;

typedef struct {
    int id;
    int type;
    char data [16];
    int data_len; // could be one byte
    int cost;
} npc_item_t;

typedef struct {
    int id; // -1 if the npc is null
    int health; // of 1000
    int type;
    int inventory_size;
    npc_item_t inventory [16]; // make to a fixed size? npcs probably dont need to have working inventories
    bool is_merchant;
    bool is_ablaze;
    bool is_alive;
    int quest_id; // 0 for no quest, negative numbers trigger cutscene of corresponding number but positive
    int x;
    int y;
} npc_t;

// function pointer typedefs
typedef npc_t (*npc_function_ft) (unsigned int x, unsigned int y); // gets npc at point

typedef struct  {
    unsigned int w; // can be one byte
    unsigned int h; // can be one byte
    int * tile_type; // can be one byte (if negative then is portal to another area)
    int num_entities;
    entity_t * entities;
} map_t;


typedef struct {
    map_t mapdat;
    coord_t coord;
} map_master;

typedef struct {
    int x;
    int y;
    int mapid;
} portal_t;


typedef struct {
    int id;
    char * title; // assemble to char title [len];
    char * issuer; // assemble to char issuer [len];
    int stages;
    int exp_reward;
    int credit_reward;
    item_t * item_reward;
    int * data;
    int * verify_id;
    int * action_id;
} mquest_t;

typedef struct {
    mquest_t quest;
    int position;
} mquest_a_t;

typedef portal_t (*portal_function_ft) (unsigned int x, unsigned int y);

// map sizing
#define WIDTH 50
#define HEIGHT 35

// screen sizing
#define S_WIDTH 1024
#define S_HEIGHT 576

// number of maps
#define NUM_MAPS 5

// define texture data
#define NUM_TEXTURES 43

// number of quests
#define NUM_QUESTS 1
#define NUM_QUESTS_MAX 4

// entity timing constants milliseconds
#define TIME_CHARACTER 760
#define TIME_ENTITY 1000
#define TIME_ROCKET 200

// max entities
#define MAX_ENTITIES 32

#define QUEST_STR_DAT_LEN 160

// timing
extern double timerval;
extern double time_entity;

// character attrs
extern int character_x;
extern int character_y;
extern int health;
extern float experience;
extern int fuel;
extern int rounds;
extern int credits;
extern int location; // location on level for rouge: -1 for none loaded
extern item_t inventory[]; // inventory list
extern int num_items;    // number of items
extern int score;

extern int time_character;
extern int time_entity_o;
extern int time_character;
extern int time_rocket;

// ???
extern int selected_object;

// game state
extern int state;

extern int num_entities;
extern int num_entities_o;
entity_t entities[32];

o_entity_t entities_o[32];
extern int id_entity_last;

// for going to quest/cutscene/etc mode
extern npc_t npc_last;

// map stuffs
extern map_t cached_map; // map for use when walkin around, needs to be loaded when player moves around
extern int master_index; // current map id (index inside rogue_map_master
extern map_master rogue_map_master[ NUM_MAPS ]; // main registry of maps
extern npc_function_ft rogue_npc_master[NUM_MAPS]; // main registry of NPCs (this is an array of pointers to functions)
extern portal_function_ft rogue_portal_master[NUM_MAPS];

extern mquest_t quest_registry[ NUM_QUESTS_MAX + 1];
extern int num_active_quests;
extern mquest_a_t quest_a_registry[ NUM_QUESTS_MAX + 1];
extern char quest_str_dat [ QUEST_STR_DAT_LEN ];

// cutscene stuffs
// nothing to see yet

// reads quest, level, npc, map data from file
bool build_game_data();

// stuff for space part of game
extern int sector_x;
extern int sector_y;
extern int sector_s;
extern int level; // level id for space view

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

// engine stuff
extern int e1_g;
extern int e1_y;
extern int e2_g;
extern int e2_y;
extern int e3_g;
extern int e3_y;
extern int e4_g;
extern int e4_y;

extern int facing;

extern int ship_x;
extern int ship_y;

// map definitions
extern const int level_0_0[10][10];
extern const tile_data level_0_0_tile_data[10];
extern const int level_0_1[10][10];
extern const tile_data level_0_1_tile_data[10];
extern const int level_0_2[10][10];
extern const tile_data level_0_2_tile_data[10];
extern const int level_0_3[10][10];
extern const tile_data level_0_3_tile_data[10];
