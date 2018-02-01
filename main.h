#include <SFML/Graphics.h>

// because C is annoying
typedef enum { false, true } bool;

// because CSFML
extern sfRenderWindow* window;
extern sfFont* font; // needs to be loaded in main

typedef struct {
    int x;
    int y;
} coord_t;

typedef struct {
    int id;
    int type;
    bool unuseable;
    char data[10];
    int data_len;
} item_t;

// does not yet support giving/taking items
typedef struct {
    char * data;
    int dat_len;
    int image_id; // -1 for black, 0 for no change
} quest_dialogue_t;

// function pointer typedefs
typedef bool (*quest_validate_ft) (void); // checks if step is complete
typedef void (*quest_assign_ft) (void); // assigns step (may do nothing)

typedef struct {
    int id; // must be positive
    quest_dialogue_t * dialogue_list; // length of list must be same as num_dialogue
    int num_dialogue; //
} quest_dialogue_block_t;

typedef struct {
    int id;
    char title[32];
    int title_len;
    char issuer[32];
    int issuer_len;
    quest_dialogue_block_t * dialogue;
    quest_validate_ft * validation_functions; // length of list must be same as num_stages
    quest_assign_ft * assignment_functions; // length of list must be same as num_stages
    int num_stages;
    int reward_exp;
    int reward_credits;
    item_t reward_item;
} quest_t;

typedef struct {
    quest_t quest;
    int block_index;
    bool complete; // if true, will be removed at some point
} quest_active_t;

typedef struct {
    int id;
    int type;
    char data [16];
    int data_len; // could be one byte
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
    int tile_type [32 * 32]; // can be one byte (if negative then is portal to another area)
    bool on_fire [32 * 32];
    bool under_water [32 * 32];
} map_t;


typedef struct {
    map_t mapdat;
    coord_t coord;
} map_master;

// flavor text
typedef struct {
    char personnell[16];
    int weight;
    char alignment[16];
} flavor_text;

// map sizing
#define WIDTH 50
#define HEIGHT 35

// screen sizing
#define S_WIDTH 1024
#define S_HEIGHT 576

// number of maps
#define NUM_MAPS 2

// define texture data
#define NUM_TEXTURES 43

// number of quests
#define NUM_QUESTS 1
#define NUM_QUESTS_MAX 4

// entity timing constants milliseconds)
#define TIME_CHARACTER 760
#define TIME_ENTITY 1000
#define TIME_ROCKET 200

// max entities
#define MAX_ENTITIES 64

// timing
extern double timerval;
extern double time_entity;

// maps
extern int mapdata[HEIGHT][WIDTH];
extern int screen[];

// character attrs
extern int character_x;
extern int character_y;
extern int facing;
extern int health;
extern float experience;
extern int fuel;
extern int rounds;
extern int credits;
extern int level; // level id for space view
extern int location; // location on level for rouge: -1 for none loaded
extern item_t inventory[]; // inventory list
extern int num_items;    // number of items

// ???
extern int selected_object;

// game state
extern int state;

// for going to quest/cutscene/etc mode
extern npc_t npc_last;

// map stuffs
extern map_t cached_map; // map for use when walkin around, needs to be loaded when player moves around
extern int master_index; // current map id (index inside rogue_map_master
extern map_master rogue_map_master[ NUM_MAPS ]; // main registry of maps
extern npc_function_ft rogue_npc_master[NUM_MAPS]; // main registry of NPCs (this is an array of pointers to functions)

// quest stuffs
extern quest_active_t active_quests [NUM_QUESTS_MAX]; // list of active quests
extern int num_active_quests;
extern quest_t quest_registry[ NUM_QUESTS + 1 ];

// cutscene stuffs
// nothing to see yet

// reads quest, level, npc, map data from file
bool build_game_data();
