#ifndef TILE_H
#define TILE_H
#include "../include/const.hpp"
#include <string.h>

class tile_t{
    sf::Vector2f pos;
    sf::Texture t;
    public:
        sf::Sprite s; 
    std::string img_path;
    tile_t(std::string img_path, float x, float y);
    int init(std::string img_path);
};


#endif
