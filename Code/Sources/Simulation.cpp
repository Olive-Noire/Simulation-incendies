#include "../Headers/Simulation.hpp"

#include <SDL.h>
#include <iostream>

Simulation::Simulation(Config &&c) noexcept : Simulation{c} {}

Simulation::Simulation(const Config &c) : run{false}, cells{static_cast<std::size_t>(c.SizeX*c.SizeY), Cell::TREE}, config{c}, renderManager{0, 0} {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);

    renderManager = Render_Manager{static_cast<std::uint16_t>(config.SizeY*config.cellSize), static_cast<std::uint16_t>(config.SizeX*config.cellSize), "Incendie"};

    cells[rand()%cells.size()] = Cell::FIRE;
    run = true;

}

void Simulation::Render() {

    SDL_RenderClear(renderManager.GetRendererPtr().get());

    for (std::size_t i{0}; i < cells.size(); i++) {

        switch (cells[i]) {

            case Cell::TREE:
            SDL_SetRenderDrawColor(renderManager.GetRendererPtr().get(), std::uint8_t{0}, std::uint8_t{255}, std::uint8_t{0}, std::uint8_t{255});
            break;

            case Cell::FIRE:
            SDL_SetRenderDrawColor(renderManager.GetRendererPtr().get(), std::uint8_t{255}, std::uint8_t{0}, std::uint8_t{0}, std::uint8_t{255});
            break;

            case Cell::DEAD:
            SDL_SetRenderDrawColor(renderManager.GetRendererPtr().get(), std::uint8_t{0}, std::uint8_t{0}, std::uint8_t{0}, std::uint8_t{255});
            break;

            default:
            break;

        }

        const std::uint32_t x{i/config.SizeX}, y{i%config.SizeX};

        if (config.cellSize == 1) {

            SDL_RenderDrawPoint(renderManager.GetRendererPtr().get(), x, y);

        } else {

            const SDL_Rect rect{x*config.cellSize, y*config.cellSize, config.cellSize, config.cellSize};
            SDL_RenderFillRect(renderManager.GetRendererPtr().get(), &rect);

        }

    }

    SDL_SetRenderDrawColor(renderManager.GetRendererPtr().get(), std::uint8_t{0}, std::uint8_t{0}, std::uint8_t{0}, std::uint8_t{0});
    SDL_RenderPresent(renderManager.GetRendererPtr().get());

}

void Simulation::Update() {

    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_EventType::SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
        
        run = false;
        return;

    }

    if (event.type == SDL_EventType::SDL_MOUSEBUTTONDOWN &&
        event.button.button == SDL_BUTTON_LEFT &&
        cells[event.button.x/config.cellSize*config.SizeX+event.button.y/config.cellSize] == Cell::TREE) {

        cells[event.button.x/config.cellSize*config.SizeX+event.button.y/config.cellSize] = Cell::FIRE;

    }

    for (std::size_t i{0}; i < cells.size(); i++) {

        if (cells[i] == Cell::FIRE) {

            const std::uint32_t x{i/config.SizeX}, y{i%config.SizeX};

            auto LightUpCase = [this](const std::uint32_t posX, const std::uint32_t posY) -> void {

                if (cells[posX*config.SizeX+posY] == Cell::TREE && rand()%100 < config.probability) {

                    cells[posX*config.SizeX+posY] = Cell::FIRE;

                }

            };

            if (x > 0) LightUpCase(x-1, y); else if (config.borders) LightUpCase(config.SizeX-1, y);
            if (x < static_cast<std::uint16_t>(config.SizeX-1)) LightUpCase(x+1, y); else if (config.borders) LightUpCase(0, y);

            if (y > 0) LightUpCase(x, y-1); else if (config.borders) LightUpCase(x, config.SizeY-1);
            if (y < static_cast<std::uint16_t>(config.SizeY-1)) LightUpCase(x, y+1); else if (config.borders) LightUpCase(x, 0);

            /*
            if (x > 0 && y > 0) {}
            if (x > Config::SizeX-1 && y > 0) {}
            if (x > 0 && y > Config::SizeY-1) {}
            if (x > Config::SizeX-1 && y > Config::SizeY-1) {}
            */

            cells[i] = Cell::DEAD;

        }

    }

}