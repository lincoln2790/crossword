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
    pos = sf::Vector2i(x,y);
}


void animation_t::draw_sprite(int sprite_index){
	sf::Vector2i v(pos.x *game_p->window_scale,pos.y*game_p->window_scale);
	sf::Vector2f window_pos = game_p->window.mapPixelToCoords(v);
	sprite.setPosition(window_pos);
	game_p->window.draw(sprite);
}

inf_animation_t::inf_animation_t(std::string texture_path, int w, int h,int x, int y, game_t *game_p) :
	animation_t(texture_path, w, h, x, y, game_p)
{
	texture.setRepeated(true);

}

void inf_animation_t::draw_sprite(){
	sf::Vector2i pixel_pos(0,0);
	sf::Vector2f window_pos = game_p->window.mapPixelToCoords(pixel_pos);
	sprite.setPosition(window_pos);
	sprite.setTextureRect(sf::IntRect(window_pos.x, window_pos.y, DEFAULT_WINDOW_DIM, DEFAULT_WINDOW_DIM));
	game_p->window.draw(sprite);
}
