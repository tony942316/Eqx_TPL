module;

#include <cstdlib>
#include <string>
#include <iostream>

export module Eqx.TPL.Tests;

import <Eqx/TPL/stb/stb_image.hpp>;
import <Eqx/TPL/glfw/glfw.hpp>;
import <Eqx/TPL/glad/glad.hpp>;

namespace tests
{
    export inline void run() noexcept;

    inline void glfw() noexcept;
    inline void glad() noexcept;
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
            std::cout << "2) glad Test\n";
            std::cout << "-1) Exit\n";
            std::cout << "==========================\n";
            std::cout << "Input: ";
            std::cin >> input;

            switch (input)
            {
            case 1:
                glfw();
                break;
            case 2:
                glad();
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

    inline void glad() noexcept
    {
        const char *vss = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char *fss = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";

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

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        auto name = std::string{};
        auto x = 0.0;
        auto y = 0.0;
        auto window = static_cast<GLFWwindow*>(nullptr);

        window = glfwCreateWindow(640, 480, "Test Glad", NULL, NULL);

        if (!window)
        {
            std::cerr << "glfw Window Failure!\n";
            glfwTerminate();
            std::abort();
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window,
            [](GLFWwindow* window, int width, int height)
            {
                glViewport(0, 0, width, height);
            });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed To Initialize GLAD\n";
            glfwTerminate();
            std::abort();
        }

        unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vss, NULL);
        glCompileShader(vs);

        unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fss, NULL);
        glCompileShader(fs);

        unsigned int sp = glCreateProgram();
        glAttachShader(sp, vs);
        glAttachShader(sp, fs);
        glLinkProgram(sp);

        glDeleteShader(vs);
        glDeleteShader(fs);

        float vertices[] = {
             0.5f,  0.5f, 0.0f,  // top right
             0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
        };
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
            GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
            GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
            (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwGetCursorPos(window, &x, &y);

            name = "glfw Test --- Mouse Position: (";
            name += std::to_string(x);
            name += ", ";
            name += std::to_string(y);
            name += ")";

            glfwSetWindowTitle(window, name.c_str());

            glUseProgram(sp);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteProgram(sp);

        glfwDestroyWindow(window);

        glfwTerminate();
    }
}
