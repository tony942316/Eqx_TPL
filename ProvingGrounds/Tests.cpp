module;

#include <cstdlib>
#include <string>
#include <iostream>

export module Eqx.TPL.Tests;

import <Eqx/TPL/stb/stb_image.hpp>;
import <Eqx/TPL/glfw/glfw.hpp>;

namespace tests
{
    export inline void run() noexcept;

    inline void glfw() noexcept;
}

namespace tests
{
    inline void run() noexcept
    {
        auto input = 0;
        while (input != -1)
        {
            std::cout << "===========Menu===========\n";
            std::cout << "1) glfw Test\n";
            std::cout << "-1) Exit\n";
            std::cout << "==========================\n";
            std::cout << "Input: ";
            std::cin >> input;

            switch (input)
            {
            case 1:
                glfw();
                break;
            case -1:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << input << " Is An Invalid Input\n";
                break;
            }
            std::cout << "\n";
        }
    }

    inline void glfw() noexcept
    {
        if (!glfwInit())
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
        auto window = static_cast<GLFWwindow*>(nullptr);

        window = glfwCreateWindow(640, 480, "Test Glfw", NULL, NULL);

        if (!window)
        {
            std::cerr << "glfw Window Failure!\n";
            glfwTerminate();
            std::abort();
        }

        glfwMakeContextCurrent(window);

        while (!glfwWindowShouldClose(window))
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
