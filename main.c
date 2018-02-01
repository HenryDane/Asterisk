#include <SFML/Graphics.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "display.h"
#include "entity.h"
#include "map.h"

sfRenderWindow* window;

// timer
double timerval = 0;
double time_entity = 0;

// game state: 0 - normal, 1 - ship nav, 2 - combat screen, 3 - character, 4 - port / entity interact
int displaystate = 0;

// character data
int health = 1000;
float experience = 0;
int credits = 1000;
int fuel = 10000;

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

sfFont* font;

bool build_game_data(){
    // reads in game file data
    FILE * game_file;
    game_file = fopen("game_data.txt", "r");

    if(!game_file){
        printf("Failed to read game file");
        return false;
    }

    // loop for reading game data
    return true;
}

int main(){
    // set up events
    sfEvent event;

    // initalize rand
    srand (time(NULL));

    // because we need to do this dont forget ok??
    init_maps();

    // create window
    sfVideoMode mode = {S_WIDTH, S_HEIGHT, 32};
    window = sfRenderWindow_create(mode, "Asterisk I", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    // gimme some fontness
    font = sfFont_createFromFile("res/telegrama_raw.ttf");
    if (!font)
        return 1;

    // time stuff
    sfClock* clock = sfClock_create();
    sfTime elapsed;

    // init textures
    if (init_displays() < 0) { return -3; }

    // cout << "DONE" << endl;
    printf("DONE \n");

    // generate font
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);

    // init cache_map
    master_index = 0;
    cached_map = rogue_map_master[master_index].mapdat;
    character_x = rogue_map_master[master_index].coord.x;
    character_y = rogue_map_master[master_index].coord.y;

    // init quests
    num_active_quests = 0; // no active quests

    int trade_index = 0;

    // because csfml wont do colors idk why
    sfColor color_blk;
    color_blk.r = 0;
    color_blk.g = 0;
    color_blk.b = 0;
    color_blk.a = 255;

    // main loop
    while (sfRenderWindow_isOpen(window)){
        // clean texture
        sfRenderWindow_clear(window, color_blk);

        // update timer
        elapsed = sfClock_restart(clock);

        // handle events
        while (sfRenderWindow_pollEvent(window, &event)){
            // close window if needed
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            // check keys (released to avoid repeated keypresses
            if (event.type == sfEvtKeyReleased) {
                // handle key presses
                switch(event.key.code){
                    case sfKeyEscape:
                        return 0;
                    case sfKeyNum5:
                        state = 16; // rouge like
                        break;
                    case sfKeyQ:
                        if (state == 19) {
                            trade_index--;
                        }
                        break;
                    case sfKeyE:
                        if (state == 19) {
                            trade_index++;
                        }
                    case sfKeyW:
                        if (state == 16) {
                            if (character_y - 1 >= 0 && check_next_step(character_x, character_y - 1)) {
                                character_y--;
                            }
                        }
                        break;
                    case sfKeyA:
                        if (state == 16) {
                            if (character_x - 1 >= 0  && check_next_step(character_x - 1, character_y)) {
                                    character_x--;
                            }
                        }
                        break;
                    case sfKeyS:
                        if (state == 16) {
                            if (character_y + 1 < cached_map.h  && check_next_step(character_x, character_y + 1)) {
                                character_y++;
                            }
                        }
                        break;
                    case sfKeyD:
                        if (state == 16) {
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
                                        //inventory[num_items] = npc_last.inventory[trade_index];
                                        strcpy(inventory[num_items].data, npc_last.inventory[trade_index].data);
                                        // = npc_last.inventory[trade_index].data;
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
                        }
                        break;
                    case sfKeyTab:
                        printf("STATE: %d SEL OBJ: %d ID_LAST: %d C_X: %d C_Y: %d /n", state, selected_object, 0, character_x, character_y);
                        break;
                    case sfKeyEqual: // increment map pointer
                        if (event.key.shift){
                            master_index ++;
                        }
                        break;
                    case sfKeyDash: // decrement map pointer
                        master_index--;
                        break;
                    case sfKeyBack: // set up changes
                        cached_map = rogue_map_master[master_index].mapdat;
                        character_x = rogue_map_master[master_index].coord.x;
                        character_y = rogue_map_master[master_index].coord.y;
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
                                //state = 16;
                            } else {
                                //cout << "FAILED TO ADD, NAQ:" << num_active_quests << " NAQ+1:" << num_active_quests + 1 << " NAQM:" << NUM_QUESTS_MAX << endl;
                            }
                        }
                        break;
                    case sfKeyN:
                        if (state == 17 || state == 18 || state == 19) {
                            state = 16;
                        }
                        break;
                    default:
                        break;
                        // do nothing
                }
            }
        }

        int l = 1;
        char tmp[80];
        // draw screen and do stuff
        switch(state){
            case -2:
                // game over?
                draw_logo();
                break;
            case -1:
                draw_logo();
                break;
            case 16:
                draw_rogue();
                break;
            case 17:
                // quest
                sfText_setString(text, "QUEST");
                textsetPosition( text, 0,0);
                sfRenderWindow_drawText(window, text, NULL);
                break;
            case 18:
                // cutscene
                sfText_setString(text, "CUTSCENE");
                textsetPosition( text, 0,0);
                sfRenderWindow_drawText(window, text, NULL);
                break;
            case 19:
                draw_trade(trade_index);
                break;
            case 20:
                sprintf(tmp, "%s", quest_registry[npc_last.quest_id].dialogue[active_quests[0].block_index].dialogue_list[0]);
                sfText_setString(text, tmp);
                textsetPosition(text, 0, 96);
                sfRenderWindow_drawText(window, text, NULL);
                break;
            default:
                printf("Intercepted bad state %d /n", state);
                state = 16; // go to rugue to cache problems
                cleardisplay(false);
                break;
        }

        sfRenderWindow_display(window);
    }

    return 0;
}
