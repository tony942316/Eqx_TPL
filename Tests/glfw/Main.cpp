// Main.cpp

import <Eqx/std.hpp>;

import Eqx.TPL.Wrapper.glfw;

import Eqx.TPL.Tests.Lib;

using namespace std::literals;

inline void run() noexcept
{
    auto name = std::array<char, std::size_t{ 128 }>{};
    auto frame_timer = eqx::tpl::tests::lib::Frame_Timer{};
    auto window = eqx::tpl::wrapper::glfw::Window{ 1920, 1080,
        std::ranges::cdata(name) };

    window.make_context_current();
    window.swap_interval(1);

    frame_timer.start();

    while (window.window_should_close() == false)
    {
        const auto [x, y] = window.get_cursor_pos();

        std::format_to(std::ranges::begin(name),
            "Eqx/TPL --- "sv
            "Test glfw --- "sv
            "Location: ({}, {}) --- "sv
            "Frames: {} --- "sv
            "FPS: {} |\0"sv, x, y, frame_timer.get_frames(),
            frame_timer.get_fps());

        window.set_window_title(std::ranges::cdata(name));

        window.set_window_should_close();

        window.swap_buffers();
        window.poll_events();

        frame_timer.end();
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::format_to(std::ostream_iterator<char>(std::cout), "Start\n\n"sv);

    eqx::tpl::wrapper::glfw::init();

    run();

    eqx::tpl::wrapper::glfw::terminate();

    std::format_to(std::ostream_iterator<char>(std::cout), "\nEnd\n"sv);
    return EXIT_SUCCESS;
}
