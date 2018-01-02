#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "main.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "entity.hpp"
#include "levels.hpp"
using namespace std;

// timer
double timerval = 0;
double time_character = 0;
double time_entity = 0;
double time_rocket = 0;

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
int health = 500;
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

// character location
int character_x = 12;
int character_y = 12;
int dx = 0;
int dy = 0;
int facing = 0;

int sector_s = 3;
int sector_x = 5;
int sector_y = 4;

int level = 0;

int selected_object = 0;

// game state
// -1: boot, 0: main map, 1: view, 2: selecting view, 3: view selected, 4: interacting, 5: mod self, 6: mod self confirm, 7: warp setup, 8: dock, 10: at warp
int state = -1;

// texture
sf::RenderTexture windowTexture;

int main(){
//    asteriod_direction = 0;default: r.setTexture(&empty_sector);

    // set up events
    sf::Event event;

    // initalize rand
    srand (time(NULL));

    cout << "sizeof: " << sizeof(level_0_0_tile_data) << endl;

    // create window
    sf::RenderWindow window(sf::VideoMode(S_WIDTH, S_HEIGHT), "Asterisk");
    sf::RectangleShape rectangle(sf::Vector2f(S_WIDTH, S_HEIGHT));

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
    sf::Font font;
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);

    // init jump position;
    int jump_x = 0;
    int jump_y = 0;
    int jump_s = 0;

    // main loop
    while (window.isOpen()){
        // clean texture
        windowTexture.clear();

        // update timer
        elapsed = clock.restart();
        time_entity += elapsed.asMilliseconds();
        time_character += elapsed.asMilliseconds();
        time_rocket += elapsed.asMilliseconds();

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
                        if (state > -2 ) state = 0;
                        break;
                    case sf::Keyboard::Num2:
                        if (state > -2 ) state = 1;
                        break;
                    case sf::Keyboard::Num3:
                        if (state > -2 ) state = 5;
                        break;
                    case sf::Keyboard::Num4:
                        if (state > -2 ) state = 7;
                        jump_x = sector_x;
                        jump_y = sector_y;
                        jump_s = sector_s;
                        break;
                    case sf::Keyboard::Num0:
                        state = -1;
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
                        }
                        break;
                    case sf::Keyboard::A:
                        if (state == 7){
                            jump_x--;
                            if (jump_y > 9) jump_y = 9;
                            if (jump_y < 0) jump_y = 0;
                        } else if (state == 0) {
                            facing = 3;
                        } else if (state == 11){
                            if(fuel_r - CONFIG_INCREMENT_AMOUNT >= 0) fuel_r -= CONFIG_INCREMENT_AMOUNT;
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
                        }
                        break;
                    case sf::Keyboard::D:
                        if (state == 7){
                            jump_x++;
                            if (jump_y > 9) jump_y = 9;
                            if (jump_y < 0) jump_y = 0;
                        } else if (state == 0) {
                            facing = 1;
                        } else if (state == 11){
                            if(flux_clamp - CONFIG_INCREMENT_AMOUNT >= 0) flux_clamp -= CONFIG_INCREMENT_AMOUNT;
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
                        }
                        break;
                    case sf::Keyboard::Space:
                        if (state == -1){
                            state = 0;
                        } else if (state == 0){
                            const char* dat = "!!!";
                            entities[num_entities].type = 5;
                            entities[num_entities].x = character_x;
                            entities[num_entities].y = character_y;
                            for (int k = 0; k < 3; k++){
                                entities[num_entities].data[k] = dat[k];
                            }
                            entities[num_entities].id = id_entity_last;
                            entities[num_entities].vx = ((facing == 1) ? 1 : 0) + ((facing == 3) ? -1 : 0);
                            entities[num_entities].vy = ((facing == 2) ? 1 : 0) + ((facing == 0) ? -1 : 0);
                            num_entities++;
                            id_entity_last++;
                        }
                        break;
                    case sf::Keyboard::Z:
                        facing +=4;
                        break;
                    case sf::Keyboard::X:
                        facing -=4;
                        break;
                    case sf::Keyboard::Return:
                        if (state == 7){
                            state = 11;
                        } else if (state == 8){
                            state = 0;
                        } else if (state == 11){
                            state = 7;
                        } else if (state == 0){
                            state = 8;
                        }
                        break;
                    case sf::Keyboard::Tab:
                        cout << "STATE: " << state << " FACING: " << facing << " SEL OBJ:" << selected_object << endl;
                        cout << "    ID_LAST: " << id_entity_last << " NUM_ENTITY: " << num_entities << endl;
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
                break;
            case 11:
                draw_engine_config();
                break;
            case 8:
                draw_dock();
                break;
            default:
                cleardisplay(false);
                break;
        }

        // display main texture
        // windowTexture.setSmooth(true);
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
