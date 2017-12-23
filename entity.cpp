#include "main.hpp"
#include "terrain.hpp"
#include "display.hpp"
#include <iostream>
using namespace std;

void update_entities(){
    // draw entities
    if (time_entity > TIME_ENTITY ){
        time_entity = 0;
        for (int i = 0; i < num_entities; i++){
            if (entities[i].type != 5 && entities[i].type >= 0){
                if (entities[i].x >= WIDTH - 1 || entities[i].x <= 0) entities[i].vx = - entities[i].vx;
                if (entities[i].y >= HEIGHT - 1 || entities[i].y <= 0) entities[i].vy = - entities[i].vy;
                entities[i].x += entities[i].vx;
                entities[i].y += entities[i].vy;

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
                if (entities[i].x >= WIDTH - 1 || entities[i].x <= 0) entities[i].type = -10;
                if (entities[i].y >= HEIGHT - 1 || entities[i].y <= 0) entities[i].type = -10;
                entities[i].x += entities[i].vx;
                entities[i].y += entities[i].vy;

                if (entities[i].x == character_x && entities[i].y == character_y && (entities[i].type == 5)){
                    cout << "COLLISION !!";
                    state = -2;
                }
            }
        }
    }

    // draw character
    if (time_character > TIME_CHARACTER){
        time_character = 0;
        switch(facing){
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
