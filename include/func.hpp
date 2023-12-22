#include <SFML/Graphics.hpp>
#include "word.hpp"

sf::Sprite get_tile(char letter, sf::Texture *tile_texture);

//void get_wod_map(const std::string word_list);
std::map<char, std::vector<std::pair<std::string, int>>> read_file(int *num_words);

void draw_word(word_t word, sf::RenderWindow *window);
