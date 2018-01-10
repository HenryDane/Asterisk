#include "main.hpp"
#include "terrain.hpp"
#include "display.hpp"
#include <iostream>
using namespace std;

typedef struct coord{
    int x;
    int y;
};

void fire_missile(int ix, int iy, int vx, int vy, int type){
    cout << "FIRED MISSILE" << endl;
    const char* dat = "!!!";
    entities[num_entities].type = type;
    entities[num_entities].x = ix;
    entities[num_entities].y = iy;
    for (int k = 0; k < 3; k++){
        entities[num_entities].data[k] = dat[k];
    }
    entities[num_entities].id = id_entity_last;
    entities[num_entities].vx = vx;
    entities[num_entities].vy = vy;
    num_entities++;
    id_entity_last++;
}

coord enemy_think_1(int address){
    // roll to fire missile
    if (rand() % 10 < 5){
        // compute missile direction
        coord m = {(character_x > entities[address].x) ? 1 : -1 , (character_y > entities[address].y) ? 1 : -1};

        // add missile
        fire_missile(entities[address].x, entities[address].y, m.x, m.y, 5);
    }

    //return dx, dy
    coord d = {(character_x > entities[address].x) ? -1 : 1 , (character_y > entities[address].y) ? 1 : -1};
    coord n = { 0, 0};
    return ( (((unsigned) (character_x - entities[address].x)) < 10) && (((unsigned) (character_y - entities[address].y)) < 10)) ? d : n;
}

void update_entities(){
    // draw entities
    if (time_entity > TIME_ENTITY ){
        time_entity = 0;
        for (int i = 0; i < num_entities; i++){
            if (entities[i].type != 5 && entities[i].type >= 0){
                if (entities[i].x >= WIDTH - 1 || entities[i].x <= 0) entities[i].vx = - entities[i].vx;
                if (entities[i].y >= HEIGHT - 1 || entities[i].y <= 0) entities[i].vy = - entities[i].vy;
                if (entities[i].type == 2){
                    coord t = enemy_think_1(i);
                    entities[i].x += t.x;
                    entities[i].y += t.y;
                    cout << "TICKED ENTITY: " << i << " WITH VX: " << t.x << " WITH VY: " << t.y << endl;
                } else {
                    entities[i].x += entities[i].vx;
                    entities[i].y += entities[i].vy;
                }

                if (entities[i].x == character_x && entities[i].y == character_y && (entities[i].type == 1 || entities[i].type == 3)){
                    cout << "COLLISION !!";
                    state = -2;
                }
            }
        }
    }

    if (time_rocket > TIME_ROCKET){
        time_rocket = 0;
        for (int i = 0; i < num_entities; i++){
            if (entities[i].type == 5){
                if (entities[i].x >= WIDTH + 1 || entities[i].x <= -1) entities[i].type = -10;
                if (entities[i].y >= HEIGHT + 1 || entities[i].y <= -1) entities[i].type = -10;
                entities[i].x += entities[i].vx;
                entities[i].y += entities[i].vy;

                if (entities[i].x == character_x && entities[i].y == character_y && entities[i].type == 6){
                    cout << "COLLISION !!!!";
                    state = -2;
                }
            }
        }
    }

    // draw character
    int facing_t = facing;
    if (tilted){
        facing_t += 4;
    }
    if (time_character > TIME_CHARACTER){
        time_character = 0;
        fuel--;
        switch(facing_t){
            case 0: character_y--; break;
            case 1: character_x++; break;
            case 2: character_y++; break;
            case 3: character_x--; break;
            case 4: character_y--; character_x++; break;
            case 5: character_x++; character_y++; break;
            case 6: character_y++; character_x--; break;
            case 7: character_x--; character_y--; break;
            default: break;
        }

        if (character_x > WIDTH - 1) character_x = WIDTH;
        if (character_x < 0) character_x = 0;
        if (character_y > HEIGHT - 1) character_y = HEIGHT;
        if (character_y < 0) character_y = 0;
    }
}

void update_warp_interface(void){
    e1_g = rand() % 9;
    e1_y = 9;
    e2_g = rand() % 9;
    e2_y = 9;
    e3_g = rand() % 9;
    e3_y = 9;
    e4_g = rand() % 9;
    e4_y = 9;
}
