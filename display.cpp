#include "main.hpp"
#include "levels.hpp"
#include <iostream>
using namespace std;

// texture definitions
sf::Texture character_t;
sf::Texture character_l;
sf::Texture character_b;
sf::Texture character_r;
sf::Texture enemy_t;
sf::Texture enemy_l;
sf::Texture enemy_b;
sf::Texture enemy_r;
sf::Texture asteriod_1;
sf::Texture asteriod_2;
sf::Texture asteriod_3;
sf::Texture debug;
sf::Texture wall;
sf::Texture rockets_tex;
sf::Texture station;
sf::Texture ice_station;
sf::Texture logo;
sf::Texture empty_sector;
sf::Texture ice_field;
sf::Texture nebula;
sf::Texture system_texture;
sf::Texture debris;
sf::Texture green;
sf::Texture red;
sf::Texture yellow;
sf::Texture star;
sf::Texture heart;
sf::Texture critical;
sf::Texture full_health;
sf::Texture bronze;
sf::Texture silver;
sf::Texture gold;
sf::Texture purple_heart;
sf::Texture exhaust_top;
sf::Texture exhaust_bottom;
sf::Texture exhaust_left;
sf::Texture exhaust_right;

int g_state = 0;

int init_displays(void){
	for (int i = 0; i < S_HEIGHT * S_WIDTH; i++){
		screen[i] = 32;
	}

	for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            mapdata[i][j] = 0;
        }
	}

    if(!character_t.loadFromFile("res/character-top.png")) return -1;
    if(!character_b.loadFromFile("res/character-bottom.png")) return -1;
    if(!character_r.loadFromFile("res/character-right.png")) return -1;
    if(!character_l.loadFromFile("res/character-left.png")) return -1;
    if(!enemy_t.loadFromFile("res/enemy-top.png")) return -1;
    if(!enemy_r.loadFromFile("res/enemy-right.png")) return -1;
    if(!enemy_b.loadFromFile("res/enemy-bottom.png")) return -1;
    if(!enemy_l.loadFromFile("res/enemy-left.png")) return -1;
    if(!asteriod_1.loadFromFile("res/asteriod-1.png")) return -1;
    if(!asteriod_2.loadFromFile("res/asteriod-2.png")) return -1;
    if(!asteriod_3.loadFromFile("res/asteriod-3.png")) return -1;
    if(!debug.loadFromFile("res/debug.png")) return -1;
    if(!wall.loadFromFile("res/wall.png")) return -1;
    if(!rockets_tex.loadFromFile("res/rockets-2.png")) return -1;
    if(!station.loadFromFile("res/station.png")) return -1;
    if(!ice_station.loadFromFile("res/ice-station.png")) return -1;
    if(!logo.loadFromFile("res/logo.png")) return -1;
    if(!empty_sector.loadFromFile("res/empty_sector.png")) return -1;
    if(!nebula.loadFromFile("res/ice-field.png")) return -1;
    if(!ice_field.loadFromFile("res/nebula.png")) return -1;
    if(!system_texture.loadFromFile("res/system.png")) return -1;
    if(!debris.loadFromFile("res/flak-2.png")) return -1;
    if(!red.loadFromFile("res/red.png")) return -1;
    if(!yellow.loadFromFile("res/yellow.png")) return -1;
    if(!green.loadFromFile("res/green.png")) return -1;
    if(!star.loadFromFile("res/yellow.png")) return -1;
    if(!heart.loadFromFile("res/full_health.png")) return -1;
    if(!critical.loadFromFile("res/heart_low.png")) return -1;
    if(!full_health.loadFromFile("res/heart.png")) return -1;
    if(!purple_heart.loadFromFile("res/purple.png")) return -1;
    if(!gold.loadFromFile("res/bronze.png")) return -1;
    if(!silver.loadFromFile("res/silver.png")) return -1;
    if(!bronze.loadFromFile("res/gold.png")) return -1;
    if(!exhaust_bottom.loadFromFile("res/exhaust_bot.png")) return -1;
    if(!exhaust_left.loadFromFile("res/exhaust_lef.png")) return -1;
    if(!exhaust_right.loadFromFile("res/exhaust_rig.png")) return -1;
    if(!exhaust_top.loadFromFile("res/exhaust_top.png")) return -1;

    return 0;
}

void cleardisplay(bool _debug){
    sf::RectangleShape r(sf::Vector2f(16, 16));
    if (_debug){
        r.setTexture(&debug);
    } else {
        r.setTexture(&wall);
    }
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j <  HEIGHT; j++){
            r.setPosition(i * 16, j * 16);
            windowTexture.draw(r);
        }
    }
}

void draw_warp_alt(){
    sf::RectangleShape r(sf::Vector2f(16, 16));
    for( int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < HEIGHT; j++){
            r.setPosition(i * 16, j * 16);
            r.setTexture(&debug);
            windowTexture.draw(r);
        }
    }
}

void draw_rouge(){
    sf::RectangleShape r(sf::Vector2f(16, 16));
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < HEIGHT; j++){
            r.setPosition(i * 16, j * 16);
            switch (map_test[(i + character_x) % 16][(j + character_y) % 16]){
                case 0:
                    r.setTexture(&wall);
                    break;
                case 1:
                    r.setTexture(&asteriod_2);
                    break;
                default:
                    r.setTexture(&system_texture);
            }
            windowTexture.draw(r);
        }
    }
    r.setPosition(25 * 16, 17 * 16);
    r.setTexture(&green);
    windowTexture.draw(r);
}

void draw_engine_config(){
    sf::RectangleShape r(sf::Vector2f(16, 16));
    sf::Text text;
    sf::Font font;
    char tim[80];
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);

    text.setString("Engine Configuration Window");
    text.setPosition(32, 32);
    windowTexture.draw(text);

    text.setColor(sf::Color::Green);
    text.setString("E1");
    text.setPosition(32, 368);
    windowTexture.draw(text);
    text.setString("E2");
    text.setPosition(112, 368);
    windowTexture.draw(text);
    text.setString("E3");
    text.setPosition(192, 368);
    windowTexture.draw(text);
    text.setString("E4");
    text.setPosition(272, 368);
    windowTexture.draw(text);
    text.setColor(sf::Color::White);
    for(int i = 0; i < 2; i++){
        for (int j = 0; j < 10; j++){
            r.setPosition(32 + 16 * i, 400 + j * 16);
            if ( j >= e1_y) {
                r.setTexture(&red);
            } else if (j >= e1_g && j < e1_y){
                r.setTexture(&yellow);
            } else {
                r.setTexture(&green);
            }
            windowTexture.draw(r);
            r.setPosition(112 + 16 * i, 400 + j * 16);
            if ( j >= e2_y) {
                r.setTexture(&red);
            } else if (j >= e2_g && j < e2_y){
                r.setTexture(&yellow);
            } else {
                r.setTexture(&green);
            }
            windowTexture.draw(r);
            r.setPosition(192 + 16 * i, 400 + j * 16);
            if ( j >= e3_y) {
                r.setTexture(&red);
            } else if (j >= e3_g && j < e3_y){
                r.setTexture(&yellow);
            } else {
                r.setTexture(&green);
            }
            windowTexture.draw(r);
            r.setPosition(272 + 16 * i, 400 + j * 16);
            if ( j >= e4_y) {
                r.setTexture(&red);
            } else if (j >= e4_g && j < e4_y){
                r.setTexture(&yellow);
            } else {
                r.setTexture(&green);
            }
            windowTexture.draw(r);
        }
    }

    text.setString("Flux:Fuel Ratio     [A][Q]");
    text.setPosition(32, 62);
    windowTexture.draw(text);
    text.setString("Dur.:Res. Ratio     [S][W]");
    text.setPosition(32, 110);
    windowTexture.draw(text);
    text.setString("Flux Clamp          [D][E]");
    text.setPosition(32, 158);
    windowTexture.draw(text);
    text.setString("Emission Clamp      [F][R]");
    text.setPosition(32, 206);
    windowTexture.draw(text);
    text.setString("Thermal Clamp       [G][T]");
    text.setPosition(32, 254);
    windowTexture.draw(text);
    text.setString("Engine Status:");
    text.setPosition(32, 350);
    windowTexture.draw(text);
    for (int i = 2; i < 20; i++){
        if(i - 1 < fuel_r / 55){
            r.setTexture(&green);
        } else {
            r.setTexture(&red);
        }
        r.setPosition(i * 16, 80);
        windowTexture.draw(r);
        if(i - 1 < durability / 55){
            r.setTexture(&green);
        } else {
            r.setTexture(&red);
        }
        r.setPosition(i * 16, 128);
        windowTexture.draw(r);
        if(i - 1 < flux_clamp / 55){
            r.setTexture(&green);
        } else {
            r.setTexture(&red);
        }
        r.setPosition(i * 16, 176);
        windowTexture.draw(r);
        if(i - 1 < emission_clamp / 55){
            r.setTexture(&green);
        } else {
            r.setTexture(&red);
        }
        r.setPosition(i * 16, 224);
        windowTexture.draw(r);
        if(i - 1 < themal_clamp / 55){
            r.setTexture(&green);
        } else {
            r.setTexture(&red);
        }
        r.setPosition(i * 16, 272);
        windowTexture.draw(r);
    }

    windowTexture.display();
}

void draw_prewarp(int x, int y, int s){
    sf::RectangleShape r(sf::Vector2f(16, 16));
    sf::Text text;
    sf::Font font;
    char tim[80];
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);

    // pick default texture
    r.setTexture(&empty_sector);
    for (int i = 0; i < 30; i+=3){
        for (int j = 0; j < 30; j+=3){
            // draw sector 0
            switch (s){
                case 0:
                    switch(level_0_0[i / 3 ][j / 3]){
                        case 0: r.setTexture(&empty_sector); break;
                        case 1: r.setTexture(&station); break;
                        case 2: r.setTexture(&ice_field); break;
                        case 3: r.setTexture(&nebula); break;
                        case 4: r.setTexture(&system_texture); break;
                        // case 5: r.setTexture(&star); break;
                        default: r.setTexture(&empty_sector);
                    }
                    for (int n = 0; n < 3; n++){
                        for (int m = 0; m < 3; m++){
                            r.setPosition(((i + n) * 16) , (j + m) * 16 + 16);
                            windowTexture.draw(r);
                        }
                    }
                    break;
                case 1:
                    // draw sector 1
                    switch(level_0_1[i / 3 ][j / 3]){
                        case 0: r.setTexture(&empty_sector); break;
                        case 1: r.setTexture(&station); break;
                        case 2: r.setTexture(&ice_field); break;
                        case 3: r.setTexture(&nebula); break;
                        case 4: r.setTexture(&system_texture); break;
                        // case 5: r.setTexture(&star); break;
                        default: r.setTexture(&empty_sector);
                    }
                    for (int n = 0; n < 3; n++){
                        for (int m = 0; m < 3; m++){
                            r.setPosition(((i + n) * 16) , (j + m) * 16 + 16);
                            windowTexture.draw(r);
                        }
                    }
                    break;
                case 2:
                    // draw sector 2
                    switch(level_0_2[i / 3 ][j / 3]){
                        case 0: r.setTexture(&empty_sector); break;
                        case 1: r.setTexture(&station); break;
                        case 2: r.setTexture(&ice_field); break;
                        case 3: r.setTexture(&nebula); break;
                        case 4: r.setTexture(&system_texture); break;
                        // case 5: r.setTexture(&star); break;
                        default: r.setTexture(&empty_sector);
                    }
                    for (int n = 0; n < 3; n++){
                        for (int m = 0; m < 3; m++){
                            r.setPosition(((i + n) * 16) , (j + m) * 16 + 16);
                            windowTexture.draw(r);
                        }
                    }
                    break;
                case 3:
                     // draw sector 3
                    switch(level_0_3[i / 3 ][j / 3]){
                        case 0: r.setTexture(&empty_sector); break;
                        case 1: r.setTexture(&station); break;
                        case 2: r.setTexture(&ice_field); break;
                        case 3: r.setTexture(&nebula); break;
                        case 4: r.setTexture(&system_texture); break;
                        // case 5: r.setTexture(&star); break;
                        default: r.setTexture(&empty_sector);
                    }
                    for (int n = 0; n < 3; n++){
                        for (int m = 0; m < 3; m++){
                            r.setPosition(((i + n) * 16) , (j + m) * 16 + 16);
                            windowTexture.draw(r);
                        }
                    }
                    break;
                default : cout << "REEEEEEE" << endl;
            }
        }
    }

    // draw jump position
    r.setPosition(x * 48 + 16, y * 48 + 16);
    r.setTexture(&character_t);
    windowTexture.draw(r);

    // initalize temp
    char temp_data[16];
    for (int i = 0; i < 16; i++){
        temp_data[i] = 0;
    }

    // search, inform
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
    text.setString(temp_data);
    text.setPosition(496, 128);
    windowTexture.draw(text);


    // draw cuttent position
    if (sector_s == s) {
        r.setPosition(sector_x * 48 + 16, sector_y * 48 + 16);
    }
    r.setTexture(&enemy_t);
    windowTexture.draw(r);

    // draw text
    text.setString("Warp Config System v12.81.20392");
    text.setPosition(496, 16);
    windowTexture.draw(text);
    text.setString("Quadrant: Epsilon");
    text.setPosition(496, 48);
    windowTexture.draw(text);
    sprintf(tim, "Jump Sector: %d - %d - %d", s, x, y);
    text.setString(tim);
    text.setPosition(496, 64);
    windowTexture.draw(text);
    sprintf(tim, "Current Sector: %d - %d - %d", sector_s, sector_x, sector_y);
    text.setString(tim);
    text.setPosition(496, 80);
    windowTexture.draw(text);
    text.setString("Warp Engine Integrity: 87%");
    text.setPosition(496, 96);
    windowTexture.draw(text);
    text.setString("[WASD] to move jump to coords");
    text.setPosition(496, 304);
    windowTexture.draw(text);
    text.setString("[~] to confirm jump");
    text.setPosition(496, 320);
    windowTexture.draw(text);

    text.setString("Engine Status:");
    text.setPosition(496, 192);
    windowTexture.draw(text);
    text.setString("[Enter] to configure");
    text.setPosition(496, 208);
    windowTexture.draw(text);
    text.setString("Fuel: 9678 / 10000");
    text.setPosition(496, 224);
    windowTexture.draw(text);
    text.setString("Peak Flux: 0.6772 ABCD");
    text.setPosition(496, 240);
    windowTexture.draw(text);
    text.setString("Reserved Flux: 10.2821");
    text.setPosition(496, 256);
    windowTexture.draw(text);
    text.setString("Time Per Cycle: 1h 17m 57s");
    text.setPosition(496, 272);
    windowTexture.draw(text);

    text.setColor(sf::Color::Green);
    text.setString("E1");
    text.setPosition(496, 368);
    windowTexture.draw(text);
    text.setString("E2");
    text.setPosition(576, 368);
    windowTexture.draw(text);
    text.setString("E3");
    text.setPosition(656, 368);
    windowTexture.draw(text);
    text.setString("E4");
    text.setPosition(736, 368);
    windowTexture.draw(text);
    text.setColor(sf::Color::White);

    for(int i = 0; i < 2; i++){
        for (int j = 0; j < 10; j++){
            r.setPosition(496 + 16 * i, 400 + j * 16);
            if ( j >= e1_y) {
                r.setTexture(&red);
            } else if (j >= e1_g && j < e1_y){
                r.setTexture(&yellow);
            } else {
                r.setTexture(&green);
            }
            windowTexture.draw(r);
            r.setPosition(576 + 16 * i, 400 + j * 16);
            if ( j >= e2_y) {
                r.setTexture(&red);
            } else if (j >= e2_g && j < e2_y){
                r.setTexture(&yellow);
            } else {
                r.setTexture(&green);
            }
            windowTexture.draw(r);
            r.setPosition(656 + 16 * i, 400 + j * 16);
            if ( j >= e3_y) {
                r.setTexture(&red);
            } else if (j >= e3_g && j < e3_y){
                r.setTexture(&yellow);
            } else {
                r.setTexture(&green);
            }
            windowTexture.draw(r);
            r.setPosition(736 + 16 * i, 400 + j * 16);
            if ( j >= e4_y) {
                r.setTexture(&red);
            } else if (j >= e4_g && j < e4_y){
                r.setTexture(&yellow);
            } else {
                r.setTexture(&green);
            }
            windowTexture.draw(r);
        }
    }
    // make it good fam
    windowTexture.display();
}

void draw_warp(int x, int y, int s){
    sf::RectangleShape r(sf::Vector2f(16, 16));
    sf::Text text;
    sf::Font font;
    char tim[80];
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);

    // pick default texture
    r.setTexture(&empty_sector);
    for (int i = 1; i < 11; i++){
        for (int j = 1; j < 11; j++){
            // draw sector 1
            switch(level_0_0[i - 1][j - 1]){
                case 0: r.setTexture(&empty_sector); break;
                case 1: r.setTexture(&station); break;
                case 2: r.setTexture(&ice_field); break;
                case 3: r.setTexture(&nebula); break;
                case 4: r.setTexture(&system_texture); break;
            }
            r.setPosition((i * 16) , j * 16);
            windowTexture.draw(r);

            // draw sector 1
            switch(level_0_1[i - 1][j - 1]){
                case 0: r.setTexture(&empty_sector); break;
                case 1: r.setTexture(&station); break;
                case 2: r.setTexture(&ice_field); break;
                case 3: r.setTexture(&nebula); break;
                case 4: r.setTexture(&system_texture); break;
            }
            r.setPosition((i + 11) * 16 , j * 16);
            windowTexture.draw(r);

            // draw sector 3
            switch(level_0_3[i - 1][j - 1]){
                case 0: r.setTexture(&empty_sector); break;
                case 1: r.setTexture(&station); break;
                case 2: r.setTexture(&ice_field); break;
                case 3: r.setTexture(&nebula); break;
                case 4: r.setTexture(&system_texture); break;
            }
            r.setPosition(i * 16 , (j + 11) * 16);
            windowTexture.draw(r);

            // draw sector 2
            switch(level_0_2[i - 1][j - 1]){
                case 0: r.setTexture(&empty_sector); break;
                case 1: r.setTexture(&station); break;
                case 2: r.setTexture(&ice_field); break;
                case 3: r.setTexture(&nebula); break;
                case 4: r.setTexture(&system_texture); break;
            }
            r.setPosition((i + 11) * 16 , (j + 11) * 16);
            windowTexture.draw(r);
        }
    }

    // draw jump position
    if (s == 0) {
        r.setPosition((x + 1) * 16, (y + 1) * 16);
    } else if (s == 1){
        r.setPosition((x + 1) * 16 + 176, (y + 1) * 16);
    } else if (s == 2){
        r.setPosition((x + 1) * 16 + 176, (y + 1) * 16 + 176);
    } else if (s == 3){
        r.setPosition((x + 1) * 16, (y + 1) * 16 + 176);
    }
    r.setTexture(&character_t);
    windowTexture.draw(r);

    // initalize temp
    char temp_data[16];
    for (int i = 0; i < 16; i++){
        temp_data[i] = 0;
    }

    // search, inform
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
    text.setString(temp_data);
    text.setPosition(368, 112);
    windowTexture.draw(text);


    // draw cuttent position
    if (sector_s == 0) {
        r.setPosition((sector_x + 1) * 16, (sector_y+ 1) * 16);
    } else if (sector_s == 1){
        r.setPosition((sector_x + 1) * 16 + 176, (sector_y + 1) * 16);
    } else if (sector_s == 2){
        r.setPosition((sector_x + 1) * 16 + 176, (sector_y + 1) * 16 + 176);
    } else if (sector_s == 3){
        r.setPosition((sector_x + 1) * 16, (sector_y + 1) * 16 + 176);
    }
    r.setTexture(&enemy_t);
    windowTexture.draw(r);

    // draw text
    text.setString("Warp Config System v12.81.20392");
    text.setPosition(368, 16);
    windowTexture.draw(text);
    text.setString("Quadrant: Epsilon");
    text.setPosition(368, 48);
    windowTexture.draw(text);
    sprintf(tim, "Jump Sector: %d - %d - %d    Current Sector: %d - %d - %d", s, x, y, sector_s, sector_x, sector_y);
    text.setString(tim);
    text.setPosition(368, 64);
    windowTexture.draw(text);
    text.setString("Warp Engine Integrity: 87%");
    text.setPosition(368, 80);
    windowTexture.draw(text);

    text.setString("Engine Status:");
    text.setPosition(368, 368);
    windowTexture.draw(text);
    text.setString("[Enter] to configure");
    text.setPosition(368, 384);
    windowTexture.draw(text);
    text.setString("Fuel: 9678 / 10000");
    text.setPosition(368, 416);
    windowTexture.draw(text);
    text.setString("Peak Flux: 0.6772 A--DE-G-");
    text.setPosition(368, 432);
    windowTexture.draw(text);
    text.setString("Reserved Flux: 10.2821");
    text.setPosition(368, 448);
    windowTexture.draw(text);
    text.setString("Time Per Cycle: 1h 17m 57s");
    text.setPosition(368, 480);
    windowTexture.draw(text);

    text.setColor(sf::Color::Green);
    text.setString("E1");
    text.setPosition(32, 368);
    windowTexture.draw(text);
    text.setString("E2");
    text.setPosition(112, 368);
    windowTexture.draw(text);
    text.setString("E3");
    text.setPosition(192, 368);
    windowTexture.draw(text);
    text.setString("E4");
    text.setPosition(272, 368);
    windowTexture.draw(text);
    text.setColor(sf::Color::White);
    for(int i = 0; i < 2; i++){
        for (int j = 0; j < 10; j++){
            r.setPosition(32 + 16 * i, 400 + j * 16);
            if ( j >= e1_y) {
                r.setTexture(&red);
            } else if (j >= e1_g && j < e1_y){
                r.setTexture(&yellow);
            } else {
                r.setTexture(&green);
            }
            windowTexture.draw(r);
            r.setPosition(112 + 16 * i, 400 + j * 16);
            if ( j >= e2_y) {
                r.setTexture(&red);
            } else if (j >= e2_g && j < e2_y){
                r.setTexture(&yellow);
            } else {
                r.setTexture(&green);
            }
            windowTexture.draw(r);
            r.setPosition(192 + 16 * i, 400 + j * 16);
            if ( j >= e3_y) {
                r.setTexture(&red);
            } else if (j >= e3_g && j < e3_y){
                r.setTexture(&yellow);
            } else {
                r.setTexture(&green);
            }
            windowTexture.draw(r);
            r.setPosition(272 + 16 * i, 400 + j * 16);
            if ( j >= e4_y) {
                r.setTexture(&red);
            } else if (j >= e4_g && j < e4_y){
                r.setTexture(&yellow);
            } else {
                r.setTexture(&green);
            }
            windowTexture.draw(r);
        }
    }

    // make it good fam
    windowTexture.display();
}

void draw_self(){
    sf::RectangleShape r(sf::Vector2f(16, 16));
    sf::Text text;
    sf::Font font;
    char tim[80];
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);

    cleardisplay(false);

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(PAD_LEFT, PAD_TOP)),
        sf::Vertex(sf::Vector2f(S_WIDTH - PAD_RIGHT, PAD_TOP)),
        sf::Vertex(sf::Vector2f(S_WIDTH - PAD_RIGHT, S_HEIGHT - PAD_BOTTOM)),
        sf::Vertex(sf::Vector2f(PAD_LEFT, S_HEIGHT - PAD_BOTTOM))
    };
    windowTexture.draw(line, 4, sf::Lines);

    text.setString("Your starcruiser: ");
    text.setPosition(PAD_LEFT, PAD_TOP);
    windowTexture.draw(text);

    sprintf(tim, "Health: %d / 500", health);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 160, PAD_TOP + 32);
    windowTexture.draw(text);

    sprintf(tim, "Experience: %d / 5000", experience);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 160, PAD_TOP + 48);
    windowTexture.draw(text);

    sprintf(tim, "Remaining fuel: %d / 10000", fuel);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 160, PAD_TOP + 64);
    windowTexture.draw(text);

    sprintf(tim, "Rockets: %d / 50", rockets);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 160, PAD_TOP + 80);
    windowTexture.draw(text);

    sprintf(tim, "Rounds: %d / 50000", rounds);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 160, PAD_TOP + 96);
    windowTexture.draw(text);

    sprintf(tim, "Credits: %d", credits);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 160, PAD_TOP + 112);
    windowTexture.draw(text);

    windowTexture.display();
}

void draw_menu(int type){
    char tim[80];
    sf::RectangleShape r(sf::Vector2f(16, 16));
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);

    cleardisplay(false);

    r.setPosition(S_WIDTH - PAD_RIGHT - 32, PAD_TOP + 16);
    r.setTexture(&station);
    windowTexture.draw(r);

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(PAD_LEFT, PAD_TOP)),
        sf::Vertex(sf::Vector2f(S_WIDTH - PAD_RIGHT, PAD_TOP)),
        sf::Vertex(sf::Vector2f(S_WIDTH - PAD_RIGHT, S_HEIGHT - PAD_BOTTOM)),
        sf::Vertex(sf::Vector2f(PAD_LEFT, S_HEIGHT - PAD_BOTTOM))
    };
    windowTexture.draw(line, 4, sf::Lines);

    char dat[16];
    for (int i = 0; i < 16; i++){
        dat[i] = level_0_0_tile_data[selected_object % 10].data[i];
    }
    sprintf(tim, "Viewing: %s", dat);
    text.setString(tim);
    text.setPosition(PAD_LEFT, PAD_TOP);
    windowTexture.draw(text);

    for(int i = 0; i < level_0_0_tile_data[selected_object % 10].num_level_data; i++){
        char dat[16];
        for (int j = 0; j < 16; j++){
            dat[j] = level_0_0_tile_data[selected_object % 10].flight_data[i].data[j];
        }
        sprintf(tim, "  %s", dat);
        text.setString(tim);
        text.setPosition(PAD_LEFT, PAD_TOP + 16 * (i + 1));
        windowTexture.draw(text);
    }

    text.setString("Your ship: ");
    text.setPosition(PAD_LEFT + 400, PAD_TOP);
    windowTexture.draw(text);

    sprintf(tim, "Health: %d / 500", health);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 400, PAD_TOP + 32);
    windowTexture.draw(text);

    sprintf(tim, "Experience: %d / 5000", experience);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 400, PAD_TOP + 48);
    windowTexture.draw(text);

    sprintf(tim, "Remaining fuel: %d / 10000", fuel);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 400, PAD_TOP + 64);
    windowTexture.draw(text);

    sprintf(tim, "Rockets: %d / 50", rockets);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 400, PAD_TOP + 80);
    windowTexture.draw(text);

    sprintf(tim, "Rounds: %d / 50000", rounds);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 400, PAD_TOP + 96);
    windowTexture.draw(text);

    sprintf(tim, "Credits: %d", credits);
    text.setString(tim);
    text.setPosition(PAD_LEFT + 400, PAD_TOP + 112);
    windowTexture.draw(text);

    windowTexture.display();
}

void display(bool update, int state){
    sf::Text text;
    sf::Font font;
    char tim[80];
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);

    // clear display
    cleardisplay(false);

    // rectangle template
    sf::RectangleShape r(sf::Vector2f(16, 16));

    // draw character
    r.setPosition(ship_x * 16, ship_y * 16);
    switch(facing % 4){
        case 0: r.setTexture(&character_t); break;
        case 1: r.setTexture(&character_r); break;
        case 2: r.setTexture(&character_b); break;
        case 3: r.setTexture(&character_l); break;
        default: r.setTexture(&character_t);
    }
    windowTexture.draw(r);

    switch(facing % 4){
        case 0:
            r.setTexture(&exhaust_top);
            r.setPosition(ship_x * 16, (ship_y + 1) * 16);
            break;
        case 1:
            r.setTexture(&exhaust_right);
            r.setPosition((ship_x - 1) * 16, (ship_y) * 16);
            break;
        case 2:
            r.setTexture(&exhaust_bottom);
            r.setPosition(ship_x * 16, (ship_y - 1) * 16);
            break;
        case 3:
            r.setTexture(&exhaust_left);
            r.setPosition((ship_x + 1) * 16, ship_y * 16);
            break;
    }
    windowTexture.draw(r);

    // draw entities
    for (int i = 0; i < num_entities; i++){
        if (entities[i].type >= 0){
            switch(entities[i].type){
                case 0:
                    r.setTexture(&station);
                    break;
                case 1:
                    r.setTexture(&asteriod_1);
                    break;
                case 2:
                    r.setTexture(&enemy_t);
                    break;
                case 3:
                    r.setTexture(&debris);
                    break;
                case 5:
                    r.setTexture(&rockets_tex);
                    break;
                default:
                    r.setTexture(&debug);
            }
        } else {
            r.setTexture(&wall);
        }
        r.setPosition(entities[i].x * 16, entities[i].y * 16);
        windowTexture.draw(r);
    }

    text.setString("HEALTH: ");
    text.setPosition(816, 16);
    windowTexture.draw(text);
    r.setTexture(&heart);
    if (health >= 250){
        r.setPosition(960,16);
        windowTexture.draw(r);
    } else {
        r.setTexture(&critical);
        r.setPosition(960,16);
        windowTexture.draw(r);
    }
    if (health >= 500){
        r.setPosition(944,16);
        windowTexture.draw(r);
    }
    if (health >= 750){
        r.setPosition(928,16);
        windowTexture.draw(r);
    }
    r.setTexture(&full_health);
    if (health >= 900){
        r.setPosition(912,16);
        windowTexture.draw(r);
    }

    text.setString("RANK: ");
    text.setPosition(816, 32);
    windowTexture.draw(text);
    r.setTexture(&bronze);
    r.setPosition(912,32);
    windowTexture.draw(r);

    sprintf(tim, "FUEL: %d / 10K", fuel);
    text.setString(tim);
    text.setPosition(816, 48);
    windowTexture.draw(text);

    sprintf(tim, "SECT: %d", sector_s);
    text.setString(tim);
    text.setPosition(816,80);
    windowTexture.draw(text);

    sprintf(tim, "COORD: (%d, %d)", sector_x, sector_y);
    text.setString(tim);
    text.setPosition(816,96);
    windowTexture.draw(text);

    // make it good fam
    windowTexture.display();
}

void draw_logo(){
    sf::RectangleShape r(sf::Vector2f(S_WIDTH, S_HEIGHT));
    r.setTexture(&logo);
    windowTexture.draw(r);
    windowTexture.display();
}

void draw_dock(){
    sf::RectangleShape r(sf::Vector2f(16, 16));
    sf::Text text;
    sf::Font font;
    char tim[80];
    if (!font.loadFromFile("res/telegrama_raw.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);

    cleardisplay(false);
}
