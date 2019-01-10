#include <SFML/Graphics.hpp>
#include <string>
#include "main.h"
#include "patch.h"

#define NUM_SPRITES 6

// yes i know this is memory intensive
sf::Texture * textures;
sf::Sprite * sprites;

void init_sprites() {
    textures = new sf::Texture[NUM_SPRITES];
    sprites = new sf::Sprite[NUM_SPRITES];

    for (int i = 0; i < NUM_SPRITES; i++) {
        textures[i].loadFromFile("res/sprite" + patch::to_string(i) + ".bmp");
        sprites[i] = sf::Sprite(textures[i]);
        sprites[i].setPosition(i * 8, 0);
    }
}

void draw_all_sprites() {
    for (int i = 0; i < NUM_SPRITES; i++) {
        renderTexture.draw(sprites[i]);
    }
}

void draw_sprite(int t, int x, int y) {
    if (t < 0 || t >= NUM_SPRITES) return; // slow, remove later
    sprites[t].setPosition(x, y);
    renderTexture.draw(sprites[t]);
}

void put_text(std::string s, int x, int y){
    text.setString(s);
    text.setPosition(x, y);
    renderTexture.draw(text);
}

void put_text_vhc(std::string s) {
    text.setString(s);
    sf::FloatRect b = text.getLocalBounds();
    text.setPosition((S_WIDTH - b.width) / 2, (S_HEIGHT - b.height) / 2);
    renderTexture.draw(text);
}

void put_text_hc(std::string s, int y) {
    text.setString(s);
    sf::FloatRect b = text.getLocalBounds();
    text.setPosition((S_WIDTH - b.width) / 2, y);
    renderTexture.draw(text);
}

void text_style_normal() {
    text.setFillColor(sf::Color(255, 255, 255));
    text.setStyle(0);
    text.setCharacterSize(16);
}

void text_style_menu_select() {
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color(127, 0, 255));
}

