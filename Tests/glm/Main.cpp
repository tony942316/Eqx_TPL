// Smoke.cpp

import <Eqx/std.hpp>;

import Eqx.TPL.Wrapper.glfw;
import Eqx.TPL.Wrapper.glad;
import Eqx.TPL.Wrapper.glm;

import Eqx.TPL.Tests.Lib;

using namespace std::literals;

inline void run() noexcept
{
    const char *vss = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 proj;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = proj * view * model * vec4(aPos, 1.0f);\n"
        "}\0";
    const char *fss = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    auto name = std::array<char, std::size_t{ 128 }>{};
    auto frame_timer = eqx::tpl::tests::lib::Frame_Timer{};
    auto window = eqx::tpl::wrapper::glfw::Window{ 1920, 1080,
        std::ranges::cdata(name) };

    window.make_context_current();
    window.load_glad();
    window.swap_interval(1);

    auto context = eqx::tpl::wrapper::glad::Context{
        eqx::tpl::wrapper::glad::Shader_Program::from_source(vss, fss),
        eqx::tpl::wrapper::glad::Vertex_Array{
            std::to_array({
                0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f }),
            std::to_array({ 3u }),
            std::to_array({
                0u, 1u, 3u,
                1u, 2u, 3u }) } };

    const auto [width, height] = window.get_window_size();

    auto model = eqx::tpl::wrapper::glm::Mat4{ 1.0f };
    model.translate(
        eqx::tpl::wrapper::glm::Vec3{ 100.0f, -100.0f, 0.0f });
    model.scale(eqx::tpl::wrapper::glm::Vec3{ 100.0f, 100.0f, 1.0f });
    auto view = eqx::tpl::wrapper::glm::Mat4{ 1.0f };
    auto projection = eqx::tpl::wrapper::glm::Mat4::ortho(
        0.0f, static_cast<float>(width), -static_cast<float>(height),
        0.0f);

    context.set_uniform("model", model.value_ptr());
    context.set_uniform("view", view.value_ptr());
    context.set_uniform("proj", projection.value_ptr());

    frame_timer.start();

    while (window.window_should_close() == false)
    {
        window.clear(0.2f, 0.3f, 0.3f);

        const auto [x, y] = window.get_cursor_pos();

        std::format_to(std::ranges::begin(name),
            "Eqx/TPL --- "sv
            "Test glm --- "sv
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
