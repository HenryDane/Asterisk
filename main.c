#include <stdio.h> // rand()
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "kernel/kernel.h"
#include "main.h"
#include "display.h"
#include "entity.h"
#include "map.h"
#include "quest.h"
#include "terrain.h"
#include "data.h"

// game state: 0 - normal, 1 - ship nav, 2 - combat screen, 3 - character, 4 - port / entity interact
int displaystate = 0;

int id_entity_last = 0;
int num_entities_o = 0;

// character data
int health = 1000;
float experience = 0;
int credits = 1000;
int fuel = 10000;
int score = 0;
int rounds = 10000;

int ship_x = 20;
int ship_y = 20;

int character_x = 0;
int character_y = 0;

int selected_object = 0;

double time_count;
double bullet_timer;

// engine data
int flux = 500;
int fuel_r = 500;
int durability = 500;
int response = 500;
int flux_clamp = 1000;
int emission_clamp = 1000;
int themal_clamp = 1000;

int sector_s = 0;
int sector_x = 0;
int sector_y = 0;

int level = 0;
int location = 0;

int e1_g = 8;
int e1_y = 9;
int e2_g = 8;
int e2_y = 9;
int e3_g = 8;
int e3_y = 9;
int e4_g = 8;
int e4_y = 9;
int ticks_for_warp;

int time_character = 0;
int time_entity_o = 0;
int time_rocket = 0;

int facing = 0;
bool tilted = false;

int modules_enabled[NUM_MODULES_MAX] = {-1};

item_t inventory[NUM_ITEMS_MAX] = {{0,2,false," T4", 3},
                        {1,1,false," 4K Cal.", 8},
                        {2,3,false," Electric", 9},
                        {4,5,false," Boom", 5},
                        {5,5,false," Boom", 5},
                        {6,5,false," Boom", 5},
                        {7,16,false," Speed Upg.", 11}};
int num_items = 7;

d_item_t dropped_items[NUM_DROPPED_MAX] = {{-1,-1,false, " ", 0}};
int num_dropped_items = 0;

int num_active_quests = 0;

npc_t npc_last = {-1, 0, 0, 0, {-1, 0, ' ', 0}, false, false, false, 0, -1, -1 };  // initalize npc

// game state (see documentation)
int state = -1;

int num_entities = 0;
entity_t entities[32];

int selected_module = -1;
int trade_index = 0; // pointer to trading address

int hidden_npcs[NUM_HIDDEN_NPCS_MAX] = {-1, -1, -1, -1, -1, -1, -1, -1}; // used for hiding NPCs by ID
int num_hidden_npcs = 0;

int time_cutscene = 0;
cutscene_t current_cutscene;

int notifications = 0;

int quests_consumed[NUM_QUESTS_MAX];

int main( ){
    // temporary variable for sprintf calls
    char tmp[80];

    // initalize rand
    srand (time(NULL));

    int level = 0;

    // because we need to do this dont forget ok??
    init_maps();
    init_quests();
    init_levels();
    init_cutscenes();

    // set up graphics
    k_init_gfx();

    // init textures
    if (init_displays() < 0) { return -3; }

    printf("DONE \n");

    // init cache_map
    master_index = 0;
    load_map(master_index);

    num_active_quests = 0; // no active quests

    int jump_x = 0;
    int jump_y = 0;
    int jump_s = 0;

    // main loop
    while (k_this_close_request()){
        // clean texture
        k_refresh_display();

        // handle events
        while (k_get_events()){
#if USE_SDCC == 2 // ugly hack #109873276
            // close window if needed
            if (k_get_sf_event_type() == sfEvtClosed)
                sfRenderWindow_close(k_get_window());
            // check keys allow repeats
            if (k_get_sf_event_type() == sfEvtKeyPressed) {
#endif // USE_SDCC
                // handle key presses

                if (state == -4){
                    return 0; // leave if on final screen
                } else if (state == -2){
                    master_index = 0;
                    load_map(master_index);
                    state = -3; // go back to main menu
                }

                switch( k_get_key() ){
                    case sfKeyEscape:
                        return 0;
                    case sfKeyNum5:
                        if (state > 0){
                            state = 16; // rouge like
                        } else if (state == -6){
                            load(5);
                        } else if (state == -7){
                            save(5);
                        }
                        break;
                    case sfKeyNum1:
                        if (state > 0) {
                            state = 1;
                        } else if (state == -6){
                            load(1);
                            state = 16;
                        } else if (state == -7){
                            save(1);
                        }
                        break;
                    case sfKeyNum2:
                        if (state > 0) {
                            state = 2;
                        } else if (state == -6){
                            load(2);
                        } else if (state == -7){
                            save(2);
                        }
                        break;
                    case sfKeyNum3:
                        if (state > 0) {
                            state = -2;
                        } else if (state == -6){
                            load(3);
                        } else if (state == -7){
                            save(3);
                        }
                        break;
                    case sfKeyNum4:
                        if (state > 0) {
                            state = 32;
                            trade_index = 0;
                        } else if (state == -6){
                            load(4);
                        } else if (state == -7){
                            save(4);
                        }
                        break;
                    case sfKeyL:
                        if (state == -3){
                            state = -4;
                        }
                        break;
                    case sfKeyQ:
                        if (state == 19 || state == 32 || state == 37 || state == 43) {
                            if (trade_index > 0) trade_index--;
                        } else if (state == 16){
                            trade_index = 0;
                            state = 21;
                        } else if (state == 21){
                            if (trade_index > 0) {
                                trade_index--;
                            }
                        } else if (state == 1){
                            jump_s++;
                            if (jump_s > 3) jump_s = 0;
                            if (jump_s < 0) jump_s = 3;
                        } else if (state == 4){
                            facing = -10;
                        } else if (state == 2){
                            if(fuel_r + CONFIG_INCREMENT_AMOUNT <= 1000) fuel_r += CONFIG_INCREMENT_AMOUNT;
                        } else if (state == 44){
                            if (trade_index - 1 >= 0) trade_index--;
                        }
                        break;
                    case sfKeyE:
                        if (state == 19) {
                            if (trade_index + 1 < npc_last.inventory_size) {
                                trade_index++;
                            }
                        } else if (state == 32){
                            if (trade_index + 1 < NUM_MODULES_MAX) {
                                trade_index++;
                            }
                        } else if (state == 37){
                            if (trade_index + 1 < num_items) {
                                trade_index++;
                            }
                        } else if (state == 21) {
                            if (trade_index + 1 < num_items) {
                                trade_index++;
                            }
                        } else if (state == 43){
                            // drop item
                            if (trade_index + 1 < NUM_DROPPED_MAX) {
                                trade_index++;
                            }
                        } else if (state == 1){
                            jump_s--;
                            if (jump_s > 3) jump_s = 0;
                            if (jump_s < 0) jump_s = 3;
                        } else if (state == 16){
                            state = 43; // go drop a thingy
                        } else if (state == 2){
                            if(flux_clamp + CONFIG_INCREMENT_AMOUNT <= 1000) flux_clamp += CONFIG_INCREMENT_AMOUNT;
                        } else if (state == 44){
                            if (trade_index + 1 < num_entities_o) trade_index++;
                        }
                        break;
                    case sfKeyW:
                        if (state == 16) {
                            update_entities();
                            if (character_y - 1 >= 0 && check_next_step(character_x, character_y - 1)) {
                                character_y--;
                            }
                        } else if (state == 1){
                            jump_y--;
                            if (jump_y > 9) jump_y = 9;
                            if (jump_y < 0) jump_y = 0;
                        } else if (state == 4){
                            facing = 0;
                        } else if (state == 32){
                            selected_module++;
                        } else if (state == 2){
                            if(durability + CONFIG_INCREMENT_AMOUNT <= 1000) durability += CONFIG_INCREMENT_AMOUNT;
                        } else if (state == -3){
                            state = -6;
                        } else if (state == 3){
                            if (tmp[65] - 1 >= 0) tmp[65]--;
                        }
                        break;
                    case sfKeyA:
                        if (state == 16) {
                            update_entities();
                            if (character_x - 1 >= 0  && check_next_step(character_x - 1, character_y)) {
                                    character_x--;
                            }
                        } else if (state == 1){
                            jump_x--;
                            if (jump_x > 9) jump_x = 9;
                            if (jump_x < 0) jump_x = 0;
                        } else if (state == 4){
                            facing = 3;
                        } else if (state == -3){
                            state = 16;
                        } else if (state == 2){
                            if(fuel_r - CONFIG_INCREMENT_AMOUNT >= 0) fuel_r -= CONFIG_INCREMENT_AMOUNT;
                        } else if (state == 3){
                            if (tmp[64] - 1 >= 0) tmp[64]--;
                        }
                        break;
                    case sfKeyS:
                        if (state == 16) {
                            update_entities();
                            if (character_y + 1 < cached_map.h  && check_next_step(character_x, character_y + 1)) {
                                character_y++;
                            }
                        } else if (state == 1){
                            jump_y++;
                            if (jump_y > 9) jump_y = 9;
                            if (jump_y < 0) jump_y = 0;
                        } else if (state == 4){
                            facing = 2;
                        } else if (state == 32){
                            selected_module--;
                        } else if (state == 2){
                            if(durability - CONFIG_INCREMENT_AMOUNT >= 0) durability -= CONFIG_INCREMENT_AMOUNT;
                        } else if (state == -3){
                            state = -6;
                        } else if (state == 3){
                            if (tmp[65] + 1 < 18) tmp[65]++;
                        }
                        break;
                    case sfKeyD:
                        if (state == 16) {
                            update_entities();
                            if (character_x + 1 < cached_map.w  && check_next_step(character_x + 1, character_y)){
                                character_x++;
                            }
                        } else if (state == 1){
                            jump_x++;
                            if (jump_x > 9) jump_x = 9;
                            if (jump_x < 0) jump_x = 0;
                        } else if (state == 4){
                            facing = 1;
                        } else if (state == 2){
                            if(flux_clamp - CONFIG_INCREMENT_AMOUNT >= 0) flux_clamp -= CONFIG_INCREMENT_AMOUNT;
                        } else if (state == 3){
                            if (tmp[64] + 1 < 10) tmp[64]++;
                        }
                        break;
                    case sfKeySpace:
                        if (state == -1){
                            state = -3;
                        }
                        break;
                    case sfKeyReturn:
                        if (state == 32){
                            if (trade_index >= 0 && trade_index < NUM_MODULES_MAX){
                                if (modules_enabled[trade_index] > 0) {
                                    printf("REMOVING MODULE %d \n", modules_enabled[trade_index]);
                                    remove_module(modules_enabled[trade_index]);
                                } else {
                                    printf("ADDING MODULE %d \n", selected_module);
                                    add_module(selected_module);
                                }
                            }
                        } else if (state == 43){
                            if (num_items > 0){
                                drop_item_c(trade_index);
                                state = 16;
                            }
                        } else if (state == 19){
                            if (trade_index >= 0 && trade_index < npc_last.inventory_size ){
                                if (num_items < 16){
                                    if (credits - npc_last.inventory[trade_index].cost >= 0){
                                        credits -= npc_last.inventory[trade_index].cost;
                                        printf("adding item . . . \n");
                                        strcpy(inventory[num_items].data, npc_last.inventory[trade_index].data);
                                        inventory[num_items].id = npc_last.inventory[trade_index].id;
                                        inventory[num_items].type = npc_last.inventory[trade_index].type;
                                        inventory[num_items].data_len = npc_last.inventory[trade_index].data_len;
                                        inventory[num_items].unuseable = false;
                                        num_items++;
                                        notifications++;
                                    } else {
                                        printf("failed cost check\n");
                                    }
                                } else {
                                    printf("failed item number check\n");
                                }
                            } else {
                                printf("failed array bounds check\n");
                            }
                        } else if (state == 37) {
                            if (trade_index >= 0 && trade_index < num_items ){
                                if (num_items < 16){
                                    credits += 10; // needs updating for actual apprasial
                                    //int i = trade_index; // yep, awful hack (#081724234) (also a redundant hack)
                                    if (/*erase*/ true){ // ugly hack #408554564
                                        for (int i = trade_index; i < num_items; i++){
                                            inventory[i] = inventory[(i + 1 < num_items) ? i + 1 : i];
                                        }
                                        if (num_items > 0) num_items --;
                                        notifications++;
                                    }
                                } else {
                                    printf("failed item number check\n");
                                }
                            } else {
                                printf("failed array bounds check\n");
                            }
                        } else if (state == 18 || state == 17 || state == 30) {
                            state = 16; // leave cutscene and (old) quest mode
                        } else if (state == 21){ // use item
                            if (trade_index >= 0 && trade_index < num_items){
                                printf("using item at trade_index %d \n", trade_index);
                                use_item(inventory[trade_index].type);
                            }
                        } else if (state == 1){
                            state = 3;
                            sector_x = jump_x;
                            sector_y = jump_y;
                            sector_s = jump_s;
                            ticks_for_warp = /*jump_x * 2 + jump_y * 2 + jump_s * 3 + (rand() % 20) */ 50;
                            build_terrain(sector_x, sector_y, sector_s);

                            // set up the gauntlet
                            for (int i = 0; i < 64; i += 4){
                                tmp[i] = rand() % 5 + 3;
                                tmp[i + 1] = - rand() % 20;
                                tmp[i + 2] = rand() % 2;
                                tmp[i + 3] = 10;
                            }

                            tmp[64] = 5;
                            tmp[65] = 14;

                            // keeps track of total fuel cost
                            tmp[66] = 10;
                        } else if (state == 44){
                            state = 45;
                        }
                        break;
                    case sfKeyTab:
                        printf("STATE: %d SEL OBJ: %d ID_LAST: %d C_X: %d C_Y: %d HEALTH: %d TRADE_INDEX: %d NUM_ITEMS: %d MASTER_INDEX: %d NUM_ENTITES: %d CACHE_W: %d CACHE_H: %d NUM_ENTITIES_O: %d NUM_DROPPED_ITEMS: %d NUM_ACTIVE_QUESTS: %d TMP[64]: %d TMP[65]: %d \n",
                               state, selected_object, 0, character_x, character_y, health, trade_index, num_items, master_index, num_entities, cached_map.w, cached_map.h, num_entities_o, num_dropped_items, num_active_quests, tmp[64], tmp[65]);
                        break;
                    case sfKeyTilde:
                        printf("entities contains %d items: \n", num_entities);
                        for (int i = 0; i < num_entities; i++){
                            printf("    Entity %d : ID: %d TYPE: %d X: %d Y: %d VX: %d VY: %d \n", i, entities[i].id, entities[i].type, entities[i].x, entities[i].y, entities[i].vx, entities[i].vy);
                        }
                        break;
                    case sfKeyEqual: // increment map pointer (changed from + so shift key can be unused)
                        if (master_index + 1 >= 0 && master_index + 1 < NUM_MAPS) master_index++; // pointer safety first
                        break;
                    case sfKeyDash: // decrement map pointer
                        if (master_index - 1 >= 0 && master_index - 1 < NUM_MAPS) master_index--; // pointer safety first
                        break;
                    case sfKeyBack: // set up changes
                        load_map(master_index);
                        break;
                    case sfKeyU:
                        if (state == 19){
                            state = 37;
                            notifications = 0;
                        }
                        break;
                    case sfKeyY:
                        if (state == 27) {
                            if (!searchQuest(npc_last.quest_id)){ // if quest is not active active
                                bool already_complete = false;
                                for(int i = 0; i < NUM_QUESTS_MAX; i++){
                                    if (quests_consumed[i] == npc_last.quest_id){
                                        // quest is found, aborting;
                                        already_complete = true;
                                        break;
                                    } else if (quests_consumed[i] < 0){
                                        // found a free slot, marking quest as done and exiting
                                        quests_consumed[i] = npc_last.quest_id;
                                        break;
                                    }
                                }

                                if (!already_complete){
                                    quest_a_registry[num_active_quests].quest = quest_registry[npc_last.quest_id];
                                    quest_a_registry[num_active_quests].position = 0;
                                    printf("Added quest %d!\n", quest_a_registry[num_active_quests - 1].quest.id);
                                    num_active_quests++;
                                    state = 16;
                                } else {
                                    printf("Could not add quest \n");
                                    state = 16;
                                }
                            } else {
                                printf("Quest %d already active \n", npc_last.quest_id);
                                state = 29; // quest add fail
                            }
                        } else if (state == 4){
                            state = 44; // view stuff bro
                        } else if (state == 29){
                            // why is this here?
                        } else if (state == 16){
                            if (num_items + 1 < NUM_ITEMS_MAX){
                                item_t tmp_item;
                                if (collect_item(&tmp_item, character_x, character_y, master_index)){
                                    printf("Item is %d %d %d \n", tmp_item.id, tmp_item.type, tmp_item.unuseable);
                                    if (tmp_item.id >= 0){
                                        inventory[num_items++] = tmp_item;
                                    }
                                }
                            }
                        }
                        break;
                    case sfKeyN:
                        if (state == 17 || state == 18 || state == 19 || state == 21 || state == 27 || state == 28 ||
                            state == 29 || state == 37 || state == 32 || state == 43 || state == 30 ) {
                            state = 16;
                        } else if (state == 45 || state == 44){
                            state = 4;
                        }
                        break;
                    case sfKeyUp:
                        if (num_entities < MAX_ENTITIES - 1 && rounds > 0) {
                            entities[num_entities++] = (entity_t) {1432, character_x, character_y, 0, -1, 1};
                            rounds--;
                        }
                        break;
                    case sfKeyDown:
                        if (num_entities < MAX_ENTITIES - 1 && rounds > 0) {
                            entities[num_entities++] = (entity_t) {1432, character_x, character_y, 0, 1, 1};
                            rounds--;
                            break;
                        }
                        break;
                    case sfKeyLeft:
                        if (num_entities < MAX_ENTITIES - 1 && rounds > 0) {
                            entities[num_entities++] = (entity_t) {1432, character_x, character_y, -1, 0, 1};
                            rounds --;
                        }
                        break;
                    case sfKeyRight:
                        if (num_entities < MAX_ENTITIES - 1 && rounds > 0) {
                            entities[num_entities++] = (entity_t) {1432, character_x, character_y, 1, 0, 1};
                            rounds --;
                        }
                        break;
                    case sfKeyBackSlash:
                        if (state == 1){
                            state = 2;
                        } else if (state == 2){
                            state = 1;
                        }
                        break;
                    case sfKeyF:
                        if (state == 2){
                            if(emission_clamp - CONFIG_INCREMENT_AMOUNT >= 0) emission_clamp -= CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sfKeyR:
                        if (state == 2){
                            if(emission_clamp + CONFIG_INCREMENT_AMOUNT <= 1000) emission_clamp += CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sfKeyT:
                        if (state == 2){
                            if(themal_clamp + CONFIG_INCREMENT_AMOUNT <= 1000) themal_clamp += CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sfKeyG:
                        if (state == 2){
                            if(themal_clamp - CONFIG_INCREMENT_AMOUNT >= 0) themal_clamp -= CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    default: // do nothing (undefined key)
                        break;
                }
#if USE_SDCC == 2
            }
#endif // USE_SDCC
        }

        switch(state){  // draw screen and do stuff
            case -6:
                k_put_text("Press 1 - 5 to load a save", 0, 0);
                break;
            case -7:
                k_put_text("Press 1 - 5 to select a slot to save to", 0, 0);
            case -2:
                // game over?
                draw_game_over();
                break;
            case -1:
                draw_logo();
                break;
            case -3:
                draw_main_menu();
                break;
            case -4:
                draw_credits();
                break;
            case 2:
                draw_engine_config();
                /*state = 1;
                printf("config is disabled \n");*/
                break;
            case 1:
                draw_prewarp(jump_x, jump_y, jump_s);
                break;
            case 3:
                //draw_warp(jump_x, jump_y, jump_s);
                draw_engine_controls();

                // do "timing" for warp travel
                // tmp (the buffer) is used to store space data here bc why tf not
                // each object is 4 bytes long (x, y, type, extra)
                // tmp[64] = player x, tmp[65] = player y, tmp[66] = last used index
                if (rand() % 100 < 2){
                    for (int i = 0; i < 64; i += 4){
                        if (tmp[i + 3] < 0){
                            if (rand() % 10 < 3){
                                tmp[i + 1] = - rand() % 3;
                                tmp[i + 2] = rand() % 2;
                                tmp[i + 3] = 9;
                            } else {
                                continue;
                            }
                        }

                        //printf("incrementing: i = %d, tmp[%d] = %d, tmp[%d + 1] = %d, tmp[%d + 2] = %d, tmp[%d + 3] = %d \n",
                        //       i, i, (int) tmp[i], i, (int) tmp[i + 1], i, (int) tmp[i + 2], i, tmp[i + 3]);

                        if (tmp[i] == tmp[64] && tmp[i + 1] == tmp[65]){
                            printf("collisson at warp! \n");
                            // player hit this object, damage engines
                            tmp[66] += rand() % 50;
                            switch (rand() % 4){
                                case 0: // engine 0
                                    e1_g -= 4;
                                    e1_y -= 3;
                                    printf("Engine 1 has taken damage \n");
                                    if (e1_g < 0) e1_g = 0;
                                    if (e1_y <= 0) state = -2; // you died
                                    break;
                                case 1: // engine 1
                                    e2_g -= 4;
                                    e2_y -= 3;
                                    printf("Engine 2 has taken damage \n");
                                    if (e2_g < 0) e2_g = 0;
                                    if (e2_y <= 0) state = -2; // you died
                                    break;
                                case 2: // engine 2
                                    e3_g -= 4;
                                    e3_y -= 3;
                                    printf("Engine 3 has taken damage \n");
                                    if (e3_g < 0) e3_g = 0;
                                    if (e3_y <= 0) state = -2; // you died
                                    break;
                                case 3: // engine 3
                                    e4_g -= 4;
                                    e4_y -= 3;
                                    printf("Engine 4 has taken damage \n");
                                    if (e4_g < 0) e4_g = 0;
                                    if (e4_y <= 0) state = -2; // you died
                                    break;
                            }
                        }

                        // bounds check
                        if (tmp[i] > 11) tmp[i + 3] = -1;
                        if (tmp[i + 1] > 16) tmp[i + 3] = -1;

                        // move
                        tmp[i] += rand() % 3 - 1;
                        tmp[i + 1] += 1;
                    }

                    ticks_for_warp--;
                    if (ticks_for_warp < 0){
                        state = 4;
                        fuel -= tmp[66];
                        printf("COMPLETED WARP \n");
                    }
                }

                for (int i = 1; i < 11; i++){
                    for (int j = 1; j < 19; j++){
                        k_put_rect(DEBUG_TEX, i, j);
                    }
                }

                for (int i = 0; i < 64; i += 4){
                    if (tmp[i + 3] < 0) continue; // skip if out of bounds
                    switch(tmp[i + 2] % 4){
                        case 0:
                            k_put_rect(ASTEROID_TEX, 1 + tmp[i], 1 + tmp[i + 1]);
                            break;
                        case 1:
                            k_put_rect(DEBRIS_TEX, 1 + tmp[i], 1 + tmp[i + 1]);
                            break;
                        default:
                            printf("Wrong type %d \n", tmp[i + 2] % 4);
                    }
                }

                k_put_rect(C_U_TEX, tmp[64] + 1, tmp[65] + 1);

                /*
                    In the gap between the controls and the display add some spaceteam type stuff motivating them to use the controls
                */

                break;
            case 4:
                display();

                // update entities
                update_entities_o(0);

                // increment timers
                time_character++;
                time_entity_o++;
                time_rocket++;
                break;
            case 15: //cutscene
                k_put_bmp(current_cutscene.first_frame_id + current_cutscene.frame);
                k_put_text(cutscene_str_dat + current_cutscene.text_reference[current_cutscene.frame], 19, 0);
                time_cutscene++;

                if (current_cutscene.frame >= current_cutscene.num_frames){
                    state = 16;
                    current_cutscene.id = -1;
                    current_cutscene.frame = 0;
                    printf("Finished cutscene \n");
                }

                if (time_cutscene > current_cutscene.delay_per_frame[current_cutscene.frame]){
                    time_cutscene = 0;
                    current_cutscene.frame++;
                }
                break;
            case 16:
                draw_rogue(); // draw scene

                // run timer for entity updates
                if (ticks_for_warp++ > 20){
                    update_entities(); // update the entities (but dont time them lmfao)
                    ticks_for_warp = 0;
                }
                break;
            case 27: // display quest add request
                sprintf(tmp, "NPC [%s] is offering quest %s, accept? [Y/N]", quest_registry[npc_last.quest_id].issuer, quest_registry[npc_last.quest_id].title);
                k_put_text(tmp, 0, 0);
                k_put_text("N(Exit) Y(Accept)", 2, 34);
                break;
            case 28: // failed to add the quest
                state = 29;
                k_put_text("Oh! Silly me! You already have that quest active!", 0, 0);
                k_put_text("Why would you want to have to do it a second time?", 0, 1);
                break;
            case 29: // quest active, display current position
                tmp[0] = tmp[0]; // that'll throw 'em off the scent
                int index = 0;
                for ( ; index < num_active_quests; index++){
                    if (quest_a_registry[index].quest.id == quest_registry[npc_last.quest_id].id) break;
                }
                sprintf(tmp, "Quest ID: %d Position: %d", npc_last.quest_id, quest_a_registry[index].position);
                k_put_text(tmp, 0, 19);

                k_put_text(quest_str_dat + quest_a_registry[index].quest.text_references[quest_a_registry[index].position], 0, 20);
                k_put_text("N(Exit)", 2, 34);
                k_put_bmp(quest_a_registry[index].quest.bitmap_references[quest_a_registry[index].position - 1]);
                break;
            case 30:
                k_put_text("Done", 19, 0);
                k_put_text(quest_str_dat + quest_a_registry[index].quest.text_references[quest_a_registry[index].position], 0, 20);
                k_put_text("N(Exit)", 2, 34);
                k_put_bmp(quest_a_registry[index].quest.bitmap_references[quest_a_registry[index].position - 1]);
                break;
            case 18: // cutscene
                k_put_text("CUTSCENE", 0, 0);
                k_put_text("N(Exit)", 2, 34);
                break;
            case 19: // trading menu
                draw_trade(trade_index);
                for (int i = 0; i < notifications; i++){
                    k_put_text("You bought an item", 32, 21 + i);
                }
                break;
            case 21: // item use menu
                draw_use_item(trade_index);
                break;
            case 32:
                draw_module_manage();
                break;
            case 37:
                draw_sell();

                for (int i = 0; i < notifications; i++){
                    k_put_text("You sold an item", 32, 21 + i);
                }
                break;
            case 43:
                draw_drop();
                break;
            case 44:
                // draw_view side panel (under stats in display();
                //state = 4; // temporary redirect
                k_put_text("Press [Q]/[E] & [Enter] to select ", 0, 0);

                for (int i = 0; i < num_entities_o; i++){
                    sprintf(tmp, "Index: %d Type: %d X: %d Y: %d", i, entities_o[i].type, entities_o[i].x, entities_o[i].y);
                    k_put_text(tmp, 5, 1 + i);
                }

                k_put_text("->", 1, 1 + trade_index);
                break;
            case 45:
                sprintf(tmp, "Viewing Object [i:%d]", trade_index);
                k_put_text(tmp, 0, 0);

                sprintf(tmp, "Type: %d X: %d Y: %d VX: %d VY: %d", entities_o[trade_index].type, entities_o[trade_index].x, entities_o[trade_index].y, entities_o[trade_index].vx, entities_o[trade_index].vy);
                k_put_text(tmp, 1, 2);

                // when prettifying UI add code here for viewing preset string data from level struct

                break;
            default:
                printf("Intercepted bad state %d \n", state);
                state = 16; // go to rogue to catch problems
                cleardisplay(false);
                break;
        }

        k_display();
    }

    return 0;
}
