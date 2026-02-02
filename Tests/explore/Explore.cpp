export module Eqx.TPL.Tests.Explore;

import Eqx.TPL.Tests.Explore.Glad;
import Eqx.TPL.Tests.Explore.Stb_Image;
import Eqx.TPL.Tests.Explore.Glm;
import Eqx.TPL.Tests.Explore.Glm_Image;
import Eqx.TPL.Tests.Explore.Freetype;
import Eqx.TPL.Tests.Explore.Glm_Freetype;
import Eqx.TPL.Tests.Explore.Miniaudio;

import <Eqx/std.hpp>;

import Eqx.TPL.Wrapper.glfw;

import Eqx.TPL.Tests.Lib;

using namespace std::literals;

export namespace eqx::tpl::tests
{
    class Explore final
    {
    public:
        Explore() = delete;
        Explore(const Explore&) = delete;
        Explore(Explore&&) = delete;
        Explore& operator= (const Explore&) = delete;
        Explore& operator= (Explore&&) = delete;
        ~Explore() = delete;

        static inline void run() noexcept
        {
            eqx::tpl::wrapper::glfw::init();

            auto name = std::array<char, std::size_t{ 128 }>{};
            auto frame_timer = eqx::tpl::tests::lib::Frame_Timer{};
            auto window = std::make_optional(
                eqx::tpl::wrapper::glfw::Window{ 2560, 1440, "" });

            window->make_context_current();
            window->load_glad();
            window->swap_interval(1);

            const auto [width, height] = window->get_window_size();

            auto glad = std::make_optional<
                eqx::tpl::tests::explore::Glad>();
            auto stb_image = std::make_optional<
                eqx::tpl::tests::explore::Stb_Image>();
            auto glm = std::make_optional<
                eqx::tpl::tests::explore::Glm>(width, height);
            auto glm_image = std::make_optional<
                eqx::tpl::tests::explore::Glm_Image>(width, height);
            auto freetype = std::make_optional<
                eqx::tpl::tests::explore::Freetype>();
            auto glm_freetype = std::make_optional<
                eqx::tpl::tests::explore::Glm_Freetype>(width, height);
            auto miniaudio = std::make_optional<
                eqx::tpl::tests::explore::Miniaudio>();

            auto c = 'Q';
            auto index = 0;

            eqx::tpl::wrapper::glfw::print_info();

            frame_timer.start();

            while (window->window_should_close() == false)
            {
                window->clear(0.2f, 0.3f, 0.3f);

                const auto [x, y] = window->get_cursor_pos();

                std::format_to(std::ranges::begin(name),
                    "Eqx/TPL --- "sv
                    "Explore --- "sv
                    "Location: ({}, {}) --- "sv
                    "Frames: {} --- "sv
                    "FPS: {} |\0"sv, x, y, frame_timer.get_frames(),
                    frame_timer.get_fps());

                window->set_window_title(std::ranges::cdata(name));

                if (window->key_down(
                    eqx::tpl::wrapper::glfw::Key::Escape))
                {
                    window->set_window_should_close();
                }

                for (int i = 48; i <= 57; ++i)
                {
                    if (window->key_down(
                        static_cast<eqx::tpl::wrapper::glfw::Key>(i)))
                    {
                        index = i - 48;
                        break;
                    }
                }

                switch (index)
                {
                case 0:
                    break;
                case 1:
                    glad->run();
                    break;
                case 2:
                    stb_image->run();
                    break;
                case 3:
                    glm->run(static_cast<float>(x), static_cast<float>(y));
                    break;
                case 4:
                    glm_image->run(static_cast<float>(x), static_cast<float>(y));
                    break;
                case 5:
                    for (int i = 65; i <= 90; ++i)
                    {
                        if (window->key_down(
                            static_cast<eqx::tpl::wrapper::glfw::Key>(i)))
                        {
                            if (window->key_down(
                                eqx::tpl::wrapper::glfw::Key::Left_Shift))
                            {
                                c = static_cast<char>(i);
                            }
                            else
                            {
                                c = static_cast<char>(i + 32);
                            }
                            break;
                        }
                    }
                    freetype->run(c);
                    break;
                case 6:
                    glm_freetype->run(static_cast<float>(x),
                        static_cast<float>(y));
                    break;
                case 7:
                    miniaudio->run();
                    break;
                }

                window->swap_buffers();
                window->poll_events();

                frame_timer.end();
            }

            glad.reset();
            stb_image.reset();
            glm.reset();
            glm_image.reset();
            freetype.reset();
            glm_freetype.reset();
            window.reset();

            eqx::tpl::wrapper::glfw::terminate();
        }

    private:
    };
}
