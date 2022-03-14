#pragma once
#include <SDL2/SDL.h>
#include <View.h>

namespace SDL {

using Rect = SDL_Rect;

inline void init(uint32_t flags = SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER)
{
    if (SDL_Init(flags)) {
        fprintf(stderr, "Could not launch SDL instance: %s\n", SDL_GetError());
        abort();
    }
}
void quit() asm("SDL_Quit");

class [[nodiscard]] Instance {
public:
    Instance()
    {
        init();
    }
    ~Instance()
    {
        quit();
    }
};

SDL_Window* create_window(char const* name, int x, int y, int w, int h, uint32_t flags = 0) asm("SDL_CreateWindow");
void destroy_window(SDL_Window* window) asm("SDL_DestroyWindow");
uint32_t window_id(SDL_Window* window) asm("SDL_GetWindowID");

SDL_Renderer* create_renderer(SDL_Window* window, int index, uint32_t flags = 0) asm("SDL_CreateRenderer");
void destroy_renderer(SDL_Renderer* renderer) asm("SDL_DestroyRenderer");
int set_render_draw_color(SDL_Renderer*, uint8_t r, uint8_t g, uint8_t b, uint8_t a) asm("SDL_SetRenderDrawColor");
int render_clear(SDL_Renderer* renderer) asm("SDL_RenderClear");
int render_present(SDL_Renderer*) asm("SDL_RenderPresent");

int poll_event(SDL_Event* event) asm("SDL_PollEvent");

uint32_t ticks() asm("SDL_GetTicks");

struct MousePoint {
    int x;
    int y;
};

inline MousePoint mouse_state()
{
    auto point = MousePoint {};
    SDL_GetMouseState(&point.x, &point.y);
    return point;
}

class Surface {
public:
    Surface(SDL_Surface* surface)
        : m_surface(surface)
    {
    }

    static Surface create(int width, int height, int depth)
    {
        // FIXME: masks are incorrect for big endian machines
        auto surface = SDL_CreateRGBSurface(0, width, height, depth,
                                    0xFF, 0x00FF, 0x0000FF, 0x000000FF);
        if (!surface) {
            fprintf(stderr, "Could not create surface: %s\n", SDL_GetError());
            abort();
        }
        return surface;
    }
    void destroy()
    {
        if (m_surface)
            SDL_FreeSurface(m_surface);
    }

    SDL_Surface* sdl_impl() { return m_surface; }

    SDL_PixelFormat const* format() const { return m_surface->format; }
    int width() const { return m_surface->w; }
    int height() const { return m_surface->h; }
    int size() const { return width()*height(); }

    int pitch() const { return m_surface->pitch; }
    void* pixels() { return m_surface->pixels; }
    void* userdata() { return m_surface->userdata; }

    View<uint32_t, int> frame_buffer() {
        return { pixels(), size() };
    }

    void lock() { SDL_LockSurface(m_surface); }
    void unlock() { SDL_UnlockSurface(m_surface); };

    Rect clip_rect() const { return m_surface->clip_rect; }
    SDL_BlitMap* map() { return m_surface->map; }

private:
    SDL_Surface* m_surface { nullptr };
};

class Window {
public:
    static Window create(char const* name,
           int width, int height,
           uint32_t flags = 0,
           int x = SDL_WINDOWPOS_CENTERED,
           int y = SDL_WINDOWPOS_CENTERED
           )
    {
        auto window = create_window(name, x, y, width, height, flags);
        if (!window) {
            fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
            abort();
        }
        SDL_HideWindow(window);
        return window;
    }

    void destroy()
    {
        if (m_window)
            destroy_window(m_window);
    }

    void show(bool yes = true)
    {
        if (yes) {
            SDL_ShowWindow(m_window);
        } else {
            SDL_HideWindow(m_window);
        }
    }


    SDL_Window* sdl_impl() { return m_window; }
    uint32_t id() const { return window_id(m_window); }
    Surface surface() { return SDL_GetWindowSurface(m_window); }

private:
    Window(SDL_Window* window)
        : m_window(window)
    {
    }

    SDL_Window* m_window { nullptr };
};

using Point = SDL_Point;

class Renderer;
class Texture {
public:

    template <typename T = Renderer>
        requires std::is_same_v<Renderer, T>
    static constexpr Texture create(T renderer, int width, int height,
            SDL_PixelFormatEnum format = SDL_PIXELFORMAT_ARGB8888,
            SDL_TextureAccess access = SDL_TEXTUREACCESS_STREAMING 
            )
    {
        auto texture = SDL_CreateTexture(renderer.sdl_impl(),
                                         format, access, width, height);
        if (!texture) {
            fprintf(stderr, "Could not create texture: %s\n", SDL_GetError());
            abort();
        }
        return texture;
    }
    
    constexpr void destroy()
    {
        if (m_texture)
            SDL_DestroyTexture(m_texture);
    }

    SDL_Texture* sdl_impl() { return m_texture; }

    int update(void const* pixels, int pitch, Rect* rect = nullptr)
    {
        return SDL_UpdateTexture(m_texture, rect, pixels, pitch);
    }

private:
    constexpr Texture(SDL_Texture* texture)
        : m_texture(texture)
    {
    }

    SDL_Texture* m_texture { nullptr };
};

class Renderer {
public:
    static Renderer create(Window window, int index = -1,
                           uint32_t flags = SDL_RENDERER_ACCELERATED)
    {
        auto renderer = create_renderer(window.sdl_impl(), index, flags);
        if (!renderer) {
            fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
            abort();
        }
        return renderer;
    }
    void destroy() { destroy_renderer(m_renderer); }

    SDL_Renderer* sdl_impl() { return m_renderer; }

    int set_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
    {
        return set_render_draw_color(m_renderer, r, g, b, a);
    }

    int draw_points(View<Point> points)
    {
        return SDL_RenderDrawPoints(m_renderer, points.data, points.size);
    }

    int clear() { return render_clear(m_renderer); }
    int present() { return render_present(m_renderer); }

    int copy(Texture texture)
    {
        return SDL_RenderCopy(m_renderer, texture.sdl_impl(), nullptr, nullptr);
    }

    int copy(Texture texture, Rect srcrect)
    {
        return SDL_RenderCopy(m_renderer, texture.sdl_impl(), &srcrect, nullptr);
    }

    int copy(Texture texture, Rect srcrect, Rect dstrect)
    {
        return SDL_RenderCopy(m_renderer, texture.sdl_impl(), &srcrect, &dstrect);
    }

private:
    Renderer(SDL_Renderer* renderer)
        : m_renderer(renderer)
    {
    }

    SDL_Renderer* m_renderer { nullptr };
};


}

