#include "main.h"
#include "modules.h"
#include <stdio.h>

void drop_item_c(int index){
    if (num_dropped_items >= NUM_DROPPED_MAX - 1) return;

    item_t dropped_item = inventory[index];
    d_item_t d_item;
    d_item.item = dropped_item;
    d_item.x = character_x;
    d_item.y = character_y;
    d_item.mapid = master_index;
    dropped_items[num_dropped_items++] = d_item;

    // delete from inventory
    if (num_items > 0){
        for (int i = index; i < num_items - 1; i++){
            inventory[i] = inventory[i + 1];
        }

        num_items--;
    } else {
        num_items = 0;
    }

    trade_index = 0;
}

void drop_item(item_t * item, int x, int y, int mapid){
    if (num_dropped_items >= NUM_DROPPED_MAX - 1) return;

    d_item_t dropped_item;

    dropped_item.item = * item;
    dropped_item.x = x;
    dropped_item.y = y;
    dropped_item.mapid = mapid;

    dropped_items[num_dropped_items++] = dropped_item;

    trade_index = 0;
}

bool collect_item(item_t * item, int x, int y, int mapid){
    int i = 0;

    if (num_dropped_items <= 0) return false;

    for ( ; i < NUM_DROPPED_MAX; i++){
        if (dropped_items[i].x == x && dropped_items[i].y == y && dropped_items[i].mapid == mapid){
            printf("Found item at address %d \n", i);

            * item = dropped_items[i].item;

            // clean up
            for (int j = i; j < num_dropped_items - 1; j++){
                dropped_items[j] = dropped_items[j + 1];
            }
            num_dropped_items--;

            // leave early
            return true;
        }
    }

    return false;

    trade_index = 0;
}

void use_item(int type){
    bool erase = false;
    int i = 0;
    int j = 0;
    int w = 0;
    int h = 0;

    switch (type){
        case 10: // medkit
            health += 250;
        case 1: // ration
            health += (rand() % 4) + 1;
            erase = true;
            break;
        case 4: // ammo
            rounds += 10000;
            erase = true;
            break;
        case 13: // speed (+10%) module item (type = 1)
            add_module(1);
            erase = true;
            break;
        case 14: // speed (+20%) module item (type = 2)
            add_module(2);
            erase = true;
            break;
        case 15: // speed (+100%) module item (type = 3)
            add_module(3);
            erase = true;
            break;
        case 16: // damage (+10%) module item (type = 4)
            add_module(4);
            erase = true;
            break;
        case 17: // damge (+20%) module item (type = 5)
            add_module(5);
            erase = true;
            break;
        case 18: // damage (+100%) module item (type = 6)
            add_module(6);
            erase = true;
            break;
        case 19: // warp speed (+50%) module item (type = 7)
            add_module(7);
            erase = true;
            break;
        case 20: // engine integrity (+50%) module item (type = 8)
            add_module(8);
            erase = true;
            break;
        case 21: // energy & tractor module item (type = 9)
            add_module(9);
            erase = true;
            break;
        case 5: // grenade
            w = cached_map.w;
            h = cached_map.h;
            for (i = -4; i < 5; i++){
                for (j = -4; j < 5; j++){
                    if (character_x + i >= 0 && character_y + i >= 0 && character_x + i < w && character_y + j < h){
                        if (cached_map.tile_type[(character_x + i) + (character_y + j) * w ] == 0 ||
                            cached_map.tile_type[(character_x + i) + (character_y + j) * w ] == 12){
                            cached_map.tile_type[(character_x + i) + (character_y + j) * h ] = 106;
                        }
                    }
                }
            }
            erase = true;
            break;
        default:
            printf("using undefined item \n");
            erase = false;
            break;
    }

    // remove item
    if (erase){
        for (int i = trade_index; i < num_items; i++){
            inventory[i] = inventory[(i + 1 < num_items) ? i + 1 : i];
        }
        if (num_items > 0) num_items --;
    }

    trade_index = 0;
}

int item_get_tex(int type){
    switch(type){
        case 1: // food
            return FOOD_ITEM_TEX;
        case 2: // handgun
            return GUN_ITEM_TEX;
        case 3: // wrench
            return WRENCH_ITEM_TEX;
        case 4: // ammo
            return BULLET_ITEM_TEX;
        case 5: // grenade
            return GRENADE_ITEM_TEX;
        case 6: // book
            return BOOK_ITEM_TEX;
        case 7: // machine gun
            return MG_ITEM_TEX;
        case 8: // rocket launcher
            return RL_ITEM_TEX;
        case 9: // pick
            return PICK_ITEM_TEX;
        case 10: // medkit
            return MEDKIT_ITEM_TEX;
        case 11: // drill
            return DRILL_TEX;
        case 12: // welder
            return WELDER_TEX;
        case 13: // speed (+10%) module item (type = 1)
        case 14: // speed (+20%) module item (type = 2)
        case 15: // speed (+100%) module item (type = 3)
        case 16: // damage (+10%) module item (type = 4)
        case 17: // damge (+20%) module item (type = 5)
        case 18: // damage (+100%) module item (type = 6)
        case 19: // warp speed (+50%) module item (type = 7)
        case 20: // engine integrity (+50%) module item (type = 8)
        case 21: // energy & tractor module item (type = 9)
            return MODULE_TEX;
        case 22: // tnt item
            return TNT_TEX;
        case 23: // turret item
            return TURRET_ITEM_TEX;
        case 24: // silver medal
            return SILVER_TEX;
        case 25: // purple heart
            return PURPLE_HEART_TEX;
        case 26: // fuel cannister
            return FUEL_ITEM_TEX;
        case 27: // platinum medal
            return PLATINUM_TEX;
        case 28: // bronze medal
            return BRONZE_TEX;
        case 29: // gold medal
            return GOLD_TEX;
        default: // unknown
            return DEBUG_TEX;
    }
}

void print_item(char * tmp, item_t * item){
    switch(item->type){
            case 1:
                sprintf(tmp, "%s Ration", item->data);
                break;
            case 2:
                sprintf(tmp, "%s Handgun", item->data);
                break;
            case 3:
                sprintf(tmp, "%s Wrench", item->data);
                break;
            case 4:
                sprintf(tmp, "%s Ammunition", item->data);
                break;
            case 5:
                sprintf(tmp, "%s Grenade", item->data);
                break;
            case 6:
                sprintf(tmp, "%s Book", item->data);
                break;
            case 7:
                sprintf(tmp, "%s Machine Gun", item->data);
                break;
            case 8:
                sprintf(tmp, "%s Rocket Launcher", item->data);
                break;
            case 9:
                sprintf(tmp, "%s Pick", item->data);
                break;
            case 10:
                sprintf(tmp, "%s Medkit", item->data);
                break;
            case 13: // speed (+10%) module item (type = 1)
            case 14: // speed (+20%) module item (type = 2)
            case 15: // speed (+100%) module item (type = 3)
            case 16: // damage (+10%) module item (type = 4)
            case 17: // damage (+20%) module item (type = 5)
            case 18: // damage (+100%) module item (type = 6)
            case 19: // warp speed (+50%) module item (type = 7)
            case 20: // engine integrity (+50%) module item (type = 8)
            case 21: // energy & tractor module item (type = 9)
                sprintf(tmp, "%s Module", item->data);
                break;
            case 28: // bronze medal
                sprintf(tmp, "Bronze Medal %s", item->data);
                break;
            case 29: // gold medal
                sprintf(tmp, "Gold Medal %s", item->data);
                break;
            case 24: // silver medal
                sprintf(tmp, "Silver Medal %s", item->data);
                break;
            case 25: // purple heart
                sprintf(tmp, "Purple Heart %s", item->data);
                break;
            case 26: // fuel cannister
                sprintf(tmp, "%s Fuel Cannister", item->data);
                break;
            case 27: // purple heart
                sprintf(tmp, "Platinum Medal %s", item->data);
                break;
            default:
                strcpy(tmp, "Invalid Item!");
                break;
        }

}
