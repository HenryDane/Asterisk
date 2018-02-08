//#include <SFML/Graphics.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "kernel/kernel.h"
#include "main.h"
#include "display.h"
#include "entity.h"
#include "map.h"
// #include "data.h"

// game state: 0 - normal, 1 - ship nav, 2 - combat screen, 3 - character, 4 - port / entity interact
int displaystate = 0;

// character data
int health = 1000;
float experience = 0;
int credits = 1000;
int fuel = 10000;
int score = 0;

int character_x = 0;
int character_y = 0;

int selected_object = 0;

item_t inventory[16] = {{0,2,false,"Glock    ", 5},
                     {1,1,false,"Generic  ", 7},
                     {2,3,false,"Glock    ", 5}};
int num_items = 3;

int num_active_quests = 0;

npc_t npc_last = {-1, 0, 0, 0, {-1, 0, ' ', 0}, false, false, false, 0, -1, -1 };  // initalize npc for states 17, 18, 19

// game state (see documentation)
int state = -1;

int num_entities = 0;
entity_t entities[32];

int main(int argc, char *argv[]){
    // initalize rand
    srand (time(NULL));

    // because we need to do this dont forget ok??
    init_maps();

    // set up graphics
    k_init_gfx();

    // init textures
    if (init_displays() < 0) { return -3; }

    printf("DONE \n");

    // init cache_map
    master_index = 0;
    load_map(master_index);

    num_active_quests = 0; // no active quests

    int trade_index = 0; // pointer to trading address

    // build_game_data();

    // main loop
    while (k_this_close_request()){
        // clean texture
        k_refresh_display();

        // handle events
        while (k_get_events()){
#ifndef USE_SDCC // ugly hack #109873276
            // close window if needed
            if (k_get_sf_event_type() == sfEvtClosed)
                sfRenderWindow_close(k_get_window());
            // check keys allow repeats
            if (k_get_sf_event_type() == sfEvtKeyPressed) {
#endif // USE_SDCC
                // handle key presses
                switch( k_get_key() ){
                    case sfKeyEscape:
                        return 0;
                    case sfKeyNum5:
                        state = 16; // rouge like
                        break;
                    case sfKeyQ:
                        if (state == 19) {
                            if (trade_index > 0) trade_index--;
                        } else if (state == 16){
                            trade_index = 0;
                            state = 21;
                        } else if (state == 21){
                            if (trade_index > 0) {
                                trade_index--;
                            }
                        }
                        break;
                    case sfKeyE:
                        if (state == 19) {
                            if (trade_index + 1< npc_last.inventory_size) {
                                trade_index++;
                            }
                        } else if (state == 21){
                            if (trade_index + 1 < num_items) {
                                trade_index++;
                            }
                        }
                    case sfKeyW:
                        if (state == 16) {
                            update_entities();
                            if (character_y - 1 >= 0 && check_next_step(character_x, character_y - 1)) {
                                character_y--;
                            }
                        }
                        break;
                    case sfKeyA:
                        if (state == 16) {
                            update_entities();
                            if (character_x - 1 >= 0  && check_next_step(character_x - 1, character_y)) {
                                    character_x--;
                            }
                        }
                        break;
                    case sfKeyS:
                        if (state == 16) {
                            update_entities();
                            if (character_y + 1 < cached_map.h  && check_next_step(character_x, character_y + 1)) {
                                character_y++;
                            }
                        }
                        break;
                    case sfKeyD:
                        if (state == 16) {
                            update_entities();
                            if (character_x + 1 < cached_map.w  && check_next_step(character_x + 1, character_y)){
                                character_x++;
                            }
                        }
                        break;
                    case sfKeySpace:
                        if (state == -1){
                            state = 16;
                        }
                        break;
                    case sfKeyReturn:
                        if (state == 19){
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
                                    } else {
                                        printf("failed cost check\n");
                                    }
                                } else {
                                    printf("failed item number check\n");
                                }
                            } else {
                                printf("failed array bounds check\n");
                            }
                        } else if (state == 18 || state == 17) {
                            state = 16;
                        } else if (state == 21){
                            if (trade_index >= 0 && trade_index < num_items){
                                switch (inventory[trade_index].type){
                                    case 10: // medkit
                                        health += 250;
                                        break;
                                    default:
                                        break;
                                }

                                // remove item
                                for (int i = trade_index; i < num_items; i++){
                                    inventory[i] = inventory[(i + 1 < num_items) ? i + 1 : i];
                                }
                                if (num_items > 0) num_items --;
                            }
                        }
                        break;
                    case sfKeyTab:
                        printf("STATE: %d SEL OBJ: %d ID_LAST: %d C_X: %d C_Y: %d HEALTH: %d TRADE_INDEX: %d NUM_ITEMS: %d MASTER_INDEX: %d NUM_ENTITES: %d CACHE_W: %d CACHE_H: %d \n", state, selected_object, 0, character_x, character_y, health, trade_index, num_items, master_index, num_entities, cached_map.w, cached_map.h);
                        break;
                    case sfKeyEqual: // increment map pointer
                        if (k_get_sf_key_shift()){
                            master_index ++;
                        }
                        break;
                    case sfKeyDash: // decrement map pointer
                        master_index--;
                        break;
                    case sfKeyBack: // set up changes
                        load_map(master_index);
                        break;
                    case sfKeyY:
                        if (state == 17) {
                            if (num_active_quests + 1 < NUM_QUESTS_MAX){
                                // search for copies
                                bool found = false;
                                for (int i = 1; i < num_active_quests + 1; i++){
                                    printf("LOOKED: NPCQID: %d AQID: %d \n", quest_registry[npc_last.quest_id].id, active_quests[i].quest.id);
                                    if (quest_registry[npc_last.quest_id].id == active_quests[i].quest.id){
                                        found = true;
                                        printf("! DUPLICATE FOUND, NPC ID: %d QUEST ID: %d INDEX: %d \n", npc_last.id, quest_registry[npc_last.quest_id].id, i);
                                        break;
                                    }
                                }

                                if (!found){
                                    // if no duplicates, add to quest list
                                    printf("NO DUPL, adding \n");
                                    active_quests[++num_active_quests] = (quest_active_t) {quest_registry[npc_last.quest_id], 0, false};
                                    state = 16;
                                } else {
                                    // complete check
                                    printf("DUPL, not adding \n");
                                    state = 20;
                                    // increment check
                                }
                            }
                        }
                        break;
                    case sfKeyN:
                        if (state == 17 || state == 18 || state == 19 || state == 21) {
                            state = 16;
                        }
                        break;
                    default:
                        break;
                        // do nothing
                }
#ifndef USE_SDCC
            }
#endif // USE_SDCC
        }

        char tmp[80];
        // draw screen and do stuff
        switch(state){
            case -2:
                // game over?
                draw_game_over();
                break;
            case -1:
                draw_logo();
                for (int i = 0; i < NUM_K_TEXTURES; i++){
                    k_put_rect(i, i, (i > S_WIDTH / 16) ? 1 : 0);
                }
                break;
            case 16:
                draw_rogue();
                //update_entities();
                break;
            case 17:
                // quest
                k_put_text("QUEST", 0, 0);
                break;
            case 18:
                // cutscene
                k_put_text("CUTSCENE", 0, 0);
                break;
            case 19:
                draw_trade(trade_index);
                break;
            case 20:
                sprintf(tmp, "%s", quest_registry[npc_last.quest_id].dialogue[active_quests[0].block_index].dialogue_list[0]);
                k_put_text(tmp, 0, 96);
                break;
            case 21:
                draw_use_item(trade_index);
                break;
            default:
                printf("Intercepted bad state %d /n", state);
                state = 16; // go to rugue to cache problems
                cleardisplay(false);
                break;
        }

        //sfRenderWindow_display(window);
        k_display();
    }

    return 0;
}
