// Main.cpp

import <Eqx/std.hpp>;
import <Eqx/TPL/glfw/glfw.hpp>;

using namespace std::literals;

#ifdef EQX_SMOKE
    constexpr auto c_smoke = true;
#else
    constexpr auto c_smoke = false;
#endif // EQX_SMOKE

constexpr auto c_width = 1920;
constexpr auto c_height = 1080;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::format_to(std::ostream_iterator<char>(std::cout), "Start\n\n"sv);

    [[maybe_unused]] auto ec = glfwInit();
    assert(ec != GLFW_FALSE);

    glfwSetErrorCallback([](int code, const char* msg)
        {
            std::format_to(std::ostream_iterator<char>(std::cerr),
                "glfw Error Code: {}\n"sv
                "glfw Message: {}\n"sv, code, msg);
            assert(false);
        });

    auto name = std::string(128, '\0');
    auto x = 0.0;
    auto y = 0.0;
    auto start = std::chrono::steady_clock::now();
    auto end = start;
    auto frames = 0ull;
    auto fps = 0.0f;
    auto window = static_cast<GLFWwindow*>(nullptr);

    window = glfwCreateWindow(c_width, c_height, "Eqx/TPL --- Test glfw",
        nullptr, nullptr);

    assert(window != nullptr);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
        glfwGetCursorPos(window, &x, &y);

        std::format_to(std::ranges::begin(name),
            "Eqx/TPL --- "sv
            "Test glfw --- "sv
            "Location: ({}, {}) --- "sv
            "Frames: {} --- "sv
            "FPS: {}\0"sv, x, y, frames, fps);

        glfwSetWindowTitle(window, name.c_str());

        if constexpr (c_smoke == true)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        ++frames;
        end = std::chrono::steady_clock::now();
        if ((end - start) > 1'000ms) [[unlikely]]
        {
            fps = (frames * 1'000.0f)
                / std::chrono::duration_cast<std::chrono::milliseconds>(
                    end - start).count();
            frames = 0ull;

            start = end;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    std::format_to(std::ostream_iterator<char>(std::cout), "\nEnd\n"sv);
    return EXIT_SUCCESS;
}
