#include "../Headers/RenderManager.hpp"

Render_Manager::Render_Manager(std::uint16_t w, std::uint16_t h, const std::string& n) :
    width{w},
    height{h},
    name{n},
    window{SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, SDL_WindowFlags::SDL_WINDOW_SHOWN), SDL_DestroyWindow},
    renderer{SDL_CreateRenderer(window.get(), 0, SDL_RendererFlags::SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer}
{
    
    if (width < 120) width = 120;
    
}

std::uint16_t Render_Manager::GetWidth() const noexcept { return width; }
std::uint16_t Render_Manager::GetHeight() const noexcept { return height; }

const std::string& Render_Manager::GetName() const noexcept { return name; }

std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>& Render_Manager::GetWindowPtr() noexcept { return window; }
std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>& Render_Manager::GetRendererPtr() noexcept { return renderer; }