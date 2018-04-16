#include "main.h"
//#include "quest.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "kernel/kernel.h"

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

int g_state = 0;

int init_displays(void){
    return 0;
}

void cleardisplay(bool debug){
    char tim[80];
    int texid = 0;
    if (debug){
        texid = DEBUG_TEX;
    } else {
        texid = BLACK_TEX;
    }
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j <  HEIGHT; j++){
            k_put_rect(texid, i, j);
        }
    }
}

void display(bool update, int state){
    // clear display
    char tim[80];
    cleardisplay(false);

    int tex;

    // draw character
    switch(facing % 4){
        case 0: tex = C_U_TEX; break;
        case 1: tex = C_L_TEX; break;
        case 2: tex = C_D_TEX; break;
        case 3: tex = C_R_TEX; break;
        default: tex = DEBUG_TEX;
    }
    k_put_rect(tex, ship_x, ship_y);

    switch(facing % 4){
        case 0:
            k_put_rect(E_U_TEX, ship_x, ship_y + 1);
            break;
        case 1:
            k_put_rect(E_R_TEX, ship_x - 1, ship_y);
            break;
        case 2:
            k_put_rect(E_D_TEX, ship_x, ship_y - 1);
            break;
        case 3:
            k_put_rect(E_L_TEX, ship_x + 1, ship_y);
            break;
    }

    // draw entities
    for (int i = 0; i < num_entities_o; i++){
        if (entities_o[i].type >= 0){
            switch(entities_o[i].type){
                case 0:
                    k_put_rect(STATION_TEX, entities_o[i].x, entities_o[i].y);
                    break;
                case 1:
                    k_put_rect(ASTEROID_TEX, entities_o[i].x, entities_o[i].y);
                    break;
                case 2:
                    k_put_rect(ENEMY_TEX, entities_o[i].x, entities_o[i].y);
                    break;
                case 3:
                    k_put_rect(DEBRIS_TEX, entities_o[i].x, entities_o[i].y);
                    break;
                case 5:
                    k_put_rect(ROCKET_TEX, entities_o[i].x, entities_o[i].y);
                    break;
                default:
                    k_put_rect(DEBUG_TEX, entities_o[i].x, entities_o[i].y);
            }
        } else {
            k_put_rect(WALL_TEX, entities_o[i].x, entities_o[i].y);
        }
    }

    k_put_text("HEALTH: ", 51, 1);
    if (health >= 250){
        k_put_rect(HEART_TEX, 60, 1);
    } else {
        k_put_rect(CRITICAL_TEX, 60, 1);
    }
    if (health >= 500){
        k_put_rect(HEART_TEX, 59, 1);
    }
    if (health >= 750){
        k_put_rect(HEART_TEX, 58, 1);
    }
    if (health >= 900){
        k_put_rect(FULL_HEALTH_TEX, 57, 1);
    }

    k_put_text("RANK: ", 51, 2);
    k_put_rect(BRONZE_TEX, 57, 2);

    sprintf(tim, "FUEL: %d / 10K", fuel);
    k_put_text(tim, 51, 3);

    sprintf(tim, "SECT: %d", sector_s);
    k_put_text(tim, 51, 5);

    sprintf(tim, "COORD: (%d, %d)", sector_x, sector_y);
    k_put_text(tim, 51, 6);
}

void update_warp_interface(void){
    e1_g = rand() % 9;
    e1_y = 9;
    e2_g = rand() % 9;
    e2_y = 9;
    e3_g = rand() % 9;
    e3_y = 9;
    e4_g = rand() % 9;
    e4_y = 9;
}

void draw_engine_config(){
    k_put_text("Engine Configuration Window", 2, 2);
    k_put_text("E1", 2, 23);
    k_put_text("E2", 7, 23);
    k_put_text("E3", 12, 23);
    k_put_text("E4", 17, 23);
    int tex;
    for(int i = 0; i < 2; i++){
        for (int j = 0; j < 10; j++){
            if ( j >= e1_y) {
                tex = RED_TEX;
            } else if (j >= e1_g && j < e1_y){
                tex = YELLOW_TEX;
            } else {
                tex = GREEN_TEX;
            }
            k_put_rect(tex, 2 +  i, 25 + j);

            if ( j >= e2_y) {
                tex = RED_TEX;
            } else if (j >= e2_g && j < e2_y){
                tex = YELLOW_TEX;
            } else {
                tex = GREEN_TEX;
            }
            k_put_rect(tex, 7 + i, 25 + j);

            if ( j >= e3_y) {
                tex = RED_TEX;
            } else if (j >= e3_g && j < e3_y){
                tex = YELLOW_TEX;
            } else {
                tex = GREEN_TEX;
            }
            k_put_rect(tex, 12 + i, 25 + j);

            if ( j >= e4_y) {
                tex = RED_TEX;
            } else if (j >= e4_g && j < e4_y){
                tex = YELLOW_TEX;
            } else {
                tex = GREEN_TEX;
            }
            k_put_rect(tex, 17 + i, 25 + j);
        }
    }

    k_put_text("Flux:Fuel Ratio     [A][Q]", 2, 4);
    k_put_text("Dur.:Res. Ratio     [S][W]", 2, 7);
    k_put_text("Flux Clamp          [D][E]", 2, 10);
    k_put_text("Emission Clamp      [F][R]", 2, 13);
    k_put_text("Thermal Clamp       [G][T]", 2, 16);
    k_put_text("Engine Status:", 2,22);
    for (int i = 2; i < 20; i++){
        if(i - 1 < fuel_r / 55){
            tex = GREEN_TEX;
        } else {
            tex = RED_TEX;
        }
        k_put_rect(tex, i, 5);
        if(i - 1 < durability / 55){
            tex = GREEN_TEX;
        } else {
            tex = RED_TEX;
        }

        k_put_rect(tex, i, 8);
        if(i - 1 < flux_clamp / 55){
            tex = GREEN_TEX;
        } else {
            tex = RED_TEX;
        }

        k_put_rect(tex, i, 11);
        if(i - 1 < emission_clamp / 55){
            tex = GREEN_TEX;
        } else {
            tex = RED_TEX;
        }

        k_put_rect(tex, i, 14);
        if(i - 1 < themal_clamp / 55){
            tex = GREEN_TEX;
        } else {
            tex = RED_TEX;
        }
        k_put_rect(tex, i, 17);
    }
}

void draw_prewarp(int x, int y, int s){
    char tim[80];
    int tex;

    // pick default texture
    tex = BLACK_TEX;
    for (int i = 1; i < 11; i++){
        for (int j = 1; j < 11; j++){
            // draw sector 1
            switch(level_0_0[i - 1][j - 1]){
                case 0: tex = BLACK_TEX; break;
                case 1: tex = STATION_TEX; break; // staytion
                case 2: tex = ICE_FEILD_TEX; break; // ice field
                case 3: tex = NEBULA_TEX; break; // nebula
                case 4: tex = SYSTEM_TEX; break;
            }
            k_put_rect(tex, i, j);

            // draw sector 1
            switch(level_0_1[i - 1][j - 1]){
                case 0: tex = BLACK_TEX; break;
                case 1: tex = STATION_TEX; break; // staytion
                case 2: tex = ICE_FEILD_TEX; break; // ice field
                case 3: tex = NEBULA_TEX; break; // nebula
                case 4: tex = SYSTEM_TEX; break;
            }
            k_put_rect(tex, i + 11, j);

            // draw sector 3
            switch(level_0_3[i - 1][j - 1]){
                case 0: tex = BLACK_TEX; break;
                case 1: tex = STATION_TEX; break; // staytion
                case 2: tex = ICE_FEILD_TEX; break; // ice field
                case 3: tex = NEBULA_TEX; break; // nebula
                case 4: tex = SYSTEM_TEX; break;
            }
            k_put_rect(tex, i, j + 11);

            // draw sector 2
            switch(level_0_2[i - 1][j - 1]){
                case 0: tex = BLACK_TEX; break;
                case 1: tex = STATION_TEX; break; // staytion
                case 2: tex = ICE_FEILD_TEX; break; // ice field
                case 3: tex = NEBULA_TEX; break; // nebula
                case 4: tex = SYSTEM_TEX; break;
            }
            k_put_rect(tex, i + 11, j + 11);
        }
    }

    // draw jump position
    if (s == 0) {
        k_put_rect(GREEN_TEX, x + 1, y + 1);
    } else if (s == 1){
        k_put_rect(GREEN_TEX, x + 11, y + 1);
    } else if (s == 2){
        k_put_rect(GREEN_TEX, x + 11, y + 11);
    } else if (s == 3){
        k_put_rect(GREEN_TEX, x + 1, y + 11);
    }
    // initalize temp
    char temp_data[16];
    for (int i = 0; i < 16; i++){
        temp_data[i] = 0;
    }

    // search, inform
    // FIX THIS -- GENERALIZE SO MULTIPLE MAPS ARE SUPPORTED (pointers?)
    switch(s){
        case 0:
            // search
            for (int i = 0; i < 10; i++){
                // yes these need to be switched eventually someone (not me) will fix this
                if(level_0_0_tile_data[i].y == x && level_0_0_tile_data[i].x == y){
                    for (int j = 0; j < 16; j++){
                        temp_data[j] = level_0_0_tile_data[i].data[j];
                    }
                }
            }
            break;
        case 1:
            // search
            for (int i = 0; i < 10; i++){
                // yes these need to be switched eventually someone (not me) will fix this
                if(level_0_1_tile_data[i].y == x && level_0_1_tile_data[i].x == y){
                    for (int j = 0; j < 16; j++){
                        temp_data[j] = level_0_1_tile_data[i].data[j];
                    }
                }
            }
            break;
        case 3:
            // search
            for (int i = 0; i < 10; i++){
                // yes these need to be switched eventually someone (not me) will fix this
                if(level_0_3_tile_data[i].y == x && level_0_3_tile_data[i].x == y){
                    for (int j = 0; j < 16; j++){
                        temp_data[j] = level_0_3_tile_data[i].data[j];
                    }
                }
            }
            break;
        case 2:
            // search
            for (int i = 0; i < 10; i++){
                // yes these need to be switched eventually someone (not me) will fix this
                if(level_0_2_tile_data[i].y == x && level_0_2_tile_data[i].x == y){
                    for (int j = 0; j < 16; j++){
                        temp_data[j] = level_0_2_tile_data[i].data[j];
                    }
                }
            }
            break;
    }
    k_put_text(temp_data, 23, 7);


    // draw cuttent position
    if (sector_s == 0) {
        k_put_rect(RED_TEX, sector_x + 1, sector_y + 1);
    } else if (sector_s == 1){
        k_put_rect(RED_TEX, sector_x + 11, sector_y + 1);
    } else if (sector_s == 2){
        k_put_rect(RED_TEX, sector_x + 11, sector_y + 11);
    } else if (sector_s == 3){
        k_put_rect(RED_TEX, sector_x + 1, sector_y + 11);
    }

    k_put_text("Warp Config System v12.81.20392", 23, 1);
    k_put_text("Quadrant: Epsilon", 23, 3); // needs to be done dynamically for when mult. maps are supported
    sprintf(tim, "Jump Sector: %d - %d - %d    Current Sector: %d - %d - %d", s, x, y, sector_s, sector_x, sector_y);
    k_put_text(tim, 23, 4);
    k_put_text("Warp Engine Integrity: 87%", 23, 5); // needs to be done dynamically once engines work

    k_put_text("Engine Status:", 23, 23);
    k_put_text("[Enter] to configure", 23, 24);
    k_put_text("Fuel: 9678 / 10000", 23, 26); // needs to be done dynamiclly once engines work
    k_put_text("Peak Flux: 0.6772 A--DE-G-", 23, 27);
    k_put_text("Reserved Flux: 10.2821", 23, 28);
    k_put_text("Time Per Cycle: 1h 17m 57s", 23, 30); // needs to be done dynamically ...

    k_put_text("E1", 2, 23);
    k_put_text("E2", 7, 23);
    k_put_text("E3", 12, 23);
    k_put_text("E4", 17, 23);

    for(int i = 0; i < 2; i++){
        for (int j = 0; j < 10; j++){
//            rsetPosition( r, 32 + 16 * i, 400 + j * 16);
            if ( j >= e1_y) {
                k_put_rect(RED_TEX, 2 + i, 25 + j);
            } else if (j >= e1_g && j < e1_y){
                k_put_rect(YELLOW_TEX, 2 + i, 25 + j);
            } else {
                k_put_rect(GREEN_TEX, 2 + i, 25 + j);
            }

            if ( j >= e2_y) {
                k_put_rect(RED_TEX, 7 + i, 25 + j);
            } else if (j >= e2_g && j < e2_y){
                k_put_rect(YELLOW_TEX, 7 + i, 25 + j);
            } else {
                k_put_rect(GREEN_TEX, 7 + i, 25 + j);
            }

            if ( j >= e3_y) {
                k_put_rect(RED_TEX, 12 + i, 25 + j);
            } else if (j >= e3_g && j < e3_y){
                k_put_rect(YELLOW_TEX, 12 + i, 25 + j);
            } else {
                k_put_rect(GREEN_TEX, 12 + i, 25 + j);
            }

            if ( j >= e1_y) {
                k_put_rect(RED_TEX, 17 + i, 25 + j);
            } else if (j >= e4_g && j < e4_y){
                k_put_rect(YELLOW_TEX, 17 + i, 25 + j);
            } else {
                k_put_rect(GREEN_TEX, 17 + i, 25 + j);
            }
        }
    }

}

// they are basically the same
// FIX THIS THO
void draw_warp(int x, int y, int s){
    draw_prewarp(x, y, s);
}

void draw_quests(){
    // nothing here
}

void draw_cutscene(){
    // nothing here
}

void draw_trade( int trade_index ){
    // merchant mode;
    k_put_text("MERCHANT", 0, 0);
    char tim[80];
    sprintf(tim, "CREDITS: $%d", credits);
    k_put_text(tim, 32, 0);

    int l = 0;

    for (int i = 0; i < npc_last.inventory_size; i++){
        switch(npc_last.inventory[i].type){
            case 1:
                sprintf(tim, "Ration : %s", inventory[i].data);
                break;
            case 2:
                sprintf(tim, "Handgun : %s", inventory[i].data);
                break;
            case 3:
                sprintf(tim, "Wrench : %s", inventory[i].data);
                break;
            case 4:
                sprintf(tim, "Ammunition : %s", inventory[i].data);
                break;
            case 5:
                sprintf(tim, "Grenade : %s", inventory[i].data);
                break;
            case 6:
                sprintf(tim, "Book : %s", inventory[i].data);
                break;
            case 7:
                sprintf(tim, "Machine Gun : %s", inventory[i].data);
                break;
            case 8:
                sprintf(tim, "Rocket Launcher : %s", inventory[i].data);
                break;
            case 9:
                sprintf(tim, "Pick : %s", inventory[i].data);
                break;
            case 10:
                sprintf(tim, "Medkit : %s", inventory[i].data);
                break;
            default:
                strcpy(tim, "Invalid Item!");
        }
        k_put_text(tim, 2, l + 1);

        if (i == trade_index){
            k_put_text("->", 0, l + 1);
        }

        sprintf(tim, "%s ($%d)", npc_last.inventory[i].data, npc_last.inventory[i].cost);
        k_put_text(tim, 2, l + 2);
        l += 3;
    }

    l+=2;
    k_put_text("N(Exit) Q(Go Up) E(Go Down) U(Sell Items) Enter(Purchase)", 2, 34);
}

void draw_stats(){
    char tim[80];
    int texid = 0;

    k_put_text("HEALTH: ", 36, 1);

    texid = HEART_TEX;
    if (health >= 250){
        k_put_rect(texid, 45, 1);
    } else {
        k_put_rect(CRITICAL_TEX, 43, 1);
    }
    if (health >= 500){
        k_put_rect(texid, 44, 1);
    }
    if (health >= 750){
        k_put_rect(texid, 43, 1);
    }
    texid = FULL_HEALTH_TEX;
    if (health >= 900){
        k_put_rect(texid, 43, 1);
    }

    sprintf(tim, "SCORE: %d", score);
    k_put_text(tim, 36, 2);

    sprintf(tim, "FUEL: %d / 10K", fuel);
    k_put_text(tim, 36, 3);

    sprintf(tim, "CREDITS: %d ", credits);
    k_put_text(tim, 36, 4);

    sprintf(tim, "AMMO: %d ", rounds);
    k_put_text(tim, 36, 5);
}

void draw_inventory(){
    char tim[80];

    k_put_text("INVENTORY: ", 36, 6);

    // loop inventory
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 4; j++){
            if (i + j * 4 < num_items){
                int tex = 0;
                switch(inventory[i + j * 4].type){
                    case 1:
                        tex = FOOD_ITEM_TEX;
                        break;
                    case 2:
                        sprintf(tim, "Handgun : %s", inventory[i].data);
                        tex = GUN_ITEM_TEX;
                        break;
                    case 3:
                        sprintf(tim, "Wrench : %s", inventory[i].data);
                        tex = WRENCH_ITEM_TEX;
                        break;
                    case 4:
                        sprintf(tim, "Ammunition : %s", inventory[i].data);
                        tex = BULLET_ITEM_TEX;
                        break;
                    case 5:
                        sprintf(tim, "Grenade : %s", inventory[i].data);
                        tex = GRENADE_ITEM_TEX;
                        break;
                    case 6:
                        sprintf(tim, "Book : %s", inventory[i].data);
                        tex = BOOK_ITEM_TEX;
                        break;
                    case 7:
                        sprintf(tim, "Machine Gun : %s", inventory[i].data);
                        tex = MG_ITEM_TEX;
                        break;
                    case 8:
                        sprintf(tim, "Rocket Launcher : %s", inventory[i].data);
                        tex = RL_ITEM_TEX;
                        break;
                    case 9:
                        sprintf(tim, "Pick : %s", inventory[i].data);
                        tex = PICK_ITEM_TEX;
                        break;
                    case 10:
                        sprintf(tim, "Medkit : %s", inventory[i].data);
                        tex = MEDKIT_ITEM_TEX;
                        break;
                    default:
                        strcpy(tim, "Invalid Item!");
                }
                k_put_rect(tex, 36 + i, j + 6);
            } else {
                k_put_rect(DEBUG_TEX, 36 + i, j + 6);
            }
        }
    }
    /*int i;
    for(i = 0; i < num_items; i++){
        switch(inventory[i].type){
            case 1:
                sprintf(tim, "Ration : %s", inventory[i].data);
                break;
            case 2:
                sprintf(tim, "Handgun : %s", inventory[i].data);
                break;
            case 3:
                sprintf(tim, "Wrench : %s", inventory[i].data);
                break;
            case 4:
                sprintf(tim, "Ammunition : %s", inventory[i].data);
                break;
            case 5:
                sprintf(tim, "Grenade : %s", inventory[i].data);
                break;
            case 6:
                sprintf(tim, "Book : %s", inventory[i].data);
                break;
            case 7:
                sprintf(tim, "Machine Gun : %s", inventory[i].data);
                break;
            case 8:
                sprintf(tim, "Rocket Launcher : %s", inventory[i].data);
                break;
            case 9:
                sprintf(tim, "Pick : %s", inventory[i].data);
                break;
            case 10:
                sprintf(tim, "Medkit : %s", inventory[i].data);
                break;
            default:
                strcpy(tim, "Invalid Item!");
        }
        k_put_text(tim, 37, i + 8);
    }
    i++;
*/
    k_put_text("QUESTS: ", 36, 12);

    if (num_active_quests == 0){
        k_put_text("-[No Active Quests]", 36, 13);
    } else {
        for (int j = 0; j < num_active_quests; j++){
            char tmp[80];
            sprintf(tmp, "%s [%d]", quest_registry[npc_last.quest_id].title, quest_registry[npc_last.quest_id].id);
            k_put_text(tmp, 36, j + 14);
        }
    }
}

void draw_rogue(){
    int texid = 0;
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < HEIGHT; j++){
            if (rogue_npc_master[master_index](i - 15 + character_x, j - 15 + character_y).id <= 0) {
                int tdat = -1;
                if (((i - 15 + character_x) >= 0 && (i - 15 + character_x ) < cached_map.w) &&
                    ((j - 15 + character_y) >= 0 && (j - 15 + character_y ) < cached_map.h)) {
                    tdat = cached_map.tile_type[(i - 15 + character_x)  + (j - 15 + character_y) * cached_map.w];
                }

                switch (tdat){
                    case -1:
                        texid = BLACK_TEX;
                        break;
                    case 0:
                        texid = FLOOR_TEX;
                        break;
                    case 1:
                        texid = WALL_TEX;
                        break;
                    case 2: // plants (passable)
                        texid = PLANTS_TEX;
                        break;
                    case 3: // plants (impassable)
                        texid = SPLANTS_TEX;
                        break;
                    case 4: // impassable machinery
                        texid = MACHINERY_TEX;
                        break;
                    case 9: // npc (impassable)
                        texid = NPC_TEX;
                        break;
                    case 6: // fire
                        texid = FIRE_TEX;
                        break;
                    case 7: // portal
                        texid = PORTAl_TEX;
                        break;
                    case 8: // enemy (impassable)
                        texid = ENEMY_TEX;
                        break;
                    case 5: // spawn
                        texid = SPAWN_TEX;
                        break;
                    case 10: // water
                        texid = WATER_TEX;
                        break;
                    case 11: // overgrown machinery (impassable)
                        texid = OMACHINERY_TEX;
                        break;
                    case 12:
                        texid = FLOOR_ALT_TEX;
                        break;
                    default:
                        texid = FLOOR_TEX;
                }
                if (tdat < -1){
                    //printf("T%d ", tdat);
                    texid = PORTAl_TEX;
                }
            } else {
                texid = NPC_TEX;
            }

            k_put_rect(texid, i, j);
        }
    }

    draw_stats();
    draw_inventory();

    for(int i = 0; i < num_entities; i++){
        if (15 - character_x + entities[i].x < 35 && 15 - character_y + entities[i].y < 35) {
            k_put_rect(CRATE_TEX, 15 - character_x + entities[i].x, 15 - character_y + entities[i].y);
        }
    }

    k_put_rect(GREEN_TEX, 15, 15);
}

void draw_use_item(int trade_index){
    char tim[80];

    k_put_text("Select Item: ", 0, 0);

    // loop inventory
    int i;
    for(i = 0; i < num_items; i++){
        switch(inventory[i].type){
            case 1:
                sprintf(tim, "%s Ration", inventory[i].data);
                break;
            case 2:
                sprintf(tim, "%s Handgun", inventory[i].data);
                break;
            case 3:
                sprintf(tim, "%s Wrench", inventory[i].data);
                break;
            case 4:
                sprintf(tim, "%s Ammunition", inventory[i].data);
                break;
            case 5:
                sprintf(tim, "%s Grenade", inventory[i].data);
                break;
            case 6:
                sprintf(tim, "%s Book", inventory[i].data);
                break;
            case 7:
                sprintf(tim, "%s Machine Gun", inventory[i].data);
                break;
            case 8:
                sprintf(tim, "%s Rocket Launcher", inventory[i].data);
                break;
            case 9:
                sprintf(tim, "%s Pick", inventory[i].data);
                break;
            case 10:
                sprintf(tim, "%s Medkit", inventory[i].data);
                break;
            default:
                strcpy(tim, "Invalid Item!");
        }

        k_put_text(tim, 2, i + 1);

        if (i == trade_index){
            k_put_text("->", 0, i + 1);
        }
    }
}

void draw_logo(){
    k_put_rects(LOGO_TEX, 0, 0, S_WIDTH, S_HEIGHT);
}

void draw_game_over(){
    k_put_rects(GAME_OVER_TEX, 0, 0, S_WIDTH, S_HEIGHT);
}
