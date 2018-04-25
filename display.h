int init_displays(void);
void cleardisplay(bool _debug);

void update_warp_interface(void); // why is this in this file?

void display(); // void draw_space();
void draw_engine_config();
void draw_prewarp(int x, int y, int s);
void draw_warp(int x, int y, int s);
void draw_quests();
void draw_cutscene();
void draw_trade(int trade_index);
void draw_stats();
void draw_inventory();
void draw_rogue();
void draw_use_item(int trade_index);
void draw_drop();
void draw_sell();
void draw_module_manage();
void draw_credits();
void draw_main_menu();
void draw_logo();
void draw_game_over(void);
