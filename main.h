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

struct chart_object_t {
    int chart;
    int x;
    int y;
    std::string label;
    int num_obj;
    int ref_addr; // reference to sector data
};

struct sector_object_t {
    int x; // if negative then this is the number of instances
    int y; // if negative one then random, if negative two then random with respawn (offscreen)
    std::string label;
    int type;
    int dock_address; // if negative then non-dockable
};

struct chest_t {
    int id;
    int num_items;
    int item_address;
    bool valid;
};

struct enemy_t {
    int id;
    int x;
    int y;
    int t;
    int state;

    void tick() {
        return; // TODO add entity AI
    }
};

struct portal_t {
    int id;
    int tx;
    int ty;
};
