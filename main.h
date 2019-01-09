#include "SFML/Graphics.hpp"

#define S_WIDTH 800
#define S_HEIGHT 600

extern int state;
extern int selector;
extern int select_max;

extern int level;

extern int cha_x;
extern int cha_y;
extern int health;
extern int score;

extern sf::RenderTexture renderTexture;
extern sf::Font font;
extern sf::Text text;
extern sf::Clock scene_timer;

struct wb_obj_t {
    int id;
    int x;
    int y;
    int t;
    int idx;
    int frame;
};
