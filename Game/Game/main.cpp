#include <SFML/Graphics.hpp>
#include "settings.h"
#include "tileMap.h"
#include <iostream>
#include "window.h"
#include "player.h"
// Globals becuase i want them to be reached in every file so i dont have to pass varibales all the time
// I wish i can find a better way but i dont know how.
Settings settings;
Window window;

int main()
{
        

   //TODO
    //Not render all 200 x 200 sprites since a lot of them is out of view
    //Move the camera with mouse
    TileMap tilemap;
    Player player;
    tilemap.populateTileMap();
    tilemap.removeTile(sf::Vector2i(10, 10));
    while (window.window.isOpen())
    {
        sf::Event event;
        while (window.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.window.close();
        }
        
        window.window.clear();
        
        tilemap.drawTileMap();
        player.update();
        window.window.display();
    }

    return 0;
}