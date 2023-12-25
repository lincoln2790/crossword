
#include <SFML/Graphics.hpp>

sf::Sprite get_tile(char letter, sf::Texture *tile_texture);

//void get_wod_map(const std::string word_list);
std::map<char, std::vector<std::pair<std::string, int>>> read_file(int *num_words);

std::vector<int> find_letter_indices(std::string s, char c);

void crossword_dfs(word_t *root_word, std::set<word_t*> *visited_words, sf::RenderWindow *window, int is_correct);
word_t generate_clue(tile_t* tile, std::map<char,std::vector<std::pair<std::string, int>>>* word_map, sf::Texture *tile_texture, std::list<word_t> *word_list);
void draw_word(word_t word, sf::RenderWindow *window);
void draw_cursor_word(cursor_t *cursor, sf::RenderWindow *window, sf::Texture *tile_texture);
int check_cursor_word(cursor_t *cursor);
