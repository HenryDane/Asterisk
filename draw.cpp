#include "main.h"
#include "display.h"
#include "patch.h"
#include "data.h"

void draw_opening(){
    put_text_vhc("OPENING CUTSCENE PLACEHOLDER\nTIME=" + patch::to_string(scene_timer.getElapsedTime().asSeconds()));
}

void draw_rogue(){

}

void draw_title_screen(){
    draw_all_sprites();

    text.setCharacterSize(32);
    text.setFillColor(sf::Color(0, 127, 255));
    put_text_vhc("ASTETRISK");
    text_style_normal();

    put_text_hc("Press any key", (S_HEIGHT / 2) + 50);
}

void draw_main_menu(){
    text.setFillColor(sf::Color(0, 127, 255));
    text.setCharacterSize(32);
    put_text_hc("ASTERISK", (S_HEIGHT / 2) - 128);
    text_style_normal();

    (selector == 0) ? text_style_menu_select() : text_style_normal(); put_text_hc("New", (S_HEIGHT / 2) - 48);
    (selector == 1) ? text_style_menu_select() : text_style_normal(); text.setFillColor(sf::Color(127, 127, 127)); put_text_hc("Resume", (S_HEIGHT / 2) - 32);
    (selector == 2) ? text_style_menu_select() : text_style_normal(); put_text_hc("Save", (S_HEIGHT / 2) - 16);
    (selector == 3) ? text_style_menu_select() : text_style_normal(); put_text_hc("Load", (S_HEIGHT / 2));
    (selector == 4) ? text_style_menu_select() : text_style_normal(); put_text_hc("Options", (S_HEIGHT / 2) + 16);
    (selector == 5) ? text_style_menu_select() : text_style_normal(); put_text_hc("Quit", (S_HEIGHT / 2) + 32);
    text_style_normal();
}

void draw_save_menu(){
    text.setFillColor(sf::Color(0, 127, 255));
    text.setCharacterSize(32);
    put_text_hc("ASTERISK", (S_HEIGHT / 2) - 128);
    text_style_normal();

    put_text_hc("Save to slot ...", (S_HEIGHT / 2) - 64);
    (selector == 0) ? text_style_menu_select() : text_style_normal(); put_text_hc("SLOT 0", (S_HEIGHT / 2) - 48);
    (selector == 1) ? text_style_menu_select() : text_style_normal(); put_text_hc("SLOT 1", (S_HEIGHT / 2) - 32);
    (selector == 2) ? text_style_menu_select() : text_style_normal(); put_text_hc("SLOT 2", (S_HEIGHT / 2) - 16);
    (selector == 3) ? text_style_menu_select() : text_style_normal(); put_text_hc("SLOT 3", (S_HEIGHT / 2));
    (selector == 4) ? text_style_menu_select() : text_style_normal(); put_text_hc("SLOT 4", (S_HEIGHT / 2) + 16);
    (selector == 5) ? text_style_menu_select() : text_style_normal(); put_text_hc("SLOT 5", (S_HEIGHT / 2) + 32);
    (selector == 6) ? text_style_menu_select() : text_style_normal(); put_text_hc("Back", (S_HEIGHT / 2) + 64);
    text_style_normal();
}

void draw_load_menu(){
    text.setFillColor(sf::Color(0, 127, 255));
    text.setCharacterSize(32);
    put_text_hc("ASTERISK", (S_HEIGHT / 2) - 128);
    text_style_normal();

    put_text_hc("Load from slot ...", (S_HEIGHT / 2) - 64);
    (selector == 0) ? text_style_menu_select() : text_style_normal(); put_text_hc("SLOT 0", (S_HEIGHT / 2) - 48);
    (selector == 1) ? text_style_menu_select() : text_style_normal(); put_text_hc("SLOT 1", (S_HEIGHT / 2) - 32);
    (selector == 2) ? text_style_menu_select() : text_style_normal(); put_text_hc("SLOT 2", (S_HEIGHT / 2) - 16);
    (selector == 3) ? text_style_menu_select() : text_style_normal(); put_text_hc("SLOT 3", (S_HEIGHT / 2));
    (selector == 4) ? text_style_menu_select() : text_style_normal(); put_text_hc("SLOT 4", (S_HEIGHT / 2) + 16);
    (selector == 5) ? text_style_menu_select() : text_style_normal(); put_text_hc("SLOT 5", (S_HEIGHT / 2) + 32);
    (selector == 6) ? text_style_menu_select() : text_style_normal(); put_text_hc("Back", (S_HEIGHT / 2) + 64);
    text_style_normal();
}

void draw_credits(){
    // NOT IMPLEMENTED
}

void draw_options(){
    text.setFillColor(sf::Color(0, 127, 255));
    text.setCharacterSize(32);
    put_text_hc("ASTERISK", (S_HEIGHT / 2) - 128);
    text_style_normal();

    (selector == 0) ? text_style_menu_select() : text_style_normal(); put_text_hc("Difficulty [NORMAL]", (S_HEIGHT / 2) - 48);
    (selector == 1) ? text_style_menu_select() : text_style_normal(); put_text_hc("Sound [100%]", (S_HEIGHT / 2) - 32);
    (selector == 2) ? text_style_menu_select() : text_style_normal(); put_text_hc("Cheats [OFF]", (S_HEIGHT / 2) - 16);
    (selector == 3) ? text_style_menu_select() : text_style_normal(); put_text_hc("Debug [OFF]", (S_HEIGHT / 2));
    (selector == 4) ? text_style_menu_select() : text_style_normal(); put_text_hc("Reload Sound", (S_HEIGHT / 2) + 16);
    (selector == 5) ? text_style_menu_select() : text_style_normal(); put_text_hc("Reload Graphics", (S_HEIGHT / 2) + 32);
    (selector == 6) ? text_style_menu_select() : text_style_normal(); put_text_hc("Back", (S_HEIGHT / 2) + 64);
}

void draw_help(){
    // NOT IMPLEMENTED
}

