//
// Created by adrijaneddebian on 4/9/18.
//

#include "Tile.hpp"
#include "const.hpp"

Tile::Tile() = default;

void Tile::setPosition(int x, int y) {
    sprite.setPosition(x * tileSize, y * tileSize);
}

void Tile::update() {
    if (isMine) {
        neighborMines = -1;
        neighborFlagged = -1;
    } else {
        neighborMines = 0;
        neighborFlagged = 0;
        if (up != nullptr) {
            if (up->isMine) {
                neighborMines++;
            }
            if (up->isFlagged) {
                neighborFlagged++;
            }
        }
        if (down != nullptr) {
            if (down->isMine) {
                neighborMines++;
            }
            if (down->isFlagged) {
                neighborFlagged++;
            }
        }
        if (left != nullptr) {
            if (left->isMine) {
                neighborMines++;
            }
            if (left->isFlagged) {
                neighborFlagged++;
            }
            if (up != nullptr) {
                if (left->up->isMine) {
                    neighborMines++;
                }
                if (left->up->isFlagged) {
                    neighborFlagged++;
                }
            }
            if (down != nullptr) {
                if (left->down->isMine) {
                    neighborMines++;
                }
                if (left->down->isFlagged) {
                    neighborFlagged++;
                }
            }
        }
        if (right != nullptr) {
            if (right->isMine) {
                neighborMines++;
            }
            if (right->isFlagged) {
                neighborFlagged++;
            }
            if (down != nullptr){
                if (right->down->isMine) {
                    neighborMines++;
                }
                if (right->down->isFlagged) {
                    neighborFlagged++;
                }
            }
            if (up != nullptr) {
                if (right->up->isMine) {
                    neighborMines++;
                }
                if (right->up->isFlagged) {
                    neighborFlagged++;
                }
            }
        }
    }

    if (!isRevealed) {
        if (isFlagged) {
            sprite.
                    setTexture(texFlag);
        } else {
            sprite.
                    setTexture(texCovered);
        }
    } else {
        switch (neighborMines) {
            case -1:
                sprite.
                        setTexture(texMine);
                break;
            case 0:
                sprite.
                        setTexture(texEmpty);
                break;
            case 1:
                sprite.
                        setTexture(tex1);
                break;
            case 2:
                sprite.
                        setTexture(tex2);
                break;
            case 3:
                sprite.
                        setTexture(tex3);
                break;
            case 4:
                sprite.
                        setTexture(tex4);
                break;
            case 5:
                sprite.
                        setTexture(tex5);
                break;
            case 6:
                sprite.
                        setTexture(tex6);
                break;
            case 7:
                sprite.
                        setTexture(tex7);
                break;
            case 8:
                sprite.
                        setTexture(tex8);
                break;
            default:
                break;
        }
    }
}

void Tile::setNeighbors(Tile *up, Tile *down, Tile *left, Tile *right) {
    this->up = up;
    this->down = down;
    this->left = left;
    this->right = right;
}

void Tile::flag() {
    if (!isRevealed) {
        isFlagged = !isFlagged;
        update();
        return;
    }
    update();
    if (neighborMines == neighborFlagged) {
        if (up != nullptr) {
            up->reveal();
        }
        if (down!= nullptr) {
            down->reveal();
        }
        if (left!= nullptr) {
            left->reveal();
            if (up!= nullptr) {
                left->up->reveal();
            }
            if (down!= nullptr) {
                left->down->reveal();
            }
        }
        if (right!= nullptr) {
            right->reveal();
            if (up!= nullptr) {
                right->up->reveal();
            }
            if (down!= nullptr) {
                right->down->reveal();
            }
        }
    }
}

int8_t Tile::reveal() {
    if (isRevealed || isFlagged) return -1;
    isRevealed = true;
    update();
    if (isMine) {
        run = false;
        return 1;
    }
    if (neighborMines == 0) {
        flag();
    }
    return 0;
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite);
}
