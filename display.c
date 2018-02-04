#include "main.h"
#include "quest.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "kernel/kernel.h"
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
#define TURRET_TEX 45
#define BULLET_TEX 46
#define FIRE_TEX 44
#define CRATE_TEX 47
#define PORTAl_TEX 48

int g_state = 0;

int init_displays(void){
    return 0;
}

void cleardisplay(bool debug){
    sfRectangleShape* r = sfRectangleShape_create(); sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    int texid = 0;
    if (debug){
        texid = DEBUG_TEX;
    } else {
        texid = BLACK_TEX;
    }
    for (int i = 0; i < WIDTH; i++){
        for (int j = 0; j <  HEIGHT; j++){
            k_put_rect(texid, i, j);
        }
    }
}

void draw_quests(){

}

void draw_cutscene(){

}

void draw_trade( int trade_index ){
    // merchant mode;
    k_put_text("MERCHANT", 0, 0);
    char tim[80];
    sprintf(tim, "CREDITS: $%d", credits);
    k_put_text(tim, 32, 0);

    int l = 0;

    for (int i = 0; i < npc_last.inventory_size; i++){
        switch(npc_last.inventory[i].type){
            case 1:
                sprintf(tim, "Ration : %s", inventory[i].data);
                break;
            case 2:
                sprintf(tim, "Handgun : %s", inventory[i].data);
                break;
            case 3:
                sprintf(tim, "Wrench : %s", inventory[i].data);
                break;
            case 4:
                sprintf(tim, "Ammunition : %s", inventory[i].data);
                break;
            case 5:
                sprintf(tim, "Grenade : %s", inventory[i].data);
                break;
            case 6:
                sprintf(tim, "Book : %s", inventory[i].data);
                break;
            case 7:
                sprintf(tim, "Machine Gun : %s", inventory[i].data);
                break;
            case 8:
                sprintf(tim, "Rocket Launcher : %s", inventory[i].data);
                break;
            case 9:
                sprintf(tim, "Pick : %s", inventory[i].data);
                break;
            case 10:
                sprintf(tim, "Medkit : %s", inventory[i].data);
                break;
            default:
                strcpy(tim, "Invalid Item!");
        }
        k_put_text(tim, 2, l + 1);

        if (i == trade_index){
            k_put_text("->", 0, l + 1);
        }

        sprintf(tim, "%s ($%d)", npc_last.inventory[i].data, npc_last.inventory[i].cost);
        k_put_text(tim, 2, l + 2);
        l += 3;
    }

    l+=2;
    k_put_text("N(Exit) Q(Go Up) E(Go Down) Enter(Purchase)", 2, 34);
}

void draw_stats(){
    char tim[80];
    int texid = 0;

    k_put_text("HEALTH: ", 36, 1);

    texid = HEART_TEX;
    if (health >= 250){
        k_put_rect(texid, 45, 1);
    } else {
        k_put_rect(CRITICAL_TEX, 60, 1);
    }
    if (health >= 500){
        k_put_rect(texid, 44, 1);
    }
    if (health >= 750){
        k_put_rect(texid, 43, 1);
    }
    texid = FULL_HEALTH_TEX;
    if (health >= 900){
        k_put_rect(texid, 43, 1);
    }

    sprintf(tim, "SCORE: %d", score);
    k_put_text(tim, 36, 2);

    sprintf(tim, "FUEL: %d / 10K", fuel);
    k_put_text(tim, 36, 3);

    sprintf(tim, "CREDITS: %d ", credits);
    k_put_text(tim, 36, 4);
}

void draw_inventory(){
    char tim[80];

    k_put_text("INVENTORY: ", 36, 6);

    // loop inventory
    int i;
    for(i = 0; i < num_items; i++){
        switch(inventory[i].type){
            case 1:
                sprintf(tim, "Ration : %s", inventory[i].data);
                break;
            case 2:
                sprintf(tim, "Handgun : %s", inventory[i].data);
                break;
            case 3:
                sprintf(tim, "Wrench : %s", inventory[i].data);
                break;
            case 4:
                sprintf(tim, "Ammunition : %s", inventory[i].data);
                break;
            case 5:
                sprintf(tim, "Grenade : %s", inventory[i].data);
                break;
            case 6:
                sprintf(tim, "Book : %s", inventory[i].data);
                break;
            case 7:
                sprintf(tim, "Machine Gun : %s", inventory[i].data);
                break;
            case 8:
                sprintf(tim, "Rocket Launcher : %s", inventory[i].data);
                break;
            case 9:
                sprintf(tim, "Pick : %s", inventory[i].data);
                break;
            case 10:
                sprintf(tim, "Medkit : %s", inventory[i].data);
                break;
            default:
                strcpy(tim, "Invalid Item!");
        }
        k_put_text(tim, 37, i + 8);
    }
    i++;

    k_put_text("QUESTS: ", 36, i + 8);

    i++;
    if (num_active_quests == 0){
        k_put_text("-[No Active Quests]", 36, i + 8);
    } else {
        for (int j = 0; j < num_active_quests; j++){
            char tmp[80];
            sprintf(tmp, "%s [%d]", quest_registry[npc_last.quest_id].title, quest_registry[npc_last.quest_id].id);
            k_put_text(tmp, 36, ++i + 8);
        }
    }
}

void draw_rogue(){
    int texid = 0;
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < HEIGHT; j++){
            if (rogue_npc_master[master_index](i - 15 + character_x, j - 15 + character_y).id <= 0) {
                int tdat = -1;
                if (((i - 15 + character_x) >= 0 && (i - 15 + character_x ) < cached_map.w) &&
                    ((j - 15 + character_y) >= 0 && (j - 15 + character_y ) < cached_map.h)) {
                    tdat = cached_map.tile_type[(i - 15 + character_x)  + (j - 15 + character_y) * cached_map.w];
                }

                switch (tdat){
                    case -1:
                        texid = BLACK_TEX;
                        break;
                    case 0:
                        texid = FLOOR_TEX;
                        break;
                    case 1:
                        texid = WALL_TEX;
                        break;
                    case 2:
                        texid = TURRET_TEX;
                        break;
                    case 3:
                        texid = BULLET_TEX;
                        break;
                    case 4:
                        texid = FIRE_TEX;
                        break;
                    case 5:
                        texid = FERN_TEX;
                        break;
                    case 6:
                        texid = CRATE_TEX;
                        break;
                    default:
                        texid = FLOOR_TEX;
                }
                if (tdat < -1){
                    //printf("T%d ", tdat);
                    texid = PORTAl_TEX;
                }
            } else {
                texid = NPC_TEX;
            }

            k_put_rect(texid, i, j);
        }
    }

    draw_stats();
    draw_inventory();

    for(int i = 0; i < num_entities; i++){
        k_put_rect(CRATE_TEX, 15 - character_x + entities[i].x, 15 - character_y + entities[i].y);
    }

    k_put_rect(GREEN_TEX, 15, 15);
}

void draw_use_item(int trade_index){
    char tim[80];

    k_put_text("Select Item: ", 0, 0);

    // loop inventory
    int i;
    for(i = 0; i < num_items; i++){
        switch(inventory[i].type){
            case 1:
                sprintf(tim, "Ration : %s", inventory[i].data);
                break;
            case 2:
                sprintf(tim, "Handgun : %s", inventory[i].data);
                break;
            case 3:
                sprintf(tim, "Wrench : %s", inventory[i].data);
                break;
            case 4:
                sprintf(tim, "Ammunition : %s", inventory[i].data);
                break;
            case 5:
                sprintf(tim, "Grenade : %s", inventory[i].data);
                break;
            case 6:
                sprintf(tim, "Book : %s", inventory[i].data);
                break;
            case 7:
                sprintf(tim, "Machine Gun : %s", inventory[i].data);
                break;
            case 8:
                sprintf(tim, "Rocket Launcher : %s", inventory[i].data);
                break;
            case 9:
                sprintf(tim, "Pick : %s", inventory[i].data);
                break;
            case 10:
                sprintf(tim, "Medkit : %s", inventory[i].data);
                break;
            default:
                strcpy(tim, "Invalid Item!");
        }

        k_put_text(tim, 2, i + 1);

        if (i == trade_index){
            //printf("%d %d \n", i, trade_index);
            k_put_text("->", 0, i + 1);
        }
    }
}

void draw_logo(){
    k_put_rects(LOGO_TEX, 0, 0, S_WIDTH, S_HEIGHT);
}
