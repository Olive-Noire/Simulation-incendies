#include "../Headers/Simulation.hpp"

#include <SDL_timer.h>
#include <iostream>
#include <ctime>

#include "../Headers/Input.hpp"

int main(int argc, char* argv[]) {

    std::srand(std::time(0));

    if (argc > 1) {
        
        for (int i{1}; i < argc; i++) std::cout << i << " : " << argv[i];

    }

    Config config;

    std::cout << "Nombre de lignes :\n";
    config.SizeX = SecureInput<std::uint16_t>();

    std::cout << "Nombre de colonnes :\n";
    config.SizeY = SecureInput<std::uint16_t>();

    std::cout << "Taille des cases (en pixel) :\n";
    config.cellSize = SecureInput<std::uint16_t>();

    std::cout << "Probabilite d'enflammer un arbre (en %) :\n";;
    config.probability = SecureInput<std::uint16_t>();

    std::cout << "Sauter les bords ? (1 : oui, 0 : non) :\n\n";;
    config.borders = SecureInput<bool>();

    Simulation incendie{config};

    constexpr std::uint32_t frameDelay{1000/60};

    std::uint32_t frameStart{0};
    std::uint32_t frameTime{0};

    while (incendie.run) {

        frameStart = SDL_GetTicks();

        incendie.Update();
        incendie.Render();

        frameTime = SDL_GetTicks()-frameStart;
        if (frameDelay > frameTime) SDL_Delay(frameDelay-frameTime);

    }

    return 0;

}