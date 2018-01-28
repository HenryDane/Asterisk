#include <SFML/Graphics.h>
//#include <iostream>
#include <stdio.h>
#include <time.h>
//#include <fstream>
#include "main.h"
#include "display.h"
#include "terrain.h"
#include "entity.h"
#include "levels.h"
#include "map.h"
//using namespace std;

// timer
double timerval = 0;
double time_character = 0;
double time_entity = 0;
double time_rocket = 0;
double time_warp = 0;
int ticks_at_warp = 0;

// enemy defs
entity entities[MAX_ENTITIES];
int num_entities = 0;
int id_entity_last = 0;

// map and screen sizing
int mapdata[HEIGHT][WIDTH];
int screen[S_WIDTH * S_HEIGHT];

// game state: 0 - normal, 1 - ship nav, 2 - combat screen, 3 - character, 4 - port / entity interact
int displaystate = 0;

// character data
int health = 1000;
float experience = 0;
int rockets = 50;
int rounds = 10000;
int credits = 1000;
int fuel = 10000;

// engine data
int flux = 500;
int fuel_r = 500;
int durability = 500;
int response = 500;
int flux_clamp = 1000;
int emission_clamp = 1000;
int themal_clamp = 1000;

// ship data
float vx = 0;
float vy = 0;
float vz = 0;
float x = 0;
float y = 0;
float z = 0;
int thrust_clamp;
int afterburn_clamp;
float thrust;

// character location for ship
int ship_x = 12;
int ship_y = 12;
int character_x = 0;
int character_y = 0;
int dx = 0;
int dy = 0;
int facing = 0;
bool tilted = false;

int sector_s = 0;
int sector_x = 0;
int sector_y = 0;

int level = 0;
int location = 0;

int selected_object = 0;

int e1_g = 8;
int e1_y = 9;
int e2_g = 8;
int e2_y = 9;
int e3_g = 8;
int e3_y = 9;
int e4_g = 8;
int e4_y = 9;
int ticks_for_warp;

item_t inventory[3] = {{0,2,false,"Glock    ", 5},
                     {1,1,false,"Generic  ", 7},
                     {2,3,false,"Glock    ", 5}};
int num_items = 3;

int num_active_quests = 0;

npc_t npc_last = {-1, 0, 0, 0, {-1, 0, ' ', 0}, false, false, false, 0, -1, -1 };  // initalize npc for states 17, 18, 19

// game state
//-1: boot, 0: main map, 1: view, 2: selecting view, 3: view selected, 4: interacting, 5: mod self,
//6: mod self confirm, 7: warp setup, 8: dock, 10: at warp, 16: rogue, 17: quest/talk, 18: cutscene,
//19: trade interface

int state = -1;

// texture
//sfRenderTexture* windowTexture;

sfFont* font;

/* needs to be written for C and needs to actually do stuff
bool build_game_data(){
    // reads in game file data
//    ifstream game_file;
    game_file.open("game_data.txt");

    if(!game_file){
        cout << "Failed to read game data" << endl;
        return false;
    }

    // loop for reading game data

    return true;
}
*/

int main(){
//    asteriod_direction = 0;default: r.setTexture(&empty_sector);

    // set up events
    sfEvent event;

    // initalize rand
    srand (time(NULL));

    init_maps();

    //cout << "sizeof: " << sizeof(rogue_map_master) << endl;

    // create window
    sfVideoMode mode = {800, 600, 32};
    window = sfRenderWindow_create(mode, "Asterisk I", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    font = sfFont_createFromFile("arial.ttf");
    if (!font)
        return 1;

    // prevent repress
    // window.setKeyRepeatEnabled(false);

    // time stuff
    sfClock* clock = sfClock_create();
    sfTime elapsed;

    // prepare window texture (now we just directly use the window instead)
    /*if(!windowTexture.create(S_WIDTH, S_HEIGHT)){
        cout << "Failed to build main window texture" << endl;
        return -5;
    } */
    //windowTexture.draw(rectangle2);

    // init textures
    if (init_displays() < 0) { return -3; }

    // generate level
    //cout << "TERRAIN ..." << endl;
    printf("BUILDING TERRAIN . . . /n");
    build_terrain(5, 4, 3);
    // cout << "DONE" << endl;
    printf("DONE /n");

    // generate font
    sfText* text = sfText_create();
    //if (!font.loadFromFile("res/telegrama_raw.ttf"));
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);

    // init jump position;
    int jump_x = 0;
    int jump_y = 0;
    int jump_s = 0;

    // init cache_map
    master_index = 0;
    cached_map = rogue_map_master[master_index].mapdat;
    character_x = rogue_map_master[master_index].coord.x;
    character_y = rogue_map_master[master_index].coord.y;

    // init quests
    num_active_quests = 0; // no active quests

    // main loop
    while (sfRenderWindow_isOpen(window)){
        // clean texture
        sfRenderWindow_clear(window, sfBlack);

        // update timer
        elapsed = sfClock_restart(clock);
        time_entity += sfTime_asMilliseconds(elapsed);
        time_character += sfTime_asMilliseconds(elapsed);
        time_rocket += sfTime_asMilliseconds(elapsed);
        time_warp += (state == 10) ? sfTime_asMilliseconds(elapsed) : 0;

        // handle events
        //if( (sfKeyEscape)) return 0;
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
                    case sfKeyNum1:
                        if (state > -2 && state != 10) state = 0;
                        break;
                    case sfKeyNum2:
                        if (state > -2 && state != 10 ) state = 1;
                        break;
                    case sfKeyNum3:
                        if (state > -2 && state != 10 ) state = 5;
                        break;
                    case sfKeyNum4:
                        if (state > -2 && state != 10 ) state = 7;
                        jump_x = sector_x;
                        jump_y = sector_y;
                        jump_s = sector_s;
                        break;
                    case sfKeyNum0:
                        state = -1;
                        break;
                    case sfKeyNum5:
                        state = 16; // rouge like
                        break;
                    case sfKeyW:
                        if (state == 7){
                            jump_y--;
                            if (jump_y > 9) jump_y = 9;
                            if (jump_y < 0) jump_y = 0;
                        } else if (state == 0) {
                            facing = 0;
                        } else if (state == 11){
                            if(durability + CONFIG_INCREMENT_AMOUNT <= 1000) durability += CONFIG_INCREMENT_AMOUNT;
                        } else if (state == 1 || state == 5){
                            selected_object++;
                        } else if (state == 16) {
                            if (character_y - 1 >= 0 && check_next_step(character_x, character_y - 1)) {
                                    character_y--;
                            }
                        }
                        break;
                    case sfKeyA:
                        if (state == 7){
                            jump_x--;
                            if (jump_x > 9) jump_x = 9;
                            if (jump_x < 0) jump_x = 0;
                        } else if (state == 0) {
                            facing = 3;
                        } else if (state == 11){
                            if(fuel_r - CONFIG_INCREMENT_AMOUNT >= 0) fuel_r -= CONFIG_INCREMENT_AMOUNT;
                        } else if (state == 16) {
                            if (character_x - 1 >= 0  && check_next_step(character_x - 1, character_y)) {
                                    character_x--;
                            }
                        }
                        break;
                    case sfKeyS:
                        if (state == 7){
                            jump_y++;
                            if (jump_y > 9) jump_y = 9;
                            if (jump_y < 0) jump_y = 0;
                        } else if (state == 0) {
                            facing = 2;
                        } else if (state == 11){
                            if(durability - CONFIG_INCREMENT_AMOUNT >= 0) durability -= CONFIG_INCREMENT_AMOUNT;
                        } else if (state == 16) {
                            if (character_y + 1 < cached_map.h  && check_next_step(character_x, character_y + 1)) {
                                character_y++;
                            }
                        }
                        break;
                    case sfKeyD:
                        if (state == 7){
                            jump_x++;
                            if (jump_x > 9) jump_x = 9;
                            if (jump_x < 0) jump_x = 0;
                        } else if (state == 0) {
                            facing = 1;
                        } else if (state == 11){
                            if(flux_clamp - CONFIG_INCREMENT_AMOUNT >= 0) flux_clamp -= CONFIG_INCREMENT_AMOUNT;
                        } else if (state == 16) {
                            if (character_x + 1 < cached_map.w  && check_next_step(character_x + 1, character_y)){
                                character_x++;
                            }
                        }
                        break;
                    case sfKeyQ:
                        if (state == 7){
                            jump_s++;
                            if (jump_s > 3) jump_s = 0;
                            if (jump_s < 0) jump_s = 3;
                        } else if (state == 0){
                            facing = -10;
                        } else if (state == 11){
                            if(fuel_r + CONFIG_INCREMENT_AMOUNT <= 1000) fuel_r += CONFIG_INCREMENT_AMOUNT;
                        } else if (state == 1 || state == 5){
                            selected_object -= (selected_object - 1 > -1) ? 1 : 0;
                        }
                        break;
                    case sfKeyE:
                        if (state == 7){
                            jump_s--;
                            if (jump_s > 3) jump_s = 0;
                            if (jump_s < 0) jump_s = 3;
                        } else if (state == 11){
                            if(flux_clamp + CONFIG_INCREMENT_AMOUNT <= 1000) flux_clamp += CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sfKeyF:
                        if (state == 11){
                            if(emission_clamp - CONFIG_INCREMENT_AMOUNT >= 0) emission_clamp -= CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sfKeyR:
                        if (state == 11){
                            if(emission_clamp + CONFIG_INCREMENT_AMOUNT <= 1000) emission_clamp += CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sfKeyT:
                        if (state == 11){
                            if(themal_clamp + CONFIG_INCREMENT_AMOUNT <= 1000) themal_clamp += CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sfKeyG:
                        if (state == 11){
                            if(themal_clamp - CONFIG_INCREMENT_AMOUNT >= 0) themal_clamp -= CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sfKeyTilde:
                        if (state == 7){
                            sector_x = jump_x;
                            sector_y = jump_y;
                            sector_s = jump_s;// for moving towards the edge of the screen
                            build_terrain(sector_x, sector_y, sector_s);
                            state = 10;
                            ticks_for_warp = sector_s + sector_x + sector_y + 10;
                            fuel -= ticks_for_warp * 3; // compute ticks
                        }
                        break;
                    case sfKeySpace:
                        if (state == -1){
                            state = 0;
                        } else if (state == 0){
                            fire_missile(ship_x, ship_y, ((facing == 1) ? 1 : 0) + ((facing == 3) ? -1 : 0), ((facing == 2) ? 1 : 0) + ((facing == 0) ? -1 : 0), 5);
                        }
                        break;
                    case sfKeyZ:
                        tilted = !tilted;
                        break;
                    case sfKeyReturn:
                        if (state == 7){
                            state = 11;
                        } else if (state == 8){
                            state = 0; // undock
                        } else if (state == 11){
                            state = 7; // warp config
                        } else if (state == 0){
                            state = 8; // dock

                            // search for everything nearby and go to the first thing we find
                            // see issue #14

                            // check if found object has a map, if yes then load it and go to state 16 else make error msg and wait for toggle to state 0
                        } else if (state == 19 || state == 18 || state == 17) {
                            state = 16;
                        }
                        break;
                    case sfKeyTab:
                        /*cout << "STATE: " << state << " FACING: " << facing << " SEL OBJ:" << selected_object << endl;
                        cout << "    ID_LAST: " << id_entity_last << " NUM_ENTITY: " << num_entities << endl;
                        cout << "    C_X: " << character_x << " C_Y: " << character_y << " S_X: " << ship_x << " S_Y: " << ship_y << endl;
                        if ( state == 16 ){
                            for (int i = 0; i < cached_map.w * cached_map.h; i++) {
                                cout << " [" << cached_map.tile_type[i] << "] ";
                            }
                            cout << endl;
                        }*/
                        break;
                    case sfKeyEqual:
                        if (event.key.shift){
                            master_index ++;
                        }
                        break;
                    case sfKeyDash:
                        master_index--;
                        break;
                    case sfKeyBack:
                        cached_map = rogue_map_master[master_index].mapdat;
                        character_x = rogue_map_master[master_index].coord.x;
                        character_y = rogue_map_master[master_index].coord.y;
                        break;
                    case sfKeyY:
                        if (state == 17) {
                            if (num_active_quests + 1 < NUM_QUESTS_MAX){
                                // search for copies
                                bool found = false;
                                for (int i = 0; i < num_active_quests + 1; i++){
                                    //cout << "LOOKED: NPCQID:" << quest_registry[npc_last.quest_id].id << " AQID:" << active_quests[i].quest.id << endl;
                                    if (quest_registry[npc_last.quest_id].id == active_quests[i].quest.id){
                                        found = true;
                                        break;
                                    }
                                }

                                if (!found){
                                    // if no duplicates, add to quest list
                                    active_quests[++num_active_quests] = (quest_active_t) {quest_registry[npc_last.quest_id], 0, false};
                                } else {
                                    // complete check

                                    // increment check
                                }
                                state = 16;
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
        // draw screen and do stuff
        switch(state){
            case -2:
                // game over?
                draw_logo();
                break;
            case -1:
                draw_logo();
                break;
            case 0:
                update_entities();
            case 2:
                display(0, false);
                break;
            case 1:
            case 5:
                draw_menu(0);
                break;
            case 7:
                draw_prewarp(jump_x, jump_y, jump_s);
                break;
            case 10:
                draw_warp(jump_x, jump_y, jump_s);
                if (time_warp > 500){
                    time_warp = 0;
                    update_warp_interface();
                    ticks_at_warp++;
                    if (ticks_at_warp > ticks_for_warp){
                        state = 0;
                        ticks_at_warp = 0;
                    }

                }
                break;
            case 11:
                draw_engine_config();
                break;
            case 8:
                draw_dock(); // should not have any graphics unless there is an error
                break;
            case 16:
                draw_rouge();
                break;
            case 17:
                // quest
                sfText_setString(text, "QUEST");
                textsetPosition(0,0);
                sfRenderWindow_drawText(window, text, NULL);
                if (npc_last.id > 0){
                    char tmp[80];
                    char tmp_t342[32] = "hello world";
                    for (int i = 0; i < quest_registry[npc_last.quest_id].title_len; i++){
                        tmp_t342[i] = quest_registry[npc_last.quest_id].title[i];
                    }
                    sprintf(tmp, "NPC [ID: %d] HAS QUEST [%s]. DO YOU ACCEPT [y / n]?", npc_last.id, tmp_t342);
                    sfText_setString(text, tmp);
                    textsetPosition(0,16);
                    sfRenderWindow_drawText(window, text, NULL);
                }

                if (num_active_quests + 1 > NUM_QUESTS_MAX ){
                    sfText_setString(text, "YOU CAN NOT ACCEPT ANY MORE QUESTS");
                    textsetPosition(0,32);
                    sfRenderWindow_drawText(window, text, NULL);
                }
                break;
            case 18:
                // cutscene
                sfText_setString(text, "CUTSCENE");
                textsetPosition(0,0);
                sfRenderWindow_drawText(window, text, NULL);
                break;
            case 19:
                // merchant mode;
                sfText_setString(text, "MERCHANT");
                textsetPosition(0,0);
                sfRenderWindow_drawText(window, text, NULL);

                //cout << "FOUND IVEN OF SIZE: " << npc_last.inventory_size << endl;
                for (int i = 0; i < npc_last.inventory_size; i++){
                    switch(npc_last.inventory[i].type){
                        default:
                            sfText_setString(text, "[DEFAULT ITEM]");
                    }
                    textsetPosition(32, (l + 1) * 16);
                    sfRenderWindow_drawText(window, text, NULL);
                    sfText_setString(text, npc_last.inventory[i].data);
                    textsetPosition(32, (l + 2) * 16);
                    sfRenderWindow_drawText(window, text, NULL);
                    l += 3;
                }
                break;
            default:
                cleardisplay(false);
                break;
        }

        // display main texture
        //windowTexture.display();
        //const sf::Texture& texture = windowTexture.getTexture();
        //sf::Sprite sprite(texture);
        //sprite.setPosition(0,0);

        // tidy up the window
        //window.clear();
        //window.draw(sprite);
        sfRenderWindow_display(window);
    }

    return 0;
}
