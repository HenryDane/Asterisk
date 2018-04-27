#include "main.h"

char null = 0;

char quest_str_dat [ QUEST_STR_DAT_LEN ] = "Hello\0Do you kno da wae?\0Hello ma brudda\0Spin on da fake kween\0Have you ever heard the tragedy of darth plageuis the wise\0What time is it?\0Summertime!\0";
int quest_1_data[] = { 0, -1, -1, -1, 6, -1, -1, -1};
int quest_1_verify[] = {0, 0, 0, 0, 0, 0, 0};
int quest_1_action[] = {0, 0, 0, 0, 0, 0, 0};
item_t quest_1_item[] = {{14523, 5, true, "Test Reward", 16}};
mquest_t quest_1 = {1,
                    "Test Quest",
                    "Test Issuer",
                    6,
                    1000,
                    5000,
                    quest_1_item,
                    quest_1_data,
                    quest_1_verify,
                    quest_1_action};

mquest_t quest_registry[ NUM_QUESTS_MAX + 1];
int num_active_quests;
mquest_a_t quest_a_registry[ NUM_QUESTS_MAX + 1];
quest_validate_function_ft quest_validate_master[NUM_QUESTS_MAX + 1];
quest_action_function_ft quest_action_master [NUM_QUESTS_MAX + 1];

// update for quest V/A registry
void init_quests(){
    quest_registry[1] = quest_1;
}

bool searchQuest(int quest_id){
    bool found = false;
    for (int i = 0; i < num_active_quests; i++){
        if (quest_a_registry[i].quest.id == quest_id){
            found = true;
            break;
        }
    }

    return found;
}
