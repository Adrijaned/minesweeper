//
// Created by adrijaneddebian on 4/9/18.
//

#ifndef MINESWEEPER_TILE_HPP
#define MINESWEEPER_TILE_HPP


#include <SFML/Graphics.hpp>

class Tile : public sf::Drawable {
    bool isRevealed = false;
    sf::Sprite sprite;
    int neighborMines = 0, neighborFlagged = 0;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    Tile *up, *down, *left, *right;
    bool isFlagged = false, isMine = false;

    Tile();

    void setPosition(int x, int y);

    void update();

    void setNeighbors(Tile *up, Tile *down, Tile *left, Tile *right);
    void flag();
    int8_t reveal();
};


#endif //MINESWEEPER_TILE_HPP
