#ifndef DEF_SIMULATION_HPP
#define DEF_SIMULATION_HPP

#include "./RenderManager.hpp"

#include <vector>

enum class Cell{TREE, FIRE, DEAD};

struct Config {

    std::uint16_t cellSize{5};
    std::uint16_t SizeX{100}, SizeY{100};

    std::uint16_t probability{40};

    bool borders{false};
    // bool curves{false}; coming soon...

};

class Simulation {

    public:

    Simulation() = delete;
    Simulation(const Config&);
    Simulation(Config&&) noexcept;

    Simulation(const Simulation&) = default;
    Simulation(Simulation&&) noexcept = default;

    ~Simulation() = default;

    void Render();
    void Update();

    bool run;

    Simulation& operator=(const Simulation&) = default;
    Simulation& operator=(Simulation&&) noexcept = default;

    private:

    std::vector<Cell> cells;
    Config config;

    Render_Manager renderManager;

};

#endif // DEF_SIMULATION_HPP