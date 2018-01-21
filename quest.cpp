#include "main.hpp"

bool validate_empty(){
    return true;
}

void assign_empty(){
    // do nothing
}

const quest_dialogue_t example_dialogue_1[3] = {{"Hello person", 12, 0}, {"Hello Example NPC", 12, 0}, {"Hello world", 12, 0}};
const quest_dialogue_t example_dialogue_2[3] = {{"Hello person (2_", 16, 0}, {"Hello Example NPC.", 13, 0}, {"Hello world-", 13, 0}};
const quest_dialogue_t example_dialogue_3[3] = {{"Hello person .3", 15, 0}, {"Hello Example NPC..", 14, 0}, {"Hello world--", 14, 0}};

quest_assign_ft ex_asn_func[3] = {assign_empty, assign_empty, assign_empty};

quest_validate_ft ex_val_func[3] = {validate_empty, validate_empty, validate_empty};

const quest_dialogue_block_t example_quest_dialogue_block [3] = { {0, example_dialogue_1, 3}, {0, example_dialogue_2, 3}, {0, example_dialogue_3, 3}};

const quest_t example_quest = {1029, "Example Quest", 13, "Example NPC", 11, example_quest_dialogue_block, ex_val_func, ex_asn_func, 3, 10, 10, {192, 2, true, "ex_quest", 8}};

quest_t quest_registry[NUM_QUESTS + 1] = {example_quest, example_quest};

quest_active_t active_quests[ NUM_QUESTS_MAX ] = {{0, "Null Quest", 10, "Null", 4, example_quest_dialogue_block, ex_val_func, ex_asn_func, 3, 10, 10, {192, 2, true, "ex_quest", 8}}, 1000, true};
