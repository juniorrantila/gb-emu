#pragma once
#include <functional>
#include <GUI/SDLWrapper.h>
#include <map>
#include <optional>
#include <BuildInfo.h>

namespace GUI {

class EventHandler {
public:
    EventHandler(SDL::Window const& window)
        : m_window(window)
    {
    }
    void handle_events() const
    {
        SDL_Event event;
        while (SDL::poll_event(&event)) {
            if constexpr (is_debug_build) {
                if (m_on_quit.has_value() &&
                    event.type == SDL_KEYDOWN &&
                    event.key.keysym.sym == SDLK_ESCAPE)
                        m_on_quit.value()();
            }
            if (event.type == SDL_QUIT && m_on_quit.has_value()) {
                m_on_quit.value()();
            } else if (event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == m_window.id() &&
                m_on_quit.has_value())
            {
                m_on_quit.value()();
            } else if (event.type == SDL_KEYDOWN) {
                if (m_on_key_down.contains(event.key.keysym.sym))
                    m_on_key_down.at(event.key.keysym.sym)();
            } else if (event.type == SDL_KEYUP) {
                if (m_on_key_up.contains(event.key.keysym.sym))
                    m_on_key_up.at(event.key.keysym.sym)();
            }
        }
    }

    void on_key_down(SDL_Keycode keycode, std::function<void()> lambda)
    {
        m_on_key_down[keycode] = lambda;
    }
    void on_key_up(SDL_Keycode keycode, std::function<void()> lambda)
    {
        m_on_key_up[keycode] = lambda;
    }

    void on_quit(std::function<void()> lambda)
    {
        m_on_quit = lambda;
    }
private:
    std::map<SDL_Keycode, std::function<void()>> m_on_key_down {};
    std::map<SDL_Keycode, std::function<void()>> m_on_key_up {};
    SDL::Window const& m_window;
    std::optional<std::function<void()>> m_on_quit;
};

}
