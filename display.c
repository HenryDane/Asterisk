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

// ugly hack #2
void rsetTexture(sfRectangleShape* r, sfTexture* texture){
    sfRectangleShape_setTexture(r, texture, sfTrue);
}

// ugly hack #3
void rsetPosition(sfRectangleShape* r, int x, int y){
    sfRectangleShape_setPosition(r, (sfVector2f) {x, y});
}

// ugly hack #1 (duplicate)
void textsetPosition(sfText* text, int x, int y){
    sfText_setPosition(text, (sfVector2f) {x, y});
}

int init_displays(void){
    for (int i = 0; i < NUM_TEXTURES; i++){
        char tmp[32];
        sprintf(tmp, "res/%d.png", i);
        printf("[%d]\n", tmp);
        textures[i] = sfTexture_createFromFile(tmp, NULL);
    }

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

void draw_quests(){

}

void draw_cutscene(){

}

void draw_trade( int trade_index ){
    // merchant mode;
    // printf("hello \n");
    sfText* text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 16);
    sfText_setString(text, "MERCHANT");
    textsetPosition( text, 0,0);
    sfRenderWindow_drawText(window, text, NULL);
    char tim[80];
    sprintf(tim, "CREDITS: $%d", credits);
    sfText_setString(text, tim);
    textsetPosition( text, 32 * 16,0);
    sfRenderWindow_drawText(window, text, NULL);

    int l = 0;

    for (int i = 0; i < npc_last.inventory_size; i++){
        switch(npc_last.inventory[i].type){
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
        textsetPosition( text, 32, (l + 1) * 16);
        sfRenderWindow_drawText(window, text, NULL);

        if (i == trade_index){
            sfText_setString(text,"->");
            textsetPosition(text, 0, (l + 1) * 16);
            sfRenderWindow_drawText(window, text, NULL);
        }

        sprintf(tim, "%s ($%d)", npc_last.inventory[i].data, npc_last.inventory[i].cost);
        sfText_setString(text, tim);
        textsetPosition( text, 32, (l + 2) * 16);
        sfRenderWindow_drawText(window, text, NULL);
        l += 3;
    }

    l+=2;
    sfText_setString(text, "N(Exit) Q(Go Up) E(Go Down) Enter(Purchase)");
    textsetPosition( text, 32, 544);
    sfRenderWindow_drawText(window, text, NULL);
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
    rsetTexture(r, textures[FULL_HEALTH_TEX]);
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

    sprintf(tim, "CREDITS: %d ", credits);
    sfText_setString(text, tim);
    sfText_setPosition(text, (sfVector2f) {816, 64});
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
