export module Eqx.TPL.Tests.Glfw;

import <Stdlib.hpp>;

import <Eqx/TPL/glfw/glfw.hpp>;

namespace tests::glfw
{
    constexpr auto c_Width = 640;
    constexpr auto c_Height = 480;

    export inline void run() noexcept;
}

namespace tests::glfw
{
    inline void run() noexcept
    {
        if (glfwInit() == GLFW_FALSE)
        {
            std::cerr << "glfw Init Failure!\n";
            std::abort();
        }

        glfwSetErrorCallback([](int code, const char* msg)
            {
                std::cerr << "EC => " << code << '\n'
                    << "Msg => " << msg << '\n';
            });

        auto name = std::string{};
        auto x = 0.0;
        auto y = 0.0;
        auto* window = static_cast<GLFWwindow*>(nullptr);

        window = glfwCreateWindow(c_Width, c_Height, "Test Glfw",
            nullptr, nullptr);

        if (window == nullptr)
        {
            std::cerr << "glfw Window Failure!\n";
            glfwTerminate();
            std::abort();
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        while (glfwWindowShouldClose(window) == GLFW_FALSE)
        {
            glfwGetCursorPos(window, &x, &y);

            name = "glfw Test --- Mouse Position: (";
            name += std::to_string(x);
            name += ", ";
            name += std::to_string(y);
            name += ")";

            glfwSetWindowTitle(window, name.c_str());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);

        glfwTerminate();
    }
}
