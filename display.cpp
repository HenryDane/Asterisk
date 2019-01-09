#include <SFML/Graphics.hpp>
#include <string>
#include "main.h"

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

