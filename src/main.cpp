#include <BuildInfo.h>
#include <Cli.h>
#include <CString.h>
#include <Defer.h>
#include <GB/Cpu.h>
#include <GB/Ppu.h>
#include <GB/Memory.h>
#include <GB/Hardware.h>
#include <GUI/Canvas.h>
#include <GUI/EventHandler.h>
#include <GUI/Font.h>
#include <GUI/SDLWrapper.h>
#include <GUI/Tile.h>
#include <stdio.h>
#include <Terminal.h>
#include <TestCode.h>
#include <TestScene.h>

#ifdef NDEBUG
#define BARE
#endif

#ifndef BARE
static constexpr const int g_scale_factor = 8;
static constexpr const int g_physical_width = GB::viewport_width*g_scale_factor;
static constexpr const int g_physical_height = GB::viewport_height*g_scale_factor;


void setup_gb_keys(GUI::EventHandler& event_handler,
                   GB::Memory& mmio);


static void update_renderer(SDL::Renderer& renderer,
                            SDL::Texture& texture,
                            Canvas& canvas,
                            uint8_t debug_scroll_x,
                            uint8_t debug_scroll_y,
                            uint8_t scroll_x,
                            uint8_t scroll_y,
                            bool debug_mode);

static auto instance = SDL::Instance();

#endif

int main(int argc, c_string argv[])
{
#ifdef BARE
    (void)argc;
    (void)argv;
#endif
#ifndef BARE
    auto cli = Cli();
    auto show_gui = true;
    cli.on_argument("--no-gui", [&show_gui] {
        show_gui = false;
    });
    cli.parse(argc, argv);

    auto window = SDL::Window::create("gb-emu",
                                      g_physical_width,
                                      g_physical_height);
    Defer destroy_window = [&window] { window.destroy(); };
    
    auto event_handler = GUI::EventHandler(window);

#endif
    bool should_quit = false;
#ifndef BARE
    event_handler.on_quit([&should_quit] {
        should_quit = true;
    });
    bool debug_mode = false;
    event_handler.on_key_down(SDLK_SPACE, [&debug_mode] {
        debug_mode = !debug_mode;
    });
#endif
    auto memory = GB::Memory(TestCode::code,
                             TestCode::code_size,
                             GB::LogInvalidAccess::Yes);
#ifndef BARE
    setup_gb_keys(event_handler, memory);
#endif

    auto cpu = GB::CPU(memory,
                       GB::PrintAssembly::Yes,
                       GB::LogRegisterEvents::Yes);

    // cpu.run(GB::PrintAssembly::Yes);
    // cpu.run();

#ifndef BARE
    auto renderer = SDL::Renderer::create(window);
    Defer destroy_renderer = [&renderer] {
        renderer.destroy();
    };

    auto ppu = GB::PPU(memory, std::move(renderer),
                       g_physical_width,
                       g_physical_height
                      );

    auto texture = SDL::Texture::create(renderer,
                                    GB::internal_width,
                                    GB::internal_height);
    Defer destroy_texture = [&texture] {
        texture.destroy();
    };

    static auto canvas = Canvas();
    canvas.clear();

    // auto scene = TestScene::basic();
    auto scene = TestScene::text();

    double scroll_x = 0;
    double scroll_y = 0;
    uint16_t debug_scroll_x = 0;
    uint16_t debug_scroll_y = 0;
    auto handle_inputs = [&] {
        if (memory.joypad().up) {
            scroll_y--;
            debug_scroll_y--;
        }
        if (memory.joypad().down) {
            scroll_y++;
            debug_scroll_y++;
        }
        if (memory.joypad().left) {
            scroll_x--;
            debug_scroll_x--;
        }
        if (memory.joypad().right) {
            scroll_x++;
            debug_scroll_x++;
        }

        if (scroll_x > GB::viewport_width)
            scroll_x = -(GB::internal_width - GB::viewport_width);
        if (scroll_x < -GB::viewport_width)
            scroll_x = GB::internal_width - GB::viewport_width;

        if (scroll_y > GB::viewport_height)
            scroll_y = -(GB::internal_height - GB::viewport_height);
        if (scroll_y < -GB::viewport_height)
            scroll_y = GB::internal_height - GB::viewport_height;
    };

    
    if (show_gui) {
        Terminal::hide_cursor();
        Terminal::clear();
        Terminal::move_cursor_home();
        window.show();
    }
    Defer show_cursor = [&show_gui] {
        if (show_gui)
            Terminal::hide_cursor(false);
    };
#endif
    while (!should_quit) {
#ifndef BARE
        event_handler.handle_events();
        handle_inputs();

        auto start_time = SDL::ticks();
        Defer delay_to_60fps = [&] {
            auto end_time = SDL::ticks();
            auto frame_time = end_time - start_time;
            SDL_Delay(uint8_t(1000/60 - frame_time));
        };
#endif

        if (cpu.pc >= memory.rom_size())
            break;

        for (auto h = 0; h<GB::viewport_height; h++) {
            // FIXME: Run, but disable access to OAM
            cpu.run_next_cycles(GB::oam_search_cycles);
            // FIXME: Run, but fix the whatever
            cpu.run_next_cycles(GB::pixel_transfer_cycles);
            cpu.run_next_cycles(GB::hblank_cycles);
        }
        cpu.run_next_cycles(GB::hblank_cycles);

#ifndef BARE
        canvas.clear();
        scene.draw_on(canvas);
        update_renderer(renderer, texture, canvas,
                        debug_scroll_x, debug_scroll_y,
                        scroll_x, scroll_y,
                        debug_mode);
        renderer.present();
#endif
    }

#ifndef BARE
    getchar();
#endif

    return 0;
}

#ifndef BARE
void setup_gb_keys(GUI::EventHandler& event_handler,
                   GB::Memory& mmio)
{
    event_handler.on_key_down(SDLK_w, [&mmio] {
        mmio.joypad().up = true;
    });
    event_handler.on_key_up(SDLK_w, [&mmio] {
        mmio.joypad().up = false;
    });
    
    event_handler.on_key_down(SDLK_a, [&mmio] {
        mmio.joypad().left = true;
    });
    event_handler.on_key_up(SDLK_a, [&mmio] {
        mmio.joypad().left = false;
    });
    
    event_handler.on_key_down(SDLK_s, [&mmio] {
        mmio.joypad().down = true;
    });
    event_handler.on_key_up(SDLK_s, [&mmio] {
        mmio.joypad().down = false;
    });

    event_handler.on_key_down(SDLK_d, [&mmio] {
        mmio.joypad().right = true;
    });
    event_handler.on_key_up(SDLK_d, [&mmio] {
        mmio.joypad().right = false;
    });
}

static void update_renderer(SDL::Renderer& renderer,
                            SDL::Texture& texture,
                            Canvas& canvas,
                            uint8_t debug_scroll_x,
                            uint8_t debug_scroll_y,
                            uint8_t scroll_x,
                            uint8_t scroll_y,
                            bool debug_mode)
{
    // FIXME: Clear screen correctly when switching between these
    if (debug_mode) {
        canvas.draw_viewport_outline(debug_scroll_x, debug_scroll_y);
        texture.update(canvas.pixels(), canvas.internal_width()*sizeof(uint32_t));
        renderer.copy(texture, { 0, 0, g_physical_width, g_physical_height });
    } else {
        texture.update(canvas.pixels(), canvas.internal_width()*sizeof(uint32_t));

        constexpr const auto rects_size = 9;
        auto x_off = scroll_x*g_scale_factor;
        auto y_off = scroll_y*g_scale_factor;

        double x_pos = double(g_physical_width) * (double(GB::internal_width) / double(GB::viewport_width));
        double y_pos = double(g_physical_height) * (double(GB::internal_height) / double(GB::viewport_height));

        SDL::Rect rects[rects_size] = {
            { int(-1.0*x_pos+x_off), int(-1*y_pos+y_off), g_physical_width, g_physical_height },
            { int( 0.0*x_pos+x_off), int(-1*y_pos+y_off), g_physical_width, g_physical_height },
            { int( 1.0*x_pos+x_off), int(-1*y_pos+y_off), g_physical_width, g_physical_height },

            { int(-1.0*x_pos+x_off), int( 0*y_pos+y_off), g_physical_width, g_physical_height },
            { int( 0.0*x_pos+x_off), int( 0*y_pos+y_off), g_physical_width, g_physical_height },
            { int( 1.0*x_pos+x_off), int( 0*y_pos+y_off), g_physical_width, g_physical_height },

            { int(-1.0*x_pos+x_off), int( 1*y_pos+y_off), g_physical_width, g_physical_height },
            { int( 0.0*x_pos+x_off), int( 1*y_pos+y_off), g_physical_width, g_physical_height },
            { int( 1.0*x_pos+x_off), int( 1*y_pos+y_off), g_physical_width, g_physical_height },
        };

        for (auto i = 0; i<rects_size; i++)
            renderer.copy(texture, { 0, 0, canvas.viewport_width(), canvas.viewport_height() }, rects[i]);
    }
}
#endif
