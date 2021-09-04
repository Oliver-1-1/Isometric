#include <SFML/Graphics.hpp>
#include "settings.h"
#include "tile_map.h"
#include <iostream>
#include "window.h"
#include "player.h"
// Globals becuase i want them to be reached in every file so i dont have to pass varibales all the time
// I wish i can find a better way but i dont know how.
Settings settings;
window display;

int main()
{
   //TODO
    //Not render all 200 x 200 sprites since a lot of them is out of view
    //Move the camera with mouse
    tile_map tile_map;
    player player;
    tile_map.populate_tile_map();
    while (display.display.isOpen())
    {

        sf::Event event;
        while (display.display.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                display.display.close();
        }
        
        display.display.clear();
        tile_map.draw_tile_map();
        player.update();

        auto mousePos = display.display.mapPixelToCoords(sf::Mouse::getPosition(display.display));
        auto grid_pos = tile_map.get_tile_coordinates(tile_map.iso_to_2d(mousePos));
        tile_map.get_tile(grid_pos);

        display.display.display();
        
    }

    return 0;
}