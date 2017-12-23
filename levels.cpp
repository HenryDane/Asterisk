#include "struct.hpp"
#include "main.hpp"
#include <iostream>
using namespace std;

void search_and_build(const tile_data * tiledata){
    cout << "SECTOR: "  << sector_s << endl;

    // init vairables
    bool exists = false;
    int i = 0;

    // search
    for ( ; i < 10; i++){
        if (tiledata[i].x == sector_y && tiledata[i].y == sector_x){
            exists = true;
            cout << " FOUND W DESC: " << tiledata[i].data  << " I: " << i << endl;
            break;
        }
    }
    cout << "EXISTS " << ((exists) ? 1 : 0) << endl;

    // create entities
    if (exists){
        cout << "EXISTS!! NUM: " << tiledata[i].num_level_data << " I:" << i << endl;
        for(int j = 0; j < tiledata[i].num_level_data; j++){
            cout << "LOOKING AT J:" << j << endl;
            switch(tiledata[i].flight_data[j].type){
                case 0: // station
                    cout << "SPAWN STATION AT X:" << tiledata[i].flight_data[j].x;
                    cout << " Y: " << tiledata[i].flight_data[j].y << endl;

                    // create entity listing
                    entities[num_entities].id = id_entity_last;
                    entities[num_entities].x = tiledata[i].flight_data[j].x;
                    entities[num_entities].y = tiledata[i].flight_data[j].y;
                    entities[num_entities].type = 0;
                    for (int k = 0; k < 16; k++){
                        entities[num_entities].data[i] = tiledata[i].flight_data[j].data[i];
                    }
                    entities[num_entities].vx = 0;
                    entities[num_entities].vy = 0;
                    if (num_entities < MAX_ENTITIES) num_entities++;
                    id_entity_last++;
                    break;
                case 1: //asteroid
                    cout << "SPAWN ASTEROID AT X:" << tiledata[i].flight_data[j].x;
                    cout << " Y: " << tiledata[i].flight_data[j].y << endl;
                    for (int m = 0; m < tiledata[i].flight_data[j].num; m++){
                        entities[num_entities].id = id_entity_last;
                        entities[num_entities].x = tiledata[i].flight_data[j].x;
                        entities[num_entities].y = tiledata[i].flight_data[j].y;
                        entities[num_entities].type = 1;
                        for (int k = 0; k < 16; k++){
                            entities[num_entities].data[i] = tiledata[i].flight_data[j].data[i];
                        }
                        entities[num_entities].vx = (rand() % 5) - 2;
                        entities[num_entities].vy = (rand() % 5) - 2;
                        if (num_entities < MAX_ENTITIES) {
                            num_entities++;
                        }
                        id_entity_last++;
                    }
                    break;
                case 2: // enemy
                    cout << "SPAWN ENEMY AT X:" << tiledata[i].flight_data[j].x;
                    cout << " Y: " << tiledata[i].flight_data[j].y << endl;
                    for (int m = 0; m < tiledata[i].flight_data[j].num; m++){
                        entities[num_entities].id = id_entity_last;
                        entities[num_entities].x = tiledata[i].flight_data[j].x;
                        entities[num_entities].y = tiledata[i].flight_data[j].y;
                        entities[num_entities].type = 2;
                        for (int k = 0; k < 16; k++){
                            entities[num_entities].data[i] = tiledata[i].flight_data[j].data[i];
                        }
                        entities[num_entities].vx = (rand() % 10 > 5) ? -1 : 1;
                        entities[num_entities].vy = (rand() % 10 > 5) ? -1 : 1;
                        if (num_entities < MAX_ENTITIES) num_entities++;
                    }
                    break;
                case 3: // debris
                    cout << "SPAWN DEBRIS AT X:" << tiledata[i].flight_data[j].x;
                    cout << " Y: " << tiledata[i].flight_data[j].y << endl;
                    for (int m = 0; m < tiledata[i].flight_data[j].num; m++){
                        entities[num_entities].id = id_entity_last;
                        entities[num_entities].x = rand() % WIDTH;
                        entities[num_entities].y = rand() % HEIGHT;
                        entities[num_entities].type = 3;
                        for (int k = 0; k < 16; k++){
                            entities[num_entities].data[i] = tiledata[i].flight_data[j].data[i];
                        }
                        entities[num_entities].vx = 0;
                        entities[num_entities].vy = 0;
                        if (num_entities < MAX_ENTITIES) num_entities++;
                        id_entity_last++;
                    }
                    break;
                default:
                    cout << "FAILED WITH: " << tiledata[i].flight_data[j].type << endl;
            }
        }
    } else {
        cout << "SPAWNING NOTHING" << endl;
    }
}
