#if USE_SDCC == 1
    #include "k_generic.c"
#endif // USE_SDCC

#if USE_SDCC == 2
    #include <SFML/Graphics.h>
    #include <stdio.h>
    #include <stdbool.h>

    #include "kernel.h"

    sfText * text;
    sfFont * font;
    sfRectangleShape * r;
    sfRenderWindow * window;
    sfEvent event;

    sfTexture * k_textures[NUM_K_TEXTURES];

    sfEventType k_get_sf_event_type();
    bool k_get_sf_key_shift();

    sfRenderWindow* k_get_window(){
        return window;
    }

    void k_put_text(char * stringin, int x, int y){
        sfText_setString(text, stringin);
        sfText_setPosition(text, (sfVector2f) {x * 16, y * 16});
        sfRenderWindow_drawText(window, text, NULL);
    }

    void k_put_rect(int tex_id, int x, int y){
        sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
        sfRectangleShape_setTexture(r, k_textures[tex_id], sfTrue);
        sfRectangleShape_setPosition(r, (sfVector2f) {x * 16, y * 16});
        sfRenderWindow_drawRectangleShape(window, r, NULL);
    }

    void k_put_rects(int tex_id, int x, int y, int w, int h){
        sfRectangleShape_setSize(r, (sfVector2f) {w, h});
        sfRectangleShape_setTexture(r, k_textures[tex_id], sfTrue);
        sfRectangleShape_setPosition(r, (sfVector2f) {x * 16, y * 16});
        sfRenderWindow_drawRectangleShape(window, r, NULL);
        sfRectangleShape_setSize(r, (sfVector2f) {16, 16});
    }

    void k_init_gfx(){
        printf("[K] INIT WINDOW \n");
        sfVideoMode mode = {S_WIDTH, S_HEIGHT, 32};
        window = sfRenderWindow_create(mode, "Asterisk I", sfResize | sfClose, NULL);
        if (!window){
            printf("[K] FAIL \n");
        }

        printf("[K] INIT TEXTURES \n");
        for (int i = 0; i < NUM_K_TEXTURES; i++){
            char tmp[32];
            sprintf(tmp, "res/%d.png", i);
            printf("[%d] \n", i);
            k_textures[i] = sfTexture_createFromFile(tmp, NULL);
        }

        printf("[K] INIT FONT \n");
        font = sfFont_createFromFile("res/telegrama_raw.ttf");
        if (!font) {
            printf("[K] FAIL \n");
        }

        printf("[K] INIT TEXT \n");
        text = sfText_create();
        sfText_setFont(text, font);
        sfText_setCharacterSize(text, 16);

        printf("[K] INIT RECT \n");
        r = sfRectangleShape_create();
        sfRectangleShape_setSize(r, (sfVector2f) {16, 16});

        printf("[K] INIT DONE \n");
    }

    bool k_this_close_request(){
        return sfRenderWindow_isOpen(window);
    }

    void k_refresh_display(){
        sfColor color_blk;
        color_blk.r = 0;
        color_blk.g = 0;
        color_blk.b = 0;
        color_blk.a = 255;
        sfRenderWindow_clear(window, color_blk);
    }

    bool k_get_events(){
        return sfRenderWindow_pollEvent(window, &event);
    }

    void k_display(){
        sfRenderWindow_display(window);
    }

    int k_get_key(){
        sfKeyCode kc = event.key.code;
        return (int) kc;
    }

    sfEventType k_get_sf_event_type(){
        return event.type;
    }

    bool k_get_sf_key_shift(){
        return event.key.shift;
    }
#endif // USE_SDCC

#if SDCC == 3
   #include "kernel/kpdcurses.c"
#endif // USE_SDCC
