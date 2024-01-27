#include "../include/animation.hpp"
#include "../include/game.hpp"

animation_t::animation_t(std::string texture_path, int w, int h, int x, int y, game_t *game_p):
	sprite_width(w),
	sprite_height(h),
	game_p(game_p)
{
	texture.loadFromFile(texture_path);
	texture.setSmooth(true);
	sprite.setTexture(texture);
	//sprite.setTextureRect(sf::IntRect(x, y, sprite_width, sprite_height));
    pos = sf::Vector2i(x,y);
}


void animation_t::draw_sprite(int sprite_index){
	sf::Vector2i v(pos.x,pos.y);
	sf::Vector2f window_pos = game_p->window.mapPixelToCoords(v);
	sprite.setPosition(window_pos);
	//sprite.setTextureRect(sf::IntRect(window_pos.x, window_pos.y, sprite_width, sprite_height));
	game_p->window.draw(sprite);
}
