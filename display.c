#include "main.h"
#include "levels.h"
#include "quest.h"
#include <stdio.h>
//using namespace std;

// texture definitions
sfTexture* character_t;
sfTexture* character_l;
sfTexture* character_b;
sfTexture* character_r;
sfTexture* enemy_t;
sfTexture* enemy_l;
sfTexture* enemy_b;
sfTexture* enemy_r;
sfTexture* asteriod_1;
sfTexture* asteriod_2;
sfTexture* asteriod_3;
sfTexture* debug;
sfTexture* wall;
sfTexture* rockets_tex;
sfTexture* station;
sfTexture* ice_station;
sfTexture* logo;
sfTexture* empty_sector;
sfTexture* ice_field;
sfTexture* nebula;
sfTexture* system_texture;
sfTexture* debris;
sfTexture* green;
sfTexture* red;
sfTexture* yellow;
sfTexture* star;
sfTexture* heart;
sfTexture* critical;
sfTexture* full_health;
sfTexture* bronze;
sfTexture* silver;
sfTexture* gold;
sfTexture* purple_heart;
sfTexture* exhaust_top;
sfTexture* exhaust_bottom;
sfTexture* exhaust_left;
sfTexture* exhaust_right;
sfTexture* floor_tex;
sfTexture* fern;
sfTexture* npc_tex;
sfTexture* black;

int g_state = 0;

void rsetTexture(sfRectangleShape* r, sfTexture* texture){
    sfRectangleShape_setTexture(r, texture, sfTrue);
}

void rsetPosition(sfRectangleShape* r, int x, int y){
    sfRectangleShape_setPosition(r, (sfVector2f) {x, y});
}

int init_displays(void){
	for (int i = 0; i < S_HEIGHT * S_WIDTH; i++){
		screen[i] = 32;
	}

	for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            mapdata[i][j] = 0;
        }
	}

    character_t = sfTexture_createFromFile("res/character-top.png", NULL);
    character_b = sfTexture_createFromFile("res/character-bottom.png", NULL);
    character_r = sfTexture_createFromFile("res/character-right.png", NULL);
    character_l = sfTexture_createFromFile("res/character-left.png", NULL);
    enemy_t = sfTexture_createFromFile("res/enemy-top.png", NULL);
    enemy_r = sfTexture_createFromFile("res/enemy-right.png", NULL);
    enemy_b = sfTexture_createFromFile("res/enemy-bottom.png", NULL);
    enemy_l = sfTexture_createFromFile("res/enemy-left.png", NULL);
    asteriod_1 = sfTexture_createFromFile("res/asteriod-1.png", NULL);
    asteriod_2 = sfTexture_createFromFile("res/asteriod-2.png", NULL);
    asteriod_3 = sfTexture_createFromFile("res/asteriod-3.png", NULL);
    debug = sfTexture_createFromFile("res/debug.png", NULL);
    wall = sfTexture_createFromFile("res/wall.png", NULL);
    rockets_tex = sfTexture_createFromFile("res/rockets-2.png", NULL);
    station = sfTexture_createFromFile("res/station.png", NULL);
    ice_station = sfTexture_createFromFile("res/ice-station.png", NULL);
    logo = sfTexture_createFromFile("res/logo.png", NULL);
    empty_sector = sfTexture_createFromFile("res/empty_sector.png", NULL);
    nebula = sfTexture_createFromFile("res/ice-field.png", NULL);
    ice_field = sfTexture_createFromFile("res/nebula.png", NULL);
    system_texture = sfTexture_createFromFile("res/system.png", NULL);
    debris = sfTexture_createFromFile("res/flak-2.png", NULL);
    red = sfTexture_createFromFile("res/red.png", NULL);
    yellow = sfTexture_createFromFile("res/yellow.png", NULL);
    green = sfTexture_createFromFile("res/green.png", NULL);
    star = sfTexture_createFromFile("res/yellow.png", NULL);
    heart = sfTexture_createFromFile("res/full_health.png", NULL);
    critical = sfTexture_createFromFile("res/heart_low.png", NULL);
    full_health = sfTexture_createFromFile("res/heart.png", NULL);
    purple_heart = sfTexture_createFromFile("res/purple.png", NULL);
    gold = sfTexture_createFromFile("res/bronze.png", NULL);
    silver = sfTexture_createFromFile("res/silver.png", NULL);
    bronze = sfTexture_createFromFile("res/gold.png", NULL);
    exhaust_bottom = sfTexture_createFromFile("res/exhaust_bot.png", NULL);
    exhaust_left = sfTexture_createFromFile("res/exhaust_lef.png", NULL);
    exhaust_right = sfTexture_createFromFile("res/exhaust_rig.png", NULL);
    exhaust_top = sfTexture_createFromFile("res/exhaust_top.png", NULL);
    floor_tex = sfTexture_createFromFile("res/floor.png", NULL);
    fern = sfTexture_createFromFile("res/fern.png", NULL);
    npc_tex = sfTexture_createFromFile("res/npc_generic.png", NULL);
    black = sfTexture_createFromFile("res/black.png", NULL);

    return 0;
}

void cleardisplay(bool _debug){
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    //sf::RectangleShape r(sf::Vector2f(16, 16));
    if (_debug){
        //rsetTexture(r,  debug);
        sfRectangleShape_setTexture(r, debug, sfTrue);
    } else {
        //rsetTexture(r,  black);
        sfRectangleShape_setTexture(r, black, sfTrue);
    }
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j <  HEIGHT; j++){
            //rsetPosition( r, i * 16, j * 16);
            sfRectangleShape_setPosition(r, (sfVector2f) {i * 16, j * 16});
            //sfRenderWindow_drawRectangleShape(window, r, NULL);
            sfRenderWindow_drawRectangleShape(window, r, NULL);
        }
    }
}

void draw_stats(){
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);
    //sfText_setColor(text, sfWhite);
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    char tim[80];

    sfText_setString(text, "HEALTH: ");
    sfText_setPosition(text, (sfVector2f) {816, 16});
    //sfRenderWindow_drawText(window, text, NULL);
    sfRenderWindow_drawText(window, text, NULL);
    rsetTexture(r,  heart);
    if (health >= 250){
        rsetPosition( r, 960,16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    } else {
        rsetTexture(r,  critical);
        rsetPosition( r, 960,16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    }
    if (health >= 500){
        rsetPosition( r, 944,16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    }
    if (health >= 750){
        rsetPosition( r, 928,16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    }
    rsetTexture(r,  full_health);
    if (health >= 900){
        rsetPosition( r, 912,16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    }

    sfText_setString(text, "RANK: ");
    sfText_setPosition(text, (sfVector2f) {816, 32});
    sfRenderWindow_drawText(window, text, NULL);
    rsetTexture(r,  bronze);
    rsetPosition( r, 912,32);
    sfRenderWindow_drawRectangleShape(window, r, NULL);

    sprintf(tim, "FUEL: %d / 10K", fuel);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {816, 48});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "SECT: %d", sector_s);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {816,80});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "COORD: (%d, %d)", sector_x, sector_y);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {816,96});
    sfRenderWindow_drawText(window, text, NULL);
}

void draw_inventory(){
    // graphics setup
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);
    //sfText_setColor(text, sfWhite);
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    char tim[80];

    sfText_setString(text, "INVENTORY: ");
    sfText_setPosition(text, (sfVector2f) {576, 16});
    sfRenderWindow_drawText(window, text, NULL);

    // loop inventory
    int i;
    for(i = 0; i < num_items; i++){
        switch(inventory[i].type){
            case 2:
                sprintf(tim, "HANDGUN [%s]", inventory[i].data);
                sfText_setString(text, tim);
                break;
            case 1:
                sprintf(tim, "RATION  [%s]", inventory[i].data);
                sfText_setString(text, tim);
                break;
            default:
                sfText_setString(text, "UNKNOWN [???      ]");
        }
        sfText_setPosition(text, (sfVector2f) {592, (i + 2) * 16});
        sfRenderWindow_drawText(window, text, NULL);
    }
    i++;

    sfText_setString(text, "QUESTS: ");
    sfText_setPosition(text, (sfVector2f) {576, (i + 2) * 16});
    sfRenderWindow_drawText(window, text, NULL);

    i++;
    if (num_active_quests == 0){
        sfText_setString(text, "-[No Active Quests]");
        sfText_setPosition(text, (sfVector2f) {576, (i + 2) * 16});
        sfRenderWindow_drawText(window, text, NULL);
    } else {
        for (int j = 0; j < num_active_quests; j++){
            char tmp[80];
            sprintf(tmp, "%s [%d]", quest_registry[npc_last.quest_id].title, quest_registry[npc_last.quest_id].id);
            sfText_setString(text, tmp);
            sfText_setPosition(text, (sfVector2f) {576, (++i + 2) * 16});
            sfRenderWindow_drawText(window, text, NULL);
        }
    }
}

void draw_rouge(){
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);
    //sfText_setColor(text, sfWhite);
//    char tim[80];
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < HEIGHT; j++){
            rsetPosition( r, (i) * 16, (j) * 16);
            if (rogue_npc_master[master_index](i - 15 + character_x, j - 15 + character_y).id <= 0) {
                int tdat = -1;
                if (((i - 15 + character_x) >= 0 && (i - 15 + character_x ) < cached_map.w) &&
                    ((j - 15 + character_y) >= 0 && (j - 15 + character_y ) < cached_map.h)) {
                    tdat = cached_map.tile_type[(i - 15 + character_x)  + (j - 15 + character_y) * cached_map.w];
                }

                switch (tdat){
                    case -1:
                        rsetTexture(r,  black);
                        break;
                    case 0:
                        rsetTexture(r,  floor_tex);
                        break;
                    case 1:
                        rsetTexture(r,  wall);
                        break;
                    case 5:
                        rsetTexture(r,  fern);
                        break;
                    default:
                        rsetTexture(r,  system_texture);
                }
            } else {
                rsetTexture(r,  npc_tex);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
        }
    }

    draw_stats();
    draw_inventory();

    rsetPosition( r, 15 * 16, 15 * 16);
    rsetTexture(r,  green);
    sfRenderWindow_drawRectangleShape(window, r, NULL);

    // make it good fam
    //windowTexture.display(); // dont need this anymore
}

void draw_engine_config(){
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);
    //sfText_setColor(text, sfWhite);
//    char tim[80];

    sfText_setString(text, "Engine Configuration Window");
    sfText_setPosition(text, (sfVector2f) {32, 32});
    sfRenderWindow_drawText(window, text, NULL);

    //sfText_setColor( text, sfGreen);
    sfText_setString(text, "E1");
    sfText_setPosition(text, (sfVector2f) {32, 368});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "E2");
    sfText_setPosition(text, (sfVector2f) {112, 368});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "E3");
    sfText_setPosition(text, (sfVector2f) {192, 368});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "E4");
    sfText_setPosition(text, (sfVector2f) {272, 368});
    sfRenderWindow_drawText(window, text, NULL);
    //sfText_setColor( text, sfWhite);
    for(int i = 0; i < 2; i++){
        for (int j = 0; j < 10; j++){
            rsetPosition( r, 32 + 16 * i, 400 + j * 16);
            if ( j >= e1_y) {
                rsetTexture(r,  red);
            } else if (j >= e1_g && j < e1_y){
                rsetTexture(r,  yellow);
            } else {
                rsetTexture(r,  green);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
            rsetPosition( r, 112 + 16 * i, 400 + j * 16);
            if ( j >= e2_y) {
                rsetTexture(r,  red);
            } else if (j >= e2_g && j < e2_y){
                rsetTexture(r,  yellow);
            } else {
                rsetTexture(r,  green);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
            rsetPosition( r, 192 + 16 * i, 400 + j * 16);
            if ( j >= e3_y) {
                rsetTexture(r,  red);
            } else if (j >= e3_g && j < e3_y){
                rsetTexture(r,  yellow);
            } else {
                rsetTexture(r,  green);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
            rsetPosition( r, 272 + 16 * i, 400 + j * 16);
            if ( j >= e4_y) {
                rsetTexture(r,  red);
            } else if (j >= e4_g && j < e4_y){
                rsetTexture(r,  yellow);
            } else {
                rsetTexture(r,  green);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
        }
    }

    sfText_setString(text, "Flux:Fuel Ratio     [A][Q]");
    sfText_setPosition(text, (sfVector2f) {32, 62});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Dur.:Res. Ratio     [S][W]");
    sfText_setPosition(text, (sfVector2f) {32, 110});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Flux Clamp          [D][E]");
    sfText_setPosition(text, (sfVector2f) {32, 158});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Emission Clamp      [F][R]");
    sfText_setPosition(text, (sfVector2f) {32, 206});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Thermal Clamp       [G][T]");
    sfText_setPosition(text, (sfVector2f) {32, 254});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Engine Status:");
    sfText_setPosition(text, (sfVector2f) {32, 350});
    sfRenderWindow_drawText(window, text, NULL);
    for (int i = 2; i < 20; i++){
        if(i - 1 < fuel_r / 55){
            rsetTexture(r,  green);
        } else {
            rsetTexture(r,  red);
        }
        rsetPosition( r, i * 16, 80);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
        if(i - 1 < durability / 55){
            rsetTexture(r,  green);
        } else {
            rsetTexture(r,  red);
        }
        rsetPosition( r, i * 16, 128);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
        if(i - 1 < flux_clamp / 55){
            rsetTexture(r,  green);
        } else {
            rsetTexture(r,  red);
        }
        rsetPosition( r, i * 16, 176);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
        if(i - 1 < emission_clamp / 55){
            rsetTexture(r,  green);
        } else {
            rsetTexture(r,  red);
        }
        rsetPosition( r, i * 16, 224);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
        if(i - 1 < themal_clamp / 55){
            rsetTexture(r,  green);
        } else {
            rsetTexture(r,  red);
        }
        rsetPosition( r, i * 16, 272);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    }

    // dont need anymore
    //windowTexture.display();
}

void draw_prewarp(int x, int y, int s){
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);
    //sfText_setColor(text, sfWhite);
    char tim[80];

    // pick default texture
    rsetTexture(r,  empty_sector);
    for (int i = 1; i < 11; i++){
        for (int j = 1; j < 11; j++){
            // draw sector 1
            switch(level_0_0[i - 1][j - 1]){
                case 0: rsetTexture(r,  empty_sector); break;
                case 1: rsetTexture(r,  station); break;
                case 2: rsetTexture(r,  ice_field); break;
                case 3: rsetTexture(r,  nebula); break;
                case 4: rsetTexture(r,  system_texture); break;
            }
            rsetPosition( r, (i * 16) , j * 16);
            sfRenderWindow_drawRectangleShape(window, r, NULL);

            // draw sector 1
            switch(level_0_1[i - 1][j - 1]){
                case 0: rsetTexture(r,  empty_sector); break;
                case 1: rsetTexture(r,  station); break;
                case 2: rsetTexture(r,  ice_field); break;
                case 3: rsetTexture(r,  nebula); break;
                case 4: rsetTexture(r,  system_texture); break;
            }
            rsetPosition( r, (i + 11) * 16 , j * 16);
            sfRenderWindow_drawRectangleShape(window, r, NULL);

            // draw sector 3
            switch(level_0_3[i - 1][j - 1]){
                case 0: rsetTexture(r,  empty_sector); break;
                case 1: rsetTexture(r,  station); break;
                case 2: rsetTexture(r,  ice_field); break;
                case 3: rsetTexture(r,  nebula); break;
                case 4: rsetTexture(r,  system_texture); break;
            }
            rsetPosition( r, i * 16 , (j + 11) * 16);
            sfRenderWindow_drawRectangleShape(window, r, NULL);

            // draw sector 2
            switch(level_0_2[i - 1][j - 1]){
                case 0: rsetTexture(r,  empty_sector); break;
                case 1: rsetTexture(r,  station); break;
                case 2: rsetTexture(r,  ice_field); break;
                case 3: rsetTexture(r,  nebula); break;
                case 4: rsetTexture(r,  system_texture); break;
            }
            rsetPosition( r, (i + 11) * 16 , (j + 11) * 16);
            sfRenderWindow_drawRectangleShape(window, r, NULL);
        }
    }

    // draw jump position
    if (s == 0) {
        rsetPosition( r, (x + 1) * 16, (y + 1) * 16);
    } else if (s == 1){
        rsetPosition( r, (x + 1) * 16 + 176, (y + 1) * 16);
    } else if (s == 2){
        rsetPosition( r, (x + 1) * 16 + 176, (y + 1) * 16 + 176);
    } else if (s == 3){
        rsetPosition( r, (x + 1) * 16, (y + 1) * 16 + 176);
    }
    rsetTexture(r,  character_t);
    sfRenderWindow_drawRectangleShape(window, r, NULL);

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
    sfText_setString(text, temp_data);
    sfText_setPosition(text, (sfVector2f) {368, 112});
    sfRenderWindow_drawText(window, text, NULL);


    // draw cuttent position
    if (sector_s == 0) {
        rsetPosition( r, (sector_x + 1) * 16, (sector_y+ 1) * 16);
    } else if (sector_s == 1){
        rsetPosition( r, (sector_x + 1) * 16 + 176, (sector_y + 1) * 16);
    } else if (sector_s == 2){
        rsetPosition( r, (sector_x + 1) * 16 + 176, (sector_y + 1) * 16 + 176);
    } else if (sector_s == 3){
        rsetPosition( r, (sector_x + 1) * 16, (sector_y + 1) * 16 + 176);
    }
    rsetTexture(r,  enemy_t);
    sfRenderWindow_drawRectangleShape(window, r, NULL);

    // draw text
    sfText_setString(text, "Warp Config System v12.81.20392");
    sfText_setPosition(text, (sfVector2f) {368, 16});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Quadrant: Epsilon");
    sfText_setPosition(text, (sfVector2f) {368, 48});
    sfRenderWindow_drawText(window, text, NULL);
    sprintf(tim, "Jump Sector: %d - %d - %d    Current Sector: %d - %d - %d", s, x, y, sector_s, sector_x, sector_y);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {368, 64});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Warp Engine Integrity: 87%");
    sfText_setPosition(text, (sfVector2f) {368, 80});
    sfRenderWindow_drawText(window, text, NULL);

    sfText_setString(text, "Engine Status:");
    sfText_setPosition(text, (sfVector2f) {368, 368});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "[Enter] to configure");
    sfText_setPosition(text, (sfVector2f) {368, 384});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Fuel: 9678 / 10000");
    sfText_setPosition(text, (sfVector2f) {368, 416});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Peak Flux: 0.6772 A--DE-G-");
    sfText_setPosition(text, (sfVector2f) {368, 432});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Reserved Flux: 10.2821");
    sfText_setPosition(text, (sfVector2f) {368, 448});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Time Per Cycle: 1h 17m 57s");
    sfText_setPosition(text, (sfVector2f) {368, 480});
    sfRenderWindow_drawText(window, text, NULL);

    //sfText_setColor( text, sfGreen);
    sfText_setString(text, "E1");
    sfText_setPosition(text, (sfVector2f) {32, 368});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "E2");
    sfText_setPosition(text, (sfVector2f) {112, 368});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "E3");
    sfText_setPosition(text, (sfVector2f) {192, 368});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "E4");
    sfText_setPosition(text, (sfVector2f) {272, 368});
    sfRenderWindow_drawText(window, text, NULL);
    //sfText_setColor( text, sfWhite);
    for(int i = 0; i < 2; i++){
        for (int j = 0; j < 10; j++){
            rsetPosition( r, 32 + 16 * i, 400 + j * 16);
            if ( j >= e1_y) {
                rsetTexture(r,  red);
            } else if (j >= e1_g && j < e1_y){
                rsetTexture(r,  yellow);
            } else {
                rsetTexture(r,  green);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
            rsetPosition( r, 112 + 16 * i, 400 + j * 16);
            if ( j >= e2_y) {
                rsetTexture(r,  red);
            } else if (j >= e2_g && j < e2_y){
                rsetTexture(r,  yellow);
            } else {
                rsetTexture(r,  green);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
            rsetPosition( r, 192 + 16 * i, 400 + j * 16);
            if ( j >= e3_y) {
                rsetTexture(r,  red);
            } else if (j >= e3_g && j < e3_y){
                rsetTexture(r,  yellow);
            } else {
                rsetTexture(r,  green);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
            rsetPosition( r, 272 + 16 * i, 400 + j * 16);
            if ( j >= e4_y) {
                rsetTexture(r,  red);
            } else if (j >= e4_g && j < e4_y){
                rsetTexture(r,  yellow);
            } else {
                rsetTexture(r,  green);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
        }
    }

    // make it good fam
    // dont need
    //windowTexture.display();
}

void draw_warp(int x, int y, int s){
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    char tim[80];
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);
    //sfText_setColor(text, sfWhite);

    // pick default texture
    rsetTexture(r,  empty_sector);
    for (int i = 1; i < 11; i++){
        for (int j = 1; j < 11; j++){
            // draw sector 1
            switch(level_0_0[i - 1][j - 1]){
                case 0: rsetTexture(r,  empty_sector); break;
                case 1: rsetTexture(r,  station); break;
                case 2: rsetTexture(r,  ice_field); break;
                case 3: rsetTexture(r,  nebula); break;
                case 4: rsetTexture(r,  system_texture); break;
            }
            rsetPosition( r, (i * 16) , j * 16);
            sfRenderWindow_drawRectangleShape(window, r, NULL);

            // draw sector 1
            switch(level_0_1[i - 1][j - 1]){
                case 0: rsetTexture(r,  empty_sector); break;
                case 1: rsetTexture(r,  station); break;
                case 2: rsetTexture(r,  ice_field); break;
                case 3: rsetTexture(r,  nebula); break;
                case 4: rsetTexture(r,  system_texture); break;
            }
            rsetPosition( r, (i + 11) * 16 , j * 16);
            sfRenderWindow_drawRectangleShape(window, r, NULL);

            // draw sector 3
            switch(level_0_3[i - 1][j - 1]){
                case 0: rsetTexture(r,  empty_sector); break;
                case 1: rsetTexture(r,  station); break;
                case 2: rsetTexture(r,  ice_field); break;
                case 3: rsetTexture(r,  nebula); break;
                case 4: rsetTexture(r,  system_texture); break;
            }
            rsetPosition( r, i * 16 , (j + 11) * 16);
            sfRenderWindow_drawRectangleShape(window, r, NULL);

            // draw sector 2
            switch(level_0_2[i - 1][j - 1]){
                case 0: rsetTexture(r,  empty_sector); break;
                case 1: rsetTexture(r,  station); break;
                case 2: rsetTexture(r,  ice_field); break;
                case 3: rsetTexture(r,  nebula); break;
                case 4: rsetTexture(r,  system_texture); break;
            }
            rsetPosition( r, (i + 11) * 16 , (j + 11) * 16);
            sfRenderWindow_drawRectangleShape(window, r, NULL);
        }
    }

    // draw jump position
    if (s == 0) {
        rsetPosition( r, (x + 1) * 16, (y + 1) * 16);
    } else if (s == 1){
        rsetPosition( r, (x + 1) * 16 + 176, (y + 1) * 16);
    } else if (s == 2){
        rsetPosition( r, (x + 1) * 16 + 176, (y + 1) * 16 + 176);
    } else if (s == 3){
        rsetPosition( r, (x + 1) * 16, (y + 1) * 16 + 176);
    }
    rsetTexture(r,  character_t);
    sfRenderWindow_drawRectangleShape(window, r, NULL);

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
    sfText_setString(text, temp_data);
    sfText_setPosition(text, (sfVector2f) {368, 112});
    sfRenderWindow_drawText(window, text, NULL);


    // draw cuttent position
    if (sector_s == 0) {
        rsetPosition( r, (sector_x + 1) * 16, (sector_y+ 1) * 16);
    } else if (sector_s == 1){
        rsetPosition( r, (sector_x + 1) * 16 + 176, (sector_y + 1) * 16);
    } else if (sector_s == 2){
        rsetPosition( r, (sector_x + 1) * 16 + 176, (sector_y + 1) * 16 + 176);
    } else if (sector_s == 3){
        rsetPosition( r, (sector_x + 1) * 16, (sector_y + 1) * 16 + 176);
    }
    rsetTexture(r,  enemy_t);
    sfRenderWindow_drawRectangleShape(window, r, NULL);

    // draw text
    sfText_setString(text, "Warp Config System v12.81.20392");
    sfText_setPosition(text, (sfVector2f) {368, 16});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Quadrant: Epsilon");
    sfText_setPosition(text, (sfVector2f) {368, 48});
    sfRenderWindow_drawText(window, text, NULL);
    sprintf(tim, "Jump Sector: %d - %d - %d    Current Sector: %d - %d - %d", s, x, y, sector_s, sector_x, sector_y);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {368, 64});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Warp Engine Integrity: 87%");
    sfText_setPosition(text, (sfVector2f) {368, 80});
    sfRenderWindow_drawText(window, text, NULL);

    sfText_setString(text, "Engine Status:");
    sfText_setPosition(text, (sfVector2f) {368, 368});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "[Enter] to configure");
    sfText_setPosition(text, (sfVector2f) {368, 384});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Fuel: 9678 / 10000");
    sfText_setPosition(text, (sfVector2f) {368, 416});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Peak Flux: 0.6772 A--DE-G-");
    sfText_setPosition(text, (sfVector2f) {368, 432});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Reserved Flux: 10.2821");
    sfText_setPosition(text, (sfVector2f) {368, 448});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "Time Per Cycle: 1h 17m 57s");
    sfText_setPosition(text, (sfVector2f) {368, 480});
    sfRenderWindow_drawText(window, text, NULL);

    //sfText_setColor( text, sfGreen);
    sfText_setString(text, "E1");
    sfText_setPosition(text, (sfVector2f) {32, 368});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "E2");
    sfText_setPosition(text, (sfVector2f) {112, 368});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "E3");
    sfText_setPosition(text, (sfVector2f) {192, 368});
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setString(text, "E4");
    sfText_setPosition(text, (sfVector2f) {272, 368});
    sfRenderWindow_drawText(window, text, NULL);
    //sfText_setColor( text, sfWhite);
    for(int i = 0; i < 2; i++){
        for (int j = 0; j < 10; j++){
            rsetPosition( r, 32 + 16 * i, 400 + j * 16);
            if ( j >= e1_y) {
                rsetTexture(r,  red);
            } else if (j >= e1_g && j < e1_y){
                rsetTexture(r,  yellow);
            } else {
                rsetTexture(r,  green);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
            rsetPosition( r, 112 + 16 * i, 400 + j * 16);
            if ( j >= e2_y) {
                rsetTexture(r,  red);
            } else if (j >= e2_g && j < e2_y){
                rsetTexture(r,  yellow);
            } else {
                rsetTexture(r,  green);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
            rsetPosition( r, 192 + 16 * i, 400 + j * 16);
            if ( j >= e3_y) {
                rsetTexture(r,  red);
            } else if (j >= e3_g && j < e3_y){
                rsetTexture(r,  yellow);
            } else {
                rsetTexture(r,  green);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
            rsetPosition( r, 272 + 16 * i, 400 + j * 16);
            if ( j >= e4_y) {
                rsetTexture(r,  red);
            } else if (j >= e4_g && j < e4_y){
                rsetTexture(r,  yellow);
            } else {
                rsetTexture(r,  green);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
        }
    }

    // make it good fam
    // unnecessary
    // windowTexture.display();
}

void draw_self(){
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);
    //sfText_setColor(text, sfWhite);
    char tim[80];

    cleardisplay(false);

    /* whatever then
    sfVertex line[] =
    {
        sfVertex(sfVector2f(PAD_LEFT, PAD_TOP)),
        sfVertex(sfVector2f(S_WIDTH - PAD_RIGHT, PAD_TOP)),
        sfVertex(sfVector2f(S_WIDTH - PAD_RIGHT, S_HEIGHT - PAD_BOTTOM)),
        sfVertex(sfVector2f(PAD_LEFT, S_HEIGHT - PAD_BOTTOM))
    };
    windowTexture.draw(line, 4, sf::Lines); */

    sfText_setString(text, "Your starcruiser: ");
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT, PAD_TOP});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "Health: %d / 500", health);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 160, PAD_TOP + 32});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "Experience: %d / 5000", experience);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 160, PAD_TOP + 48});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "Remaining fuel: %d / 10000", fuel);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 160, PAD_TOP + 64});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "Rockets: %d / 50", rockets);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 160, PAD_TOP + 80});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "Rounds: %d / 50000", rounds);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 160, PAD_TOP + 96});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "Credits: %d", credits);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 160, PAD_TOP + 112});
    sfRenderWindow_drawText(window, text, NULL);

    // dont need anymore
    // windowTexture.display();
}

void draw_menu(int type){
    char tim[80];
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);
    //sfText_setColor(text, sfWhite);

    cleardisplay(false);

    rsetPosition( r, S_WIDTH - PAD_RIGHT - 32, PAD_TOP + 16);
    rsetTexture(r,  station);
    sfRenderWindow_drawRectangleShape(window, r, NULL);

    /* whatever then
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(PAD_LEFT, PAD_TOP)),
        sf::Vertex(sf::Vector2f(S_WIDTH - PAD_RIGHT, PAD_TOP)),
        sf::Vertex(sf::Vector2f(S_WIDTH - PAD_RIGHT, S_HEIGHT - PAD_BOTTOM)),
        sf::Vertex(sf::Vector2f(PAD_LEFT, S_HEIGHT - PAD_BOTTOM))
    };
    windowTexture.draw(line, 4, sf::Lines);
    */

    char dat[16];
    for (int i = 0; i < 16; i++){
        dat[i] = level_0_0_tile_data[selected_object % 10].data[i];
    }
    sprintf(tim, "Viewing: %s", dat);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT, PAD_TOP});
    sfRenderWindow_drawText(window, text, NULL);

    for(int i = 0; i < level_0_0_tile_data[selected_object % 10].num_level_data; i++){
        char dat[16];
        for (int j = 0; j < 16; j++){
            dat[j] = level_0_0_tile_data[selected_object % 10].flight_data[i].data[j];
        }
        sprintf(tim, "  %s", dat);
        sfText_setString(text, tim);
        sfText_setPosition(text, (sfVector2f) {PAD_LEFT, PAD_TOP + 16 * (i + 1)});
        sfRenderWindow_drawText(window, text, NULL);
    }

    sfText_setString(text, "Your ship: ");
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 400, PAD_TOP});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "Health: %d / 500", health);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 400, PAD_TOP + 32});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "Experience: %d / 5000", experience);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 400, PAD_TOP + 48});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "Remaining fuel: %d / 10000", fuel);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 400, PAD_TOP + 64});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "Rockets: %d / 50", rockets);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 400, PAD_TOP + 80});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "Rounds: %d / 50000", rounds);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 400, PAD_TOP + 96});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "Credits: %d", credits);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {PAD_LEFT + 400, PAD_TOP + 112});
    sfRenderWindow_drawText(window, text, NULL);

    // dont need anymore
    //windowTexture.display();
}

void display(bool update, int state){
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);
    //sfText_setColor(text, sfWhite);
    char tim[80];

    // clear display
    cleardisplay(false);

    // rectangle template
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});

    // draw character
    rsetPosition( r, ship_x * 16, ship_y * 16);
    switch(facing % 4){
        case 0: rsetTexture(r,  character_t); break;
        case 1: rsetTexture(r,  character_r); break;
        case 2: rsetTexture(r,  character_b); break;
        case 3: rsetTexture(r,  character_l); break;
        default: rsetTexture(r,  character_t);
    }
    sfRenderWindow_drawRectangleShape(window, r, NULL);

    switch(facing % 4){
        case 0:
            rsetTexture(r,  exhaust_top);
            rsetPosition( r, ship_x * 16, (ship_y + 1) * 16);
            break;
        case 1:
            rsetTexture(r,  exhaust_right);
            rsetPosition( r, (ship_x - 1) * 16, (ship_y) * 16);
            break;
        case 2:
            rsetTexture(r,  exhaust_bottom);
            rsetPosition( r, ship_x * 16, (ship_y - 1) * 16);
            break;
        case 3:
            rsetTexture(r,  exhaust_left);
            rsetPosition( r, (ship_x + 1) * 16, ship_y * 16);
            break;
    }
    sfRenderWindow_drawRectangleShape(window, r, NULL);

    // draw entities
    for (int i = 0; i < num_entities; i++){
        if (entities[i].type >= 0){
            switch(entities[i].type){
                case 0:
                    rsetTexture(r,  station);
                    break;
                case 1:
                    rsetTexture(r,  asteriod_1);
                    break;
                case 2:
                    rsetTexture(r,  enemy_t);
                    break;
                case 3:
                    rsetTexture(r,  debris);
                    break;
                case 5:
                    rsetTexture(r,  rockets_tex);
                    break;
                default:
                    rsetTexture(r,  debug);
            }
        } else {
            rsetTexture(r,  wall);
        }
        rsetPosition( r, entities[i].x * 16, entities[i].y * 16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    }

    sfText_setString(text, "HEALTH: ");
    sfText_setPosition(text, (sfVector2f) {816, 16});
    sfRenderWindow_drawText(window, text, NULL);
    rsetTexture(r,  heart);
    if (health >= 250){
        rsetPosition( r, 960,16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    } else {
        rsetTexture(r,  critical);
        rsetPosition( r, 960,16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    }
    if (health >= 500){
        rsetPosition( r, 944,16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    }
    if (health >= 750){
        rsetPosition( r, 928,16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    }
    rsetTexture(r,  full_health);
    if (health >= 900){
        rsetPosition( r, 912,16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    }

    sfText_setString(text, "RANK: ");
    sfText_setPosition(text, (sfVector2f) {816, 32});
    sfRenderWindow_drawText(window, text, NULL);
    rsetTexture(r,  bronze);
    rsetPosition( r, 912,32);
    sfRenderWindow_drawRectangleShape(window, r, NULL);

    sprintf(tim, "FUEL: %d / 10K", fuel);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {816, 48});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "SECT: %d", sector_s);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {816,80});
    sfRenderWindow_drawText(window, text, NULL);

    sprintf(tim, "COORD: (%d, %d)", sector_x, sector_y);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {816,96});
    sfRenderWindow_drawText(window, text, NULL);

    // make it good fam
    // domt need anymore
    //windowTexture.display();
}

void draw_logo(){
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {S_WIDTH, S_HEIGHT});
    rsetTexture(r,  logo);
    sfRenderWindow_drawRectangleShape(window, r, NULL);
    //windowTexture.display();
}

void draw_dock(){
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);
    //sfText_setColor(text, sfWhite);
//    char tim[80];

    cleardisplay(false);
}
