#ifndef TILE_H
#define TILE_H

class tile_t{
    sf::Vector2f pos;
    public:
        sf::Sprite sprite;
    tile_t(sf::Sprite s, float x, float y);

};


#endif
