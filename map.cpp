#include "main.hpp"

// EXAMPLE MAP DEF
const map_t example_map = {4,
                             4,
                            {0, 0, 0, 0,
                             0, 1, 2, 1,
                             0, 0, 1, 0,
                             1, 0, 0, 2},
                            {false, false, false, false,
                             false, false, false, false,
                             false, true, false, false,
                             false, false, false, false},
                            {true, false, false, false,
                             false, false, false, false,
                             false, false, false, false,
                             false, false, false, false} };
const coord_t example_map_start = {3, 2};
npc_t example_map_npc ( unsigned int x, unsigned int y ){
    npc_t a = {1432, 988, 7, 1, {5763, 42, "Legendary", 9}, false, false, true, 1, 1, 0 };
    npc_t b = {-1, 0, 0, 0, {-1, 0, ' ', 0}, false, false, false, 0, -1, -1};
    if (x == 2 && y == 3){
        return a;
    }
    return b;
}

// TEST MAP DEF
const map_t test_map = {6,
                        6,
                       {0, 0, 0, 0, 5, 0,
                        0, 1, 2, 1, 5, 0,
                        0, 0, 1, 0, 0, 5,
                        1, 0, 0, 2, 5, 2,
                        0, 0, 0, 5, 5, 5,
                        5, 0, 0, 0, 3, 0 },
                       {false, false, false, false,
                        false, false, false, false,
                        false, true, false, false,
                        false, false, false, false},
                       {true, false, false, false,
                        false, false, false, false,
                        false, false, false, false,
                        false, false, false, false} };
const coord_t test_map_start = {3, 2};
npc_t test_map_npc ( unsigned int x, unsigned int y ){
    npc_t a = {9107, 988, 7, 1, {5763, 42, "Legendary", 9}, true, false, true, 1, 5, 5 };
    npc_t b = {-1, 0, 0, 0, {-1, 0, ' ', 0}, false, false, false, 0, -1, -1 };
    if (x == 2 && y == 3){
        return a;
    }
    return b;
}

// stuff involving maps lol
int master_index = 0;
map_t cached_map = example_map;

// set up master record for maps
map_master rogue_map_master[NUM_MAPS] = {{ example_map, example_map_start }, { test_map, test_map_start } }  ;

// set up master record for NPC functions
npc_function_ft rogue_npc_master[NUM_MAPS] = {example_map_npc, test_map_npc};

void init_maps(){
    // do nothing
}
