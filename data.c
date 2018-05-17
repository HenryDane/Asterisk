#include <stdio.h>

#include "main.h"

bool save(int slot){
    FILE *fp; // file for saving too
    char tmp[80];

    sprintf(tmp, "savedata%d.txt", slot);
    fp = fopen(tmp, "w+");

    // header
    fputc('S', fp);
    fputc(slot, fp);

    // save type -- (S)elf (G)enerated (F)ile version (1)
    // asterisk may put out different types
    fputc('S', fp);
    fputc('G', fp);
    fputc('F', fp);
    fputc('1', fp);

    // write entities_o
    printf("Writing space entity definitions \n");
    fputc(num_entities_o, fp);
    for (int i = 0; i < num_entities_o; i++){
        fputc(entities_o[i].id, fp);
        fputc(entities_o[i].type, fp);
        fputc(entities_o[i].vx, fp);
        fputc(entities_o[i].vy, fp);
        fputc(entities_o[i].x, fp);
        fputc(entities_o[i].y, fp);
    }

    printf("Writing entity definitions\n");
    fputc(num_entities, fp);
    for (int i = 0; i < num_entities_o; i++){
        fputc(entities[i].id, fp);
        fputc(entities[i].type, fp);
        fputc(entities[i].x, fp);
        fputc(entities[i].y, fp);
        fputc(entities[i].vx, fp);
        fputc(entities[i].vy, fp);
    }

    // write hidden npcs
    printf("Writing hidden NPCs \n");
    fputc(num_hidden_npcs, fp);
    for (int i = 0; i < NUM_HIDDEN_NPCS_MAX; i++){
        fputc(hidden_npcs[i], fp);
    }

    // write inventory
    printf("Write inventory data \n");
    fputc(num_items, fp);
    for (int i = 0; i < num_items; i++){
        fputc(inventory[i].id, fp);
        fputc(inventory[i].type, fp);
        fputc(inventory[i].unuseable, fp);
    }

    // write dropped items
    printf("Writing ground items \n");
    fputc(num_dropped_items, fp);
    for (int i = 0; i < NUM_DROPPED_MAX; i++){
        fputc(dropped_items[i].item.id, fp);
        fputc(dropped_items[i].item.type, fp);
        fputc(dropped_items[i].item.unuseable, fp);
        fputc(dropped_items[i].mapid, fp);
        fputc(dropped_items[i].x, fp);
        fputc(dropped_items[i].y, fp);
    }

    // write character data
    printf("Saving the character\n");
    fputc(character_x, fp);
    fputc(character_y, fp);
    fputc(health, fp);
    fputc(experience, fp);
    fputc(fuel, fp);
    fputc(rounds, fp);
    fputc(credits, fp);
    fputc(location, fp);
    fputc(score, fp);

    // write space character data
    fputc(ship_x, fp);
    fputc(ship_y, fp);
    fputc(sector_s, fp);
    fputc(sector_x, fp);
    fputc(sector_y, fp);
    fputc(level, fp);
    fputc(tilted, fp);
    fputc(facing, fp);

    // write module data
    printf("Writing modules \n");
    for(int i = 0; i < NUM_MODULES_MAX; i++){
        fputc(modules_enabled[i], fp);
    }

    // write timer data
    printf("Writing timer data \n");
//    fputc(timerval, fp); // where did this go? what is it?
    fputc(time_character, fp);
    fputc(time_cutscene, fp);
//    fputc(time_entity, fp); // where did this go? what is it?
    fputc(time_entity_o, fp);
    fputc(ticks_for_warp, fp);

    // save current quests
    printf("Writing active quest data \n");
    fputc(num_active_quests, fp);
    for (int i = 0; i < num_active_quests; i++){
        fputc(quest_a_registry[i].position, fp);
        fputc(quest_a_registry[i].quest.id, fp); // ALL QUESTS MUST HAVE UNIQUE IDS
    }

    // save internals
    printf("Saving system data \n");
    fputc(state, fp);
    fputc(npc_last.frame_id, fp);
    fputc(npc_last.health, fp);
    fputc(npc_last.id, fp);
    fputc(npc_last.inventory_size, fp);
    fputc(npc_last.is_ablaze, fp);
    fputc(npc_last.is_alive, fp);
    fputc(npc_last.is_merchant, fp);
    fputc(npc_last.quest_id, fp);
    fputc(npc_last.type, fp);
    fputc(npc_last.x, fp);
    fputc(npc_last.y, fp);
    fputc(trade_index, fp);
    fputc(selected_module, fp);
    fputc(selected_object, fp);

    fclose(fp);
    printf("Done. \n");

    return true;
}

bool load(int slot){
    char header[6];
    FILE * fp;
    char tmp[80];

    int buffer[16];

    sprintf(tmp, "savedata%d.txt", slot);
    fp = fopen(tmp, "r+");

    for(int i = 0; i < 6; i++){
        header[i] = fgetc(fp);
    }

    header[1] += 33;

    printf("Reading slot %d (%d), found header: %.6s \n", slot, header[1] - 33, header);

    if(header[0] != 'S'){
        printf("Header has bad starting byte \n");
        return false;
    } else if (header[1] - 33 != slot){
        printf("Slotting does not make sense \n");
        return false;
    } else {
        printf("Header ok, continuing \n");
    }

    // entity definitions
    int num;
    num_entities_o = fgetc(fp);
    printf("Reading %d space entities \n", num_entities_o);
    for(int i = 0; i < num_entities_o; i++){
        for(int j = 0; j < 6; j++){
            buffer[i] = fgetc(fp);
        }
        entities_o[i] = (o_entity_t) {buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]};
    }

    num_entities = fgetc(fp);
    printf("Reading %d entities \n", num_entities);
    for(int i = 0; i < num_entities; i++){
        for(int j = 0; j < 6; j++){
            buffer[i] = fgetc(fp);
        }
        entities[i] = (entity_t) {buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]};
    }

    num_hidden_npcs = fgetc(fp);
    printf("Reading %d hidden NPCs \n");
    for (int i = 0; i < NUM_HIDDEN_NPCS_MAX; i++){
        hidden_npcs[i] = fgetc(fp);
    }

    // read inventory
    num_items = fgetc(fp);
    printf("Reading %d items to inventory \n", num_items);
    for (int i = 0; i < num_items; i++){
        inventory[i].id = fgetc(fp);
        inventory[i].type = fgetc(fp);
        inventory[i].unuseable = fgetc(fp);
    }

    num_dropped_items = fgetc(fp);
    printf("Picking up %d dropped items \n", num_dropped_items);
    for (int i = 0; i < NUM_DROPPED_MAX; i++){
        dropped_items[i].item.id = fgetc(fp);
        dropped_items[i].item.type = fgetc(fp);
        dropped_items[i].item.unuseable = fgetc(fp);
        dropped_items[i].mapid  = fgetc(fp);
        dropped_items[i].x = fgetc(fp);
        dropped_items[i].y = fgetc(fp);
    }

    printf("Creating the character\n");
    character_x = fgetc(fp);
    character_y = fgetc(fp);
    health = fgetc(fp);
    experience = fgetc(fp);
    fuel = fgetc(fp);
    rounds = fgetc(fp);
    credits = fgetc(fp);
    location = fgetc(fp);
    score = fgetc(fp);

    // read space character data
    ship_x = fgetc(fp);
    ship_y = fgetc(fp);
    sector_s = fgetc(fp);
    sector_x = fgetc(fp);
    sector_y = fgetc(fp);
    level = fgetc(fp);
    tilted = fgetc(fp);
    facing = fgetc(fp);

    // read module data
    printf("Reading modules \n");
    for(int i = 0; i < NUM_MODULES_MAX; i++){
        modules_enabled[i] = fgetc(fp);
    }

    // write timer data
    printf("Writing timer data \n");
    // timerval ??
    time_character = fgetc(fp);
    time_cutscene = fgetc(fp);
    // time entity???
    time_entity_o = fgetc(fp);
    ticks_for_warp = fgetc(fp);

    // save current quests
    num_active_quests = fgetc(fp);
    printf("Writing active quest data \n");
    for (int i = 0; i < num_active_quests; i++){
        quest_a_registry[i].position = fgetc(fp);

        // assemble quest
        /*quest_a_registry[i].quest.id*/ int id = fgetc(fp);
        int a = 0;
        for ( ; a < NUM_QUESTS; a++){
            if (id == quest_registry[a].id) {
                printf("Found at %d (%d == %d) \n", a, id, quest_registry[a].id);
                break;
            }
        }

        if (a >= NUM_QUESTS){
            printf("Found quest with invalid ID value! \n");
            break;
        }

        quest_a_registry[i].quest = quest_registry[a];
    }

    printf("Saving system data \n");
    state = fgetc(fp);
    npc_last.frame_id = fgetc(fp);
    npc_last.health = fgetc(fp);
    npc_last.id = fgetc(fp);
    npc_last.inventory_size = fgetc(fp);
    npc_last.is_ablaze = fgetc(fp);
    npc_last.is_alive = fgetc(fp);
    npc_last.is_merchant = fgetc(fp);
    npc_last.quest_id = fgetc(fp);
    npc_last.type = fgetc(fp);
    npc_last.x = fgetc(fp);
    npc_last.y = fgetc(fp);
    trade_index = fgetc(fp);
    selected_module = fgetc(fp);
    selected_object = fgetc(fp);

    fclose(fp);
    printf("Done \n");
    return true;
}

