#ifndef DEF_RENDER_MANAGER_HPP
#define DEF_RENDER_MANAGER_HPP

#include <SDL_render.h>
#include <memory>
#include <string>

struct Render_Manager {

    public:

    Render_Manager() = delete;
    Render_Manager(std::uint16_t, std::uint16_t, const std::string& = "unamed");

    Render_Manager(const Render_Manager&) = default;
    Render_Manager(Render_Manager&&) noexcept = default;

    ~Render_Manager() = default;

    std::uint16_t GetWidth() const noexcept;
    std::uint16_t GetHeight() const noexcept;

    const std::string& GetName() const noexcept;

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>& GetWindowPtr() noexcept;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>& GetRendererPtr() noexcept;

    Render_Manager& operator=(const Render_Manager&) = default;
    Render_Manager& operator=(Render_Manager&&) noexcept = default;

    private:

    std::uint16_t width, height;
    std::string name;

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer{SDL_CreateRenderer(window.get(), 0, SDL_RendererFlags::SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer};

};

#endif // DEF_RENDER_MANAGER_HPP