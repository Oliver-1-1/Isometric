#include <SFML/Graphics.hpp>
#include "settings.h"
#include "chunk.h"
#include <iostream>
#include <ranges>
#include <string>
#include "window.h"
#include "player.h"
#include "world.h"
Settings settings;
window display;

int main()
{
	player player;
    world world1;
    while (display.display.isOpen())
    {
        sf::Event event{};
        while (display.display.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                display.display.close();
        }
        display.display.clear();

        world1.detarmain_chunks();
        world1.render_world();
        world1.render_chunk_outlines();

        player.move_cam();
        display.display.display();


    }
    
    return 0;
}

