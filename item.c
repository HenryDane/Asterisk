#include "main.h"

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
}

void drop_item(item_t * item, int x, int y, int mapid){
    if (num_dropped_items >= NUM_DROPPED_MAX - 1) return;

    d_item_t dropped_item;

    dropped_item.item = * item;
    dropped_item.x = x;
    dropped_item.y = y;
    dropped_item.mapid = mapid;

    dropped_items[num_dropped_items++] = dropped_item;
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
}
