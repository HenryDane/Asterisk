//#include <SFML/Graphics.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} coord_t;

typedef struct {
    int id;
    int x;
    int y;
    int vx;
    int vy;
    int type;
} entity_t;

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

// ???
extern int selected_object;

// game state
extern int state;

extern int num_entities;
entity_t entities[32];

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
