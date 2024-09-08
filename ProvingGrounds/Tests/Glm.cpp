export module Eqx.TPL.Tests.Glm;

import <Stdlib.hpp>;

import <Eqx/TPL/glfw/glfw.hpp>;
import <Eqx/TPL/glad/glad.hpp>;
import <Eqx/TPL/glm/glm.hpp>;

namespace tests::glm
{
    constexpr auto c_Width = 640;
    constexpr auto c_Height = 480;

    export inline void run() noexcept;
}

namespace tests::glm
{
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

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        auto name = std::string{};
        auto x = 0.0;
        auto y = 0.0;
        auto* window = static_cast<GLFWwindow*>(nullptr);

        window = glfwCreateWindow(c_Width, c_Height, "Test Glm",
            nullptr, nullptr);

        if (window == nullptr)
        {
            std::cerr << "glfw Window Failure!\n";
            glfwTerminate();
            std::abort();
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwSetFramebufferSizeCallback(window,
            []([[maybe_unused]] GLFWwindow* window, int width, int height)
            {
                glViewport(0, 0, width, height);
            });

        //NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
        if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0)
        {
            std::cerr << "Failed To Initialize GLAD\n";
            glfwTerminate();
            std::abort();
        }
        //NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

        unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vss, nullptr);
        glCompileShader(vs);

        unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fss, nullptr);
        glCompileShader(fs);

        unsigned int sp = glCreateProgram();
        glAttachShader(sp, vs);
        glAttachShader(sp, fs);
        glLinkProgram(sp);

        glDeleteShader(vs);
        glDeleteShader(fs);

        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto vertices = std::array<float, 12>{
             100.0F,  100.0F, 0.0F,  // top right
             100.0F, 0.0F, 0.0F,  // bottom right
             0.0F, 0.0F, 0.0F,  // bottom left
             0.0F,  100.0F, 0.0F   // top left
        };
        auto indices = std::array<unsigned int, 6>{
            0U, 1U, 3U,
            1U, 2U, 3U
        };
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)

        auto VAO = 0U;
        auto VBO = 0U;
        auto EBO = 0U;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
            GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
            GL_STATIC_DRAW);

        // NOLINTBEGIN(modernize-use-nullptr)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
            (void*)0);
        // NOLINTEND(modernize-use-nullptr)
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        auto model = ::glm::mat4{1.0F};
        auto view = ::glm::mat4{1.0F};
        auto projection = ::glm::mat4{1.0F};
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        projection = ::glm::ortho(-320.0F, 320.0F, -240.0F, 240.0F,
            -1000.0F, 1000.0F);
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        glUseProgram(sp);
        glUniformMatrix4fv(glGetUniformLocation(sp, "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(sp, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(sp, "proj"), 1, GL_FALSE, &projection[0][0]);

        std::cout << "Version: " << glGetString(GL_VERSION) << '\n';
        std::cout << "Max Textures: "
            << GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS << '\n';

        while (glfwWindowShouldClose(window) == GLFW_FALSE)
        {
            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
            glClear(GL_COLOR_BUFFER_BIT);

            glfwGetCursorPos(window, &x, &y);

            name = "glm Test --- Mouse Position: (";
            name += std::to_string(x);
            name += ", ";
            name += std::to_string(y);
            name += ")";

            glfwSetWindowTitle(window, name.c_str());

            glUseProgram(sp);
            glBindVertexArray(VAO);
            // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
            // NOLINTBEGIN(modernize-use-nullptr)
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            // NOLINTEND(modernize-use-nullptr)
            // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)

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
