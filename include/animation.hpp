#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <string>

#include "const.hpp"
#include "sf_const.hpp"

class game_t;
class animation_t{

	public:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2i pos; // pos of topleft pixel of starting frame in animation
		int sprite_width;
		int sprite_height;
		int sprite_scale;
		int is_inf;
		game_t *game_p;
		
		animation_t(std::string texture_path, int w, int h,int x, int y, game_t *game_p, int is_inf);
		void draw_sprite(int sprite_index);

};
#endif
