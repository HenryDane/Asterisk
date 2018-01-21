# Mapping guide
## Map definitions
A map is built out of the following:
- One or more instances of `map_t` bundled together in an array, such as `debug_map`. 
- One function returning `npc_t` given two inputs `unsigned int x` and `unsigned int y` labelled with the same name as the array of type `map_t` but with `_npc` at the end. An example of this would be `npc_t debug_map_npc ( unsigned int x, unsigned int y );`
- One function returning `portal_t` given two inputs `unsigned int x` and `unsigned int y` labelled with the same name as the array of type `map_t` but with `_portal` at the end. An example of this would be `portal_t` debug_map_portal ( unsigned int x, unsigned int y );`
- One variable returning `coord_t` which returns the starting point for the character. This should be named in the style of the two functions but the ending should be `_start`.

All maps are of a maximum size of 255 by 255 and should be hardcoded. All variables not used in the functioned or returned should be `const`.

Example definition for `example_map`:
```
const map_t example_map[] = {4,
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
    npc_t a = {1432, 988, 7, 1, {5763, 42, "Legendary", 9}, true, false, true };
    npc_t b = {-1, 0, 0, 0, {-1, 0, ' ', 0}, false, false, false };
    if (x == 2 && y == 3){
        return a;
    }
    return b;
}
```

## Types 
NPC:
- 0 or less: null
- 988: Example NPC

Map:
- 0: Metal floor
- 1: Wall
- 2: Plants (non-solid)