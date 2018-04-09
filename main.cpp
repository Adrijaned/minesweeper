#include <SFML/Graphics.hpp>
#include "const.hpp"
#include "Tile.hpp"

int main() {
    srand(time(NULL));
    tex1.loadFromFile("res/1.png");
    tex2.loadFromFile("res/2.png");
    tex3.loadFromFile("res/3.png");
    tex4.loadFromFile("res/4.png");
    tex5.loadFromFile("res/5.png");
    tex6.loadFromFile("res/6.png");
    tex7.loadFromFile("res/7.png");
    tex8.loadFromFile("res/8.png");
    texCovered.loadFromFile("res/covered.png");
    texEmpty.loadFromFile("res/empty.png");
    texFlag.loadFromFile("res/flag.png");
    texMine.loadFromFile("res/mine.png");
    sf::RenderWindow window(sf::VideoMode(width*tileSize, height*tileSize), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);

    Tile tiles[width*height];
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            tiles[i*height+j].setPosition(i, j);
            Tile *up, *down, *left, *right;
            if (j == 0) up = nullptr;
            else up = &tiles[(j-1)+i*height];
            if (j == height - 1) down = nullptr;
            else down = &tiles[(j+1)+i*height];
            if (i==0) left = nullptr;
            else left = &tiles[(i-1)*height+j];
            if (i==width-1) right = nullptr;
            else right = &tiles[(i+1)*height+j];
            tiles[i*height+j].setNeighbors(up, down,left, right);
        }
    }
    for (int i = 0; i < mineAmount; ++i) {
        int num = rand() % (width * height);
        if (tiles[num].isMine) i--;
        else tiles[num].isMine = true;
    }
    for (Tile &tile : tiles) {
        tile.update();
    }

    while (run && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                Tile *tile = &tiles[(event.mouseButton.x/tileSize)*height+event.mouseButton.y/tileSize];
                if (event.mouseButton.button == sf::Mouse::Left) {
                    tile->reveal();
                }
                if (event.mouseButton.button==sf::Mouse::Right) {
                    tile->flag();
                }
                bool temp = true;
                for (auto &&tile : tiles) {
                    temp = temp && ((tile.isFlagged && tile.isMine) || !(tile.isFlagged || tile.isMine));
                }
                if (temp) {
                    run = false;
                }
            }
        }
        window.clear(sf::Color::Green);
        for (auto &&tile : tiles) {
            window.draw(tile);
        }
        window.display();
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::MouseButtonPressed) {
                window.close();
            }
        }
    }
    return 0;
}