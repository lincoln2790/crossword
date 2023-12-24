#ifndef WORD_H
#define WORD_H

#include <list>
class tile_t;
class word_t{
	public:
	sf::Vector2f pos;
	std::list<tile_t> tiles;
	word_t(sf::Texture *tile_texture, std::string letters, float x, float y, int is_horiz, std::list<word_t> *word_list, int is_correct_, std::map<char, std::vector<std::pair<std::string, int>>>* word_map);
	int is_correct;
	std::string word;
};

#endif
