#include "world.h"
world::world()
{
	texture->loadFromFile("terrain_0.png");
	chunks.resize(6);
    world_size = 6;

    initialize_world();
}

void world::render_world()
{
    for (const auto i : std::views::iota(0, world_size))
    {
        for (const auto j : std::views::iota(0, world_size))
        {
            chunks[i][j].draw_tile_map();
        }
    }
}

void world::render_chunk_outlines()
{
    for (const auto i : std::views::iota(0, world_size))
    {
        for (const auto j : std::views::iota(0, world_size))
        {
            for (const auto c : std::views::iota(0, 4))
            {
                display.display.draw(chunks[i][j].corner_positions[c]);    
            }

        }
    }
}

void world::detarmain_chunks()
{
    sf::FloatRect view(sf::Vector2f(display.view_port.getCenter().x - settings.resolution_x / 2, display.view_port.getCenter().y - settings.resolution_y / 2),
        sf::Vector2f(settings.resolution_x, settings.resolution_y)); // view area

    for (auto i : std::views::iota(0, (int)chunks.size()))
    {
        for (auto j : std::views::iota(0, 4)) // 4 corners
        {
            // x +
            if (view.contains(chunks[chunks.size() - 1][i].corner_positions[j].getPosition()))
            {
                auto pos = chunks[chunks.size() - 1][0].chunk_pos;
                chunks.erase(chunks.begin());
                chunks.resize(6);

                for (auto x : std::views::iota(0, (int)chunks.size()))
                {
                    chunks[chunks.size() - 1].emplace_back(chunk(sf::Vector2i(pos.x + 1, pos.y + x), texture));
                }
            }
            //x -
            if (view.contains(chunks[0][i].corner_positions[j].getPosition()))
            {
                auto pos = chunks[0][0].chunk_pos;

                for (auto x : std::views::iota(0, (int)chunks.size()))
                    chunks[chunks.size() - 1][x] = (chunk(sf::Vector2i(pos.x - 1, pos.y + x), texture));

                std::rotate(chunks.rbegin(), chunks.rbegin() + 1, chunks.rend());
            }

            // + y
            if (view.contains(chunks[i][chunks.size() - 1].corner_positions[j].getPosition()))
            {
                auto pos = chunks[0][chunks.size() - 1].chunk_pos;

                for (auto x : std::views::iota(0, (int)chunks.size()))
                {
                    chunks[x].erase(chunks[x].begin());
                    chunks[x].emplace_back(chunk(sf::Vector2i(pos.x + x, pos.y + 1), texture));
                }
            }
            // - y
            if (view.contains(chunks[i][0].corner_positions[j].getPosition()))
            {
                auto pos = chunks[0][0].chunk_pos;
                for(auto j : std::views::iota(0, (int)chunks.size()))
                    std::rotate(chunks[j].rbegin(), chunks[j].rbegin() + 1, chunks[j].rend());

                for (auto x : std::views::iota(0, (int)chunks.size()))
                {
                    chunks[x][0] = (chunk(sf::Vector2i(pos.x + x, pos.y - 1), texture));
                }

            }

        }

    }
}

void world::initialize_world()
{
    for (const auto i : std::views::iota(-world_size / 2, world_size / 2))
    {
        for (const auto j : std::views::iota(-world_size / 2, world_size / 2))
        {
            chunks[i + world_size / 2].emplace_back(sf::Vector2i(i, j), texture); // create chunks vector
        }
    }
}
