//#include <SFML/Graphics.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} coord_t;

/*
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
*/

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
    unsigned int num; // if type == 0 then this is the target map_id to dock to;
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
    int x;
    int y;
    item_t items[16];
    int num_items;
} chest_t;

typedef struct {
    item_t item;
    int x;
    int y;
    int mapid;
} d_item_t;

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
    int inventory_size; // do we need this? I think yes
    npc_item_t inventory [16]; // make to a fixed size? npcs probably dont need to have working inventories
    bool is_merchant;
    bool is_ablaze;
    bool is_alive;
    int quest_id; // 0 for no quest, negative numbers trigger cutscene of corresponding number but positive
    int x;
    int y;
    int frame_id;
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
    int * map_dat;
    tile_data * tile_dat; // there must always be ten of these
    int w;
    int h;
} s_map;

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
    item_t item_reward;
    int * data;
    int * verify_id;
    int * action_id;
    int * bitmap_references;
    int * text_references;
} mquest_t;

typedef struct {
    mquest_t quest;
    int position;
} mquest_a_t;

typedef struct {
    int id;
    int num_frames;
    int frame;
    int * delay_per_frame;
    int first_frame_id;
    int * text_reference;
} cutscene_t;


// portal definition function
typedef portal_t (*portal_function_ft) (unsigned int x, unsigned int y);

// enemy definition function
typedef void (*enemy_function_ft) (entity_t * entity, int index);

// validate function definition
typedef bool (*quest_validate_function_ft) (void);

// action function definition
typedef bool (*quest_action_function_ft) (void);

// chest definition function
typedef chest_t (*chest_function_ft) (unsigned int x, unsigned int y);

typedef int module_t;

// map sizing
#define WIDTH 50
#define HEIGHT 35

// screen sizing
#define S_WIDTH 1024
#define S_HEIGHT 576

// number of maps
#define NUM_MAPS 3

// number of space maps
#define NUM_LEVELS 4

// max number of loaded modules
#define NUM_MODULES_MAX 16

// maximum size of player inventory
#define NUM_ITEMS_MAX 16

// maximum number of dropped items across all maps
#define NUM_DROPPED_MAX 32

// define maximum number of hidden NPCS
#define NUM_HIDDEN_NPCS_MAX 8

#define NUM_CHESTS_MAX 18

// number of quests (moved to quest.c)
#define NUM_QUESTS_MAX 1

// number of cutscenes
#define NUM_CUTSCENES 1

// entity timing constants "milliseconds"
#define TIME_CHARACTER 50 // was 760 --> 380
#define TIME_ENTITY 500
#define TIME_ROCKET 100

// max entities
#define MAX_ENTITIES 32

// length of quest text data
#define QUEST_STR_DAT_LEN 145

// length of cutscene text data
#define CUTSCENE_STR_DAT_LEN 160

#define CONFIG_INCREMENT_AMOUNT 50

// game state
extern int state;

extern int notifications;

// timing for entities
extern double timerval;
extern double time_entity;
extern int time_character;
extern int time_entity_o;
extern int time_character;
extern int time_rocket;

// timing for cutscenes
extern int time_cutscene;
extern cutscene_t current_cutscene;
extern cutscene_t cutscene_registry[NUM_CUTSCENES];

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

extern d_item_t dropped_items[NUM_DROPPED_MAX];
extern int num_dropped_items;

extern int hidden_npcs[NUM_HIDDEN_NPCS_MAX];
extern int num_hidden_npcs;

// rogue-like entities
extern int num_entities;
extern int num_entities_o;
entity_t entities[32];

// space entities
o_entity_t entities_o[32];
extern int id_entity_last;

// for going to quest/cutscene/etc mode
extern npc_t npc_last;
extern int trade_index;
extern int selected_module;
extern int selected_object;

// map stuffs
extern map_t cached_map; // map for use when walkin around, needs to be loaded when player moves around
extern int master_index; // current map id (index inside rogue_map_master
extern map_master rogue_map_master[ NUM_MAPS ]; // main registry of maps
extern npc_function_ft rogue_npc_master[NUM_MAPS]; // main registry of NPCs (this is an array of pointers to functions)
extern portal_function_ft rogue_portal_master[NUM_MAPS];
extern enemy_function_ft rogue_enemy_master[NUM_MAPS];
extern chest_function_ft rogue_chest_master[NUM_MAPS];
extern int chests_consumed[NUM_CHESTS_MAX];
extern int quests_consumed[NUM_QUESTS_MAX];

extern mquest_t quest_registry[ NUM_QUESTS_MAX + 1];
extern int num_active_quests;
extern mquest_a_t quest_a_registry[ NUM_QUESTS_MAX + 1];
extern char quest_str_dat [ QUEST_STR_DAT_LEN ];

char cutscene_str_dat [ CUTSCENE_STR_DAT_LEN ];

extern quest_validate_function_ft quest_validate_master[NUM_QUESTS_MAX + 1];
extern quest_action_function_ft quest_action_master [NUM_QUESTS_MAX + 1];

extern int modules_enabled[NUM_MODULES_MAX];

// reads quest, level, npc, map data from file
bool build_game_data();

// stuff for space part of game
extern int sector_x;
extern int sector_y;
extern int sector_s;
extern int level; // level id for space view
extern bool tilted; // check for angled movement
extern int facing;

// engine data
extern int flux;
extern int fuel_r;
extern int durability;
extern int response;
extern int flux_clamp;
extern int emission_clamp;
extern int themal_clamp;

// ship data
extern float vx;
extern float vy;
extern int thrust_clamp;
extern int afterburn_clamp;
extern float thrust;
extern int ship_x;
extern int ship_y;

// engine stress values (can this be made private?? or in a struct??)
extern int e1_g;
extern int e1_y;
extern int e2_g;
extern int e2_y;
extern int e3_g;
extern int e3_y;
extern int e4_g;
extern int e4_y;

extern int ticks_for_warp;

// map definitions
extern s_map level_master[NUM_LEVELS];

// texture names
#define DEBUG_TEX           9
#define SPAWN_TEX           9
#define BLACK_TEX           3
#define HEART_TEX           24
#define CRITICAL_TEX        28
#define FULL_HEALTH_TEX     27
#define BRONZE_TEX          25
#define FLOOR_TEX           23
#define WALL_TEX            42
#define FERN_TEX            19
#define SYSTEM_TEX          41
#define NPC_TEX             34
#define GREEN_TEX           26
#define LOGO_TEX            32
#define TURRET_TEX          45
#define BULLET_TEX          46
#define FIRE_TEX            44
#define CRATE_TEX           47
#define PORTAl_TEX          48
#define PLANTS_TEX          49
#define SPLANTS_TEX         50
#define MACHINERY_TEX       52
#define ENEMY_TEX           53
#define WATER_TEX           54
#define OMACHINERY_TEX      51
#define FLOOR_ALT_TEX       55
#define GAME_OVER_TEX       56
#define GUN_ITEM_TEX        57
#define FOOD_ITEM_TEX       58
#define MEDKIT_ITEM_TEX     59
#define WRENCH_ITEM_TEX     60
#define BULLET_ITEM_TEX     61
#define GRENADE_ITEM_TEX    62
#define BOOK_ITEM_TEX       63
#define MG_ITEM_TEX         64
#define RL_ITEM_TEX         65
#define PICK_ITEM_TEX       66
#define RED_TEX             37
#define YELLOW_TEX          43
#define ICE_FEILD_TEX       30
#define ICE_STATION_TEX     31
#define STATION_TEX         40
#define NEBULA_TEX          33
#define C_U_TEX             8
#define C_R_TEX             6
#define C_D_TEX             5
#define C_L_TEX             7
#define E_U_TEX             15
#define E_R_TEX             17
#define E_D_TEX             18
#define E_L_TEX             16
#define ASTEROID_TEX        1
#define DEBRIS_TEX          22
#define ROCKET_TEX          37
#define MODULE_TEX          68
#define WELDER_TEX          72
#define TNT_TEX             69
#define TURRET_ITEM_TEX     70
#define DRILL_TEX           71
#define GOLD_TEX            4
#define PURPLE_HEART_TEX    36
#define SILVER_TEX          39
#define PLATINUM_TEX        35
#define FUEL_ITEM_TEX       73
#define GRID_BG_TEX         10
