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

    tile_map tile_map;
  
    player player;
    tile_map.populate_tile_map(0);
    //tile_map.remove_tile(sf::Vector2i(0, 0));

    while (display.display.isOpen())
    {
        tile_map.remove_tile(sf::Vector2i(0, 0));
        tile_map.add_tile(sf::Vector2i(0, 0), 0);
        sf::Event event{};
        while (display.display.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                display.display.close();
        }
        display.display.clear();
        tile_map.draw_tile_map();

        player.update();
        //auto grid_pos = tile_map.get_tile_coordinates(tile_map::iso_to_2d(display.get_mouse_position()));

       //tile_map.add_tile(sf::Vector2i(grid_pos.x, grid_pos.y), 2);
        //tile_map.get_tile(grid_pos);
        display.display.display();

  

    }

    return 0;
}