// Smoke.cpp

import <Eqx/std.hpp>;
import <Eqx/TPL/glfw/glfw.hpp>;
import <Eqx/TPL/glad/glad.hpp>;
import <Eqx/TPL/stb/stb_image.hpp>;

using namespace std::literals;

constexpr auto c_Width = 1920;
constexpr auto c_Height = 1080;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::format_to(std::ostream_iterator<char>(std::cout), "Start\n\n"sv);
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
        std::format_to(std::ostream_iterator<char>(std::cerr),
            "glfw Init Failure!\n"sv);
        std::abort();
    }

    glfwSetErrorCallback([](int code, const char* msg)
        {
            std::format_to(std::ostream_iterator<char>(std::cerr),
                "glfw Error Code: {}\nglfw Message: {}\n"sv, code, msg);
        });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto* window = static_cast<GLFWwindow*>(nullptr);

    window = glfwCreateWindow(c_Width, c_Height, "Test Glad",
        nullptr, nullptr);

    if (window == nullptr)
    {
        std::format_to(std::ostream_iterator<char>(std::cerr),
            "glfw Window Failure!\n");
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

    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0)
    {
        std::format_to(std::ostream_iterator<char>(std::cerr),
            "glad Init Failure!\n"sv);
        glfwTerminate();
        std::abort();
    }

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

    auto vertices = std::array<float, 20>{
         0.5F,  0.5F, 0.0F,  1.0F, 0.0F, // top right
         0.5F, -0.5F, 0.0F,  1.0F, 1.0F, // bottom right
        -0.5F, -0.5F, 0.0F,  0.0F, 1.0F, // bottom left
        -0.5F,  0.5F, 0.0F,  0.0F, 0.0F  // top left
    };
    auto indices = std::array<unsigned int, 6>{
        0U, 1U, 3U,
        1U, 2U, 3U
    };

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
        (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
        (void*)(3 * sizeof(float)));
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
    unsigned char* data = stbi_load("Resources/Textures/BrickWall.png",
        &width, &height, &nrChannels, 0);
    if (data == nullptr)
    {
        std::format_to(std::ostream_iterator<char>(std::cerr),
            "stb_image Load Failure: {}\n"sv, stbi_failure_reason());
        std::abort();
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    glUseProgram(sp);
    glUniform1i(glGetUniformLocation(sp, "tex0"), 0);

    const char* version = std::bit_cast<const char*>(glGetString(GL_VERSION));
    std::format_to(std::ostream_iterator<char>(std::cout),
        "Version: {}\nMax Textures: {}\n"sv, version,
        GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
        glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUseProgram(sp);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSetWindowShouldClose(window, GL_TRUE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(sp);

    glfwDestroyWindow(window);

    glfwTerminate();

    std::format_to(std::ostream_iterator<char>(std::cout), "\nEnd\n"sv);
    return EXIT_SUCCESS;
}
