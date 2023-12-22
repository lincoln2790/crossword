#include <SFML/Graphics.hpp>
#include "word.hpp"

sf::Sprite get_tile(char letter, sf::Texture *tile_texture);

void draw_word(word_t word, sf::RenderWindow *window);
