#include "../include/tile.hpp"

tile_t::tile_t(std::string img_path, float x, float y ){
    !init(img_path);
        // return;
    // }
    pos = sf::Vector2f(x,y);
    s.setPosition(pos);
    // this->img_path = img_path;

};

int tile_t::init(std::string img_path){

    if(!t.loadFromFile(img_path)){return EXIT_FAILURE;};
    t.setSmooth(true);
    s.setTexture(t);
    s.setTextureRect(sf::IntRect(0,0,50,50));
    return 1;
}