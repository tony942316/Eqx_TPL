export module Eqx.TPL.Tests.Stb_Image;

import <Stdlib.hpp>;

import <Eqx/TPL/glfw/glfw.hpp>;
import <Eqx/TPL/glad/glad.hpp>;
import <Eqx/TPL/stb/stb_image.hpp>;

namespace tests::stb_image
{
    constexpr auto c_Width = 640;
    constexpr auto c_Height = 480;

    export inline void run() noexcept;
}

namespace tests::stb_image
{
    inline void run() noexcept
    {
        const char *vss = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec2 aTexCoord;\n"
            "out vec2 TexCoord;\n"
            "void main()\n"
            "{\n"
            "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char *fss = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "in vec2 TexCoord;\n"
            "uniform sampler2D tex0;\n"
            "void main()\n"
            "{\n"
            "   FragColor = texture(tex0, TexCoord);\n"
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

        window = glfwCreateWindow(c_Width, c_Height, "Test stb_image",
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
        auto vertices = std::array<float, 20>{
             0.5F,  0.5F, 0.0F,  1.0F, 1.0F, // top right
             0.5F, -0.5F, 0.0F,  1.0F, 0.0F, // bottom right
            -0.5F, -0.5F, 0.0F,  0.0F, 0.0F, // bottom left
            -0.5F,  0.5F, 0.0F,  0.0F, 1.0F  // top left
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
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
            5 * sizeof(float), (void*)0);
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        // NOLINTEND(modernize-use-nullptr)
        glEnableVertexAttribArray(0);
        // NOLINTBEGIN(performance-no-int-to-ptr)
        // NOLINTBEGIN(cppcoreguidelines-pro-type-cstyle-cast)
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
            5 * sizeof(float), (void*)(3 * sizeof(float)));
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        // NOLINTEND(cppcoreguidelines-pro-type-cstyle-cast)
        // NOLINTEND(performance-no-int-to-ptr)
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        auto tex = 0U;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        auto width = 0;
        auto height = 0;
        auto nrChannels = 0;
        stbi_set_flip_vertically_on_load(static_cast<int>(true));
        unsigned char* data = stbi_load("Resources/Textures/BrickWall.png",
            &width, &height, &nrChannels, 0);
        if (data == nullptr)
        {
            std::cerr << "Failed To Load Texture!\n";
            std::abort();
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);

        glUseProgram(sp);
        glUniform1i(glGetUniformLocation(sp, "tex0"), 0);

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

            name = "stbi_image Test --- Mouse Position: (";
            name += std::to_string(x);
            name += ", ";
            name += std::to_string(y);
            name += ")";

            glfwSetWindowTitle(window, name.c_str());

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, tex);
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
