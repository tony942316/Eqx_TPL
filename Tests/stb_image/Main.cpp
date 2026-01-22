// Main.cpp

import <Eqx/std.hpp>;

import Eqx.TPL.Wrapper.glfw;
import Eqx.TPL.Wrapper.glad;
import Eqx.TPL.Wrapper.stb_image;

import Eqx.TPL.Tests.Lib;

using namespace std::literals;

inline void run() noexcept
{
    const char *vss = "#version 330 core\n"
        "layout (location = 0) in vec2 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
        "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
        "}";
    const char *fss = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D tex0;\n"
        "void main()\n"
        "{\n"
        "   FragColor = texture(tex0, TexCoord);\n"
        "}\n";

    auto name = std::array<char, std::size_t{ 128 }>{};
    auto frame_timer = eqx::tpl::tests::lib::Frame_Timer{};
    auto window = eqx::tpl::wrapper::glfw::Window{ 1920, 1080,
        std::ranges::cdata(name) };

    window.make_context_current();
    window.load_glad();
    window.swap_interval(1);

    auto image = eqx::tpl::wrapper::stb_image::Image{
        "Resources/Textures/Brick_Wall.png"sv };
    auto tex = eqx::tpl::wrapper::glad::Texture{ image.get_width(),
        image.get_height(), image.get_data(), image.get_channel_count() };
    auto context = eqx::tpl::wrapper::glad::Context{
        eqx::tpl::wrapper::glad::Shader_Program::from_source(vss, fss),
        eqx::tpl::wrapper::glad::Vertex_Array{
            std::to_array({
                0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 0.0f }),
            std::to_array({ 2u, 2u }),
            std::to_array({
                0u, 1u, 3u,
                1u, 2u, 3u }) },
        &tex };

    frame_timer.start();

    while (window.window_should_close() == false)
    {
        window.clear(0.2f, 0.3f, 0.3f);

        const auto [x, y] = window.get_cursor_pos();

        std::format_to(std::ranges::begin(name),
            "Eqx/TPL --- "sv
            "Test stb_image --- "sv
            "Location: ({}, {}) --- "sv
            "Frames: {} --- "sv
            "FPS: {} |\0"sv, x, y, frame_timer.get_frames(),
            frame_timer.get_fps());

        window.set_window_title(std::ranges::cdata(name));

        context.draw();

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
