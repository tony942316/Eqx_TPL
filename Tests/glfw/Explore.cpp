// Explore.cpp

import <Eqx/std.hpp>;
import <Eqx/TPL/glfw/glfw.hpp>;

using namespace std::literals;

constexpr auto c_Width = 1920;
constexpr auto c_Height = 1080;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::format_to(std::ostream_iterator<char>(std::cout), "Start\n\n"sv);

    if (glfwInit() == GLFW_FALSE)
    {
        std::format_to(std::ostream_iterator<char>(std::cerr),
            "glfw Init Failure\n"sv);
        std::abort();
    }

    glfwSetErrorCallback([](int code, const char* msg)
        {
            std::format_to(std::ostream_iterator<char>(std::cerr),
                "glfw Error Code: {}\nglfw Message: {}\n"sv, code, msg);
        });

    auto name = std::string{};
    auto x = 0.0;
    auto y = 0.0;
    auto* window = static_cast<GLFWwindow*>(nullptr);

    window = glfwCreateWindow(c_Width, c_Height, "Test Glfw", nullptr, nullptr);

    if (window == nullptr)
    {
        std::format_to(std::ostream_iterator<char>(std::cerr),
            "glfw Window Failure\n"sv);
        glfwTerminate();
        std::abort();
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
        glfwGetCursorPos(window, &x, &y);

        name = std::format("glfw Test --- Mouse Position: ({}, {})",
            std::to_string(x), std::to_string(y));

        glfwSetWindowTitle(window, name.c_str());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    std::format_to(std::ostream_iterator<char>(std::cout), "\nEnd\n"sv);
    return EXIT_SUCCESS;
}
