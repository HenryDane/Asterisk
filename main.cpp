#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "main.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "entity.hpp"
#include "levels.hpp"
#include "map.hpp"
using namespace std;

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

item inventory[3] = {{0,2,false,"Glock    ", 5},
                     {1,1,false,"Generic  ", 7},
                     {2,3,false,"Glock    ", 5}};
int num_items = 3;

// game state
/*
-1: boot, 0: main map, 1: view, 2: selecting view, 3: view selected, 4: interacting, 5: mod self,
6: mod self confirm, 7: warp setup, 8: dock, 10: at warp, 16: rogue, 17: quest/talk, 18: cutscene

*/
int state = -1;

// texture
sf::RenderTexture windowTexture;

sf::Font font;

int main(){
//    asteriod_direction = 0;default: r.setTexture(&empty_sector);

    // set up events
    sf::Event event;

    // initalize rand
    srand (time(NULL));

    init_maps();

    cout << "sizeof: " << sizeof(rogue_map_master) << endl;

    // create window
    sf::RenderWindow window(sf::VideoMode(S_WIDTH, S_HEIGHT), "Asterisk");

    // prevent repress
    window.setKeyRepeatEnabled(false);

    // time stuff
    sf::Clock clock;
    sf::Time elapsed;

    // prepare window texture
    if(!windowTexture.create(S_WIDTH, S_HEIGHT)){
        cout << "Failed to build main window texture" << endl;
        return -5;
    }
    //windowTexture.draw(rectangle2);

    // init textures
    if (init_displays() < 0) { return -3; }

    // generate level
    cout << "TERRAIN ..." << endl;
    build_terrain(5, 4, 3);
    cout << "DONE" << endl;

    // generate font
    sf::Text text;
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);

    // init jump position;
    int jump_x = 0;
    int jump_y = 0;
    int jump_s = 0;

    // init cache_map
    //cached_map = rogue_map_master[0].mapdat;
    master_index = 0;
    cached_map = rogue_map_master[master_index].mapdat;
    character_x = rogue_map_master[master_index].coord.x;
    character_y = rogue_map_master[master_index].coord.y;

    // main loop
    while (window.isOpen()){
        // clean texture
        windowTexture.clear();

        // update timer
        elapsed = clock.restart();
        time_entity += elapsed.asMilliseconds();
        time_character += elapsed.asMilliseconds();
        time_rocket += elapsed.asMilliseconds();
        time_warp += (state == 10) ? elapsed.asMilliseconds() : 0;

        // handle events
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return 0;
        while (window.pollEvent(event)){
            // close window if needed
            if (event.type == sf::Event::Closed) window.close();
            // check keys (released to avoid repeated keypresses
            if (event.type == sf::Event::KeyReleased) {
                // handle key presses
                switch(event.key.code){
                    case sf::Keyboard::Num1:
                        if (state > -2 && state != 10) state = 0;
                        break;
                    case sf::Keyboard::Num2:
                        if (state > -2 && state != 10 ) state = 1;
                        break;
                    case sf::Keyboard::Num3:
                        if (state > -2 && state != 10 ) state = 5;
                        break;
                    case sf::Keyboard::Num4:
                        if (state > -2 && state != 10 ) state = 7;
                        jump_x = sector_x;
                        jump_y = sector_y;
                        jump_s = sector_s;
                        break;
                    case sf::Keyboard::Num0:
                        state = -1;
                        break;
                    case sf::Keyboard::Num5:
                        state = 16; // rouge like
                        break;
                    case sf::Keyboard::W:
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
                    case sf::Keyboard::A:
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
                    case sf::Keyboard::S:
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
                    case sf::Keyboard::D:
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
                    case sf::Keyboard::Q:
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
                    case sf::Keyboard::E:
                        if (state == 7){
                            jump_s--;
                            if (jump_s > 3) jump_s = 0;
                            if (jump_s < 0) jump_s = 3;
                        } else if (state == 11){
                            if(flux_clamp + CONFIG_INCREMENT_AMOUNT <= 1000) flux_clamp += CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sf::Keyboard::F:
                        if (state == 11){
                            if(emission_clamp - CONFIG_INCREMENT_AMOUNT >= 0) emission_clamp -= CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sf::Keyboard::R:
                        if (state == 11){
                            if(emission_clamp + CONFIG_INCREMENT_AMOUNT <= 1000) emission_clamp += CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sf::Keyboard::T:
                        if (state == 11){
                            if(themal_clamp + CONFIG_INCREMENT_AMOUNT <= 1000) themal_clamp += CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sf::Keyboard::G:
                        if (state == 11){
                            if(themal_clamp - CONFIG_INCREMENT_AMOUNT >= 0) themal_clamp -= CONFIG_INCREMENT_AMOUNT;
                        }
                        break;
                    case sf::Keyboard::Tilde:
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
                    case sf::Keyboard::Space:
                        if (state == -1){
                            state = 0;
                        } else if (state == 0){
                            fire_missile(ship_x, ship_y, ((facing == 1) ? 1 : 0) + ((facing == 3) ? -1 : 0), ((facing == 2) ? 1 : 0) + ((facing == 0) ? -1 : 0), 5);
                        }
                        break;
                    case sf::Keyboard::Z:
                        tilted = !tilted;
                        break;
                    case sf::Keyboard::Return:
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
                    case sf::Keyboard::Tab:
                        cout << "STATE: " << state << " FACING: " << facing << " SEL OBJ:" << selected_object << endl;
                        cout << "    ID_LAST: " << id_entity_last << " NUM_ENTITY: " << num_entities << endl;
                        cout << "    C_X: " << character_x << " C_Y: " << character_y << " S_X: " << ship_x << " S_Y: " << ship_y << endl;
                        if ( state == 16 ){
                            for (int i = 0; i < cached_map.w * cached_map.h; i++) {
                                cout << " [" << cached_map.tile_type[i] << "] ";
                            }
                            cout << endl;
                        }
                        break;
                    case sf::Keyboard::Equal:
                        if (event.key.shift){
                            master_index ++;
                        }
                        break;
                    case sf::Keyboard::Dash:
                        master_index--;
                        break;
                    case sf::Keyboard::BackSpace:
                        cached_map = rogue_map_master[master_index].mapdat;
                        character_x = rogue_map_master[master_index].coord.x;
                        character_y = rogue_map_master[master_index].coord.y;
                        break;
                    default:
                        break;
                        // do nothing
                }
            }
        }

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
                text.setString("QUEST");
                text.setPosition(0,0);
                windowTexture.draw(text);
                break;
            case 18:
                // cutscene
                text.setString("CUTSCENE");
                text.setPosition(0,0);
                windowTexture.draw(text);
                break;
            case 19:
                // merchant mode;
                text.setString("MERCHANT");
                text.setPosition(0,0);
                windowTexture.draw(text);
                break;
            default:
                cleardisplay(false);
                break;
        }

        // display main texture
        windowTexture.display();
        const sf::Texture& texture = windowTexture.getTexture();
        sf::Sprite sprite(texture);
        sprite.setPosition(0,0);

        // tidy up the window
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
