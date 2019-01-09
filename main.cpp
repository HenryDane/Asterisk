#include <SFML/Graphics.hpp>
#include <iostream>
#include "main.h"
#include "draw.h"
#include "data.h"
#include "display.h"

// global system variables
int state = 0;
int selector = 0;
int select_max = 10;

// global environment properties
int level = 0;

// global character properties
int cha_x = 0;
int cha_y = 0;
int health = 0;
int score = 0;

// global SFML objects
sf::RenderTexture renderTexture;
sf::Font font;
sf::Text text;
sf::Clock scene_timer;

int main() {
    // configure random
    srand( time( NULL) );

    // create window
    sf::RenderWindow window(sf::VideoMode(S_WIDTH, S_HEIGHT), "Asterisk");

    // generate render texture
    if (!renderTexture.create(S_WIDTH, S_HEIGHT)) return 1000;

    // configure font and text objects
    if (!font.loadFromFile("res/font.ttf")) return 1001;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color(255, 255, 255));

    // load graphics
    init_sprites();

    // load gamedata
    setup_gamegata();

    std::cout << window.getSize().x << "," << window.getSize().y << std::endl;

    while (window.isOpen()) {
        //clear the screen
		window.clear();
        renderTexture.clear();

        //process events
		sf::Event event;
		while (window.pollEvent(event)) {
			//close when the window is closed
			if (event.type == sf::Event::Closed) {
				window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                // exit on esc
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return 0;
                }

				if (event.key.code == sf::Keyboard::Equal) {
					state++;
				} else if (event.key.code == sf::Keyboard::Subtract) {
					state--;
				}

                // is it a menu?
                if (state >= 1 && state <=6){
                    if (event.key.code == sf::Keyboard::Up ||
                        event.key.code == sf::Keyboard::W ||
                        event.key.code == sf::Keyboard::Numpad8) {
                        if (selector - 1 >= 0) selector--;
                    } else if (event.key.code == sf::Keyboard::Down ||
                        event.key.code == sf::Keyboard::S ||
                        event.key.code == sf::Keyboard::Numpad2) {
                        if (selector + 1 <= select_max) selector++;
                    }
                }

                // handle key presses
                switch (state) {
                case 0: // title screen
                    state = 1; // someone pressed a key???!
                    select_max = 5;
                    break;
                case 1: // main menu
                    if (event.key.code != sf::Keyboard::Enter) break;
                    switch (selector) {
                    case 0:
                        state = 9;
                        scene_timer.restart();
                        break;
                    case 1: // resume
                        break;
                    case 2:
                        state = 2;
                        selector = 0;
                        select_max = 6;
                        break;
                    case 3:
                        state = 3;
                        selector = 0;
                        select_max = 6;
                        break;
                    case 4: // options
                        state = 5;
                        selector = 0;
                        select_max = 6;
                        break;
                    case 5: // quit
                        return 0;
                        break;
                    }
                    break;
                case 2: // save game
                    if (event.key.code != sf::Keyboard::Enter) break;
                    if (selector >= 0 && selector <= 5) {
                        save_game(selector);
                    } else {
                        state = 1;
                        selector = 2;
                        select_max = 5;
                    }
                    break;
                case 3: // load game
                    if (event.key.code != sf::Keyboard::Enter) break;
                    if (selector >= 0 && selector <= 5) {
                        load_game(selector);
                    } else {
                        state = 1;
                        selector = 3;
                        select_max = 5;
                    }
                    break;
                case 4: // credits
                    // NOT IMPLEMENTED
                    break;
                case 5: // options
                    if (event.key.code != sf::Keyboard::Enter) break;
                    switch(selector){
                    case 0: // difficulty
                    case 1: // sound
                    case 2: // cheats
                    case 3: // debug
                    case 4: // reload sound
                    case 5: // reload gfx
                        std::cout << "NOT IMPLEMENTED" << std::endl;
                        break;
                    case 6: // back
                        state = 1;
                        selector = 4;
                        select_max = 5;
                        break;
                    }
                    break;
                case 6:
                    // NOT IMPLEMENTED
                    break;
                case 9: // opening cutscene
                    if (scene_timer.getElapsedTime().asSeconds() < OPENING_LENGTH) break;
                    state = 10;
                    break;
                case 10: // main mode (walking/exploring)
                    break;
                default:
                    break;
                }
            }
		}

        // handle key event unsynced key presses and draw behavior
        switch (state) {
        case 0:
            draw_title_screen();
            break;
        case 1:
            draw_main_menu();
            break;
        case 2:
            draw_save_menu();
            break;
        case 3:
            draw_load_menu();
            break;
        case 4:
            draw_credits();
            break;
        case 5:
            draw_options();
            break;
        case 6:
            draw_help();
            break;
        case 9:
            draw_opening();
            break;
        case 10:
            draw_rogue();
            break;
        default:
            break;
        }

        // prep the render texture
        renderTexture.display();

        // get the target texture (where the stuff has been drawn)
        const sf::Texture& texture = renderTexture.getTexture();

        // draw it to the window
        sf::Sprite sprite(texture);
        window.draw(sprite);

        // flip display
		window.display();

    }

    clean_gamedata();

    return 0;
}
