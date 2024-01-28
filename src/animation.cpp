#include "../include/animation.hpp"
#include "../include/game.hpp"

animation_t::animation_t(std::string texture_path, int w, int h, int x, int y, game_t *game_p, int is_inf):
	sprite_width(w),
	sprite_height(h),
	game_p(game_p),
	is_inf(is_inf)
{
	texture.loadFromFile(texture_path);
	texture.setSmooth(true);
	if(is_inf){
		texture.setRepeated(true); //change to constructor paramete
	}
	sprite.setTexture(texture);
	//sprite.setTextureRect(sf::IntRect(x, y, sprite_width, sprite_height));
    pos = sf::Vector2i(x,y);
}


void animation_t::draw_sprite(int sprite_index){
	if(is_inf){
		sf::Vector2i pixel_pos(0,0);
		sf::Vector2f window_pos = game_p->window.mapPixelToCoords(pixel_pos);
		sprite.setPosition(window_pos);
		sprite.setTextureRect(sf::IntRect(window_pos.x, window_pos.y, WINDOW_WIDTH, WINDOW_HEIGHT));
	} else {
		sf::Vector2i v(pos.x,pos.y);
		sf::Vector2f window_pos = game_p->window.mapPixelToCoords(v);
		sprite.setPosition(window_pos);
	}
	game_p->window.draw(sprite);
}
