#include "main.h"
#include "quest.h"
#include <stdio.h>
#include <string.h>
//using namespace std;

// texture names
#define DEBUG_TEX 9
#define BLACK_TEX 3
#define HEART_TEX 24
#define CRITICAL_TEX 28
#define FULL_HEALTH_TEX 27
#define BRONZE_TEX 25
#define FLOOR_TEX 23
#define WALL_TEX 42
#define FERN_TEX 19
#define SYSTEM_TEX 41
#define NPC_TEX 34
#define GREEN_TEX 26
#define LOGO_TEX 32

// texture definitions
/*sfTexture* character_t;
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
sfTexture* textures[DEBUG_TEX];
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
sfTexture* textures[HEART_TEX];
sfTexture* textures[CRITICAL_TEX];
sfTexture* textures[FULL_HEALTH_TEX];
sfTexture* textures[BRONZE_TEX];
sfTexture* silver;
sfTexture* gold;
sfTexture* purple_textures[HEART_TEX];
sfTexture* exhaust_top;
sfTexture* exhaust_bottom;
sfTexture* exhaust_left;
sfTexture* exhaust_right;
sfTexture* floor_tex;
sfTexture* fern;
sfTexture* npc_tex;
sfTexture* textures[BLACK_TEX];*/

sfTexture* textures[NUM_TEXTURES];

int g_state = 0;

void rsetTexture(sfRectangleShape* r, sfTexture* texture){
    sfRectangleShape_setTexture(r, texture, sfTrue);
}

void rsetPosition(sfRectangleShape* r, int x, int y){
    sfRectangleShape_setPosition(r, (sfVector2f) {x, y});
}

int init_displays(void){
    for (int i = 0; i < NUM_TEXTURES; i++){
        char tmp[32];
        sprintf(tmp, "res/%d.png", i);
        printf("[%d]", tmp);
        textures[i] = sfTexture_createFromFile(tmp, NULL);
    }

    /*character_t = sfTexture_createFromFile("res/character-top.png", NULL);
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
    textures[DEBUG_TEX] = sfTexture_createFromFile("res/textures[DEBUG_TEX].png", NULL);
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
    textures[HEART_TEX] = sfTexture_createFromFile("res/textures[FULL_HEALTH_TEX].png", NULL);
    textures[CRITICAL_TEX] = sfTexture_createFromFile("res/textures[HEART_TEX]_low.png", NULL);
    textures[FULL_HEALTH_TEX] = sfTexture_createFromFile("res/textures[HEART_TEX].png", NULL);
    purple_textures[HEART_TEX] = sfTexture_createFromFile("res/purple.png", NULL);
    gold = sfTexture_createFromFile("res/textures[BRONZE_TEX].png", NULL);
    silver = sfTexture_createFromFile("res/silver.png", NULL);
    textures[BRONZE_TEX] = sfTexture_createFromFile("res/gold.png", NULL);
    exhaust_bottom = sfTexture_createFromFile("res/exhaust_bot.png", NULL);
    exhaust_left = sfTexture_createFromFile("res/exhaust_lef.png", NULL);
    exhaust_right = sfTexture_createFromFile("res/exhaust_rig.png", NULL);
    exhaust_top = sfTexture_createFromFile("res/exhaust_top.png", NULL);
    floor_tex = sfTexture_createFromFile("res/floor.png", NULL);
    fern = sfTexture_createFromFile("res/fern.png", NULL);
    npc_tex = sfTexture_createFromFile("res/npc_generic.png", NULL);
    textures[BLACK_TEX] = sfTexture_createFromFile("res/textures[BLACK_TEX].png", NULL); */

    return 0;
}

void cleardisplay(bool _textures[DEBUG_TEX]){
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    //sf::RectangleShape r(sf::Vector2f(16, 16));
    if (_textures[DEBUG_TEX]){
        //rsetTexture(r,  textures[DEBUG_TEX]);
        sfRectangleShape_setTexture(r, textures[DEBUG_TEX], sfTrue);
    } else {
        //rsetTexture(r,  textures[BLACK_TEX]);
        sfRectangleShape_setTexture(r, textures[BLACK_TEX], sfTrue);
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
    rsetTexture(r,  textures[HEART_TEX]);
    if (health >= 250){
        rsetPosition( r, 960,16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    } else {
        rsetTexture(r,  textures[CRITICAL_TEX]);
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
    rsetTexture(r,  textures[FULL_HEALTH_TEX]);
    if (health >= 900){
        rsetPosition( r, 912,16);
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    }

    sfText_setString(text, "RANK: ");
    sfText_setPosition(text, (sfVector2f) {816, 32});
    sfRenderWindow_drawText(window, text, NULL);
    rsetTexture(r,  textures[BRONZE_TEX]);
    rsetPosition( r, 912,32);
    sfRenderWindow_drawRectangleShape(window, r, NULL);

    sprintf(tim, "FUEL: %d / 10K", fuel);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {816, 48});
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
            case 1:
                sprintf(tim, "Ration : %s", inventory[i].data);
                sfText_setString(text, tim);
                break;
            case 2:
                sprintf(tim, "Handgun : %s", inventory[i].data);
                sfText_setString(text, tim);
                break;
            case 3:
                sprintf(tim, "Wrench : %s", inventory[i].data);
                sfText_setString(text, tim);
                break;
            case 4:
                sprintf(tim, "Ammunition : %s", inventory[i].data);
                sfText_setString(text, tim);
                break;
            case 5:
                sprintf(tim, "Grenade : %s", inventory[i].data);
                sfText_setString(text, tim);
                break;
            case 6:
                sprintf(tim, "Book : %s", inventory[i].data);
                sfText_setString(text, tim);
                break;
            case 7:
                sprintf(tim, "Machine Gun : %s", inventory[i].data);
                sfText_setString(text, tim);
                break;
            case 8:
                sprintf(tim, "Rocket Launcher : %s", inventory[i].data);
                sfText_setString(text, tim);
                break;
            case 9:
                sprintf(tim, "Pick : %s", inventory[i].data);
                sfText_setString(text, tim);
                break;
            case 10:
                sprintf(tim, "Medkit : %s", inventory[i].data);
                sfText_setString(text, tim);
                break;
            default:
                sfText_setString(text, "Invalid Item!");
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

void draw_rogue(){
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);

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
                        rsetTexture(r,  textures[BLACK_TEX]);
                        break;
                    case 0:
                        rsetTexture(r,  textures[FLOOR_TEX]);
                        break;
                    case 1:
                        rsetTexture(r,  textures[WALL_TEX]);
                        break;
                    case 5:
                        rsetTexture(r,  textures[FERN_TEX]);
                        break;
                    default:
                        rsetTexture(r,  textures[FLOOR_TEX]);
                }
            } else {
                rsetTexture(r,  textures[NPC_TEX]);
            }
            sfRenderWindow_drawRectangleShape(window, r, NULL);
        }
    }

    draw_stats();
    draw_inventory();

    rsetPosition( r, 15 * 16, 15 * 16);
    rsetTexture(r,  textures[GREEN_TEX]);
    sfRenderWindow_drawRectangleShape(window, r, NULL);
}

void draw_logo(){
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {S_WIDTH, S_HEIGHT});
    rsetTexture(r,  textures[LOGO_TEX]);
    sfRenderWindow_drawRectangleShape(window, r, NULL);
}
