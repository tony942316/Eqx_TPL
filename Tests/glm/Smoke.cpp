// Smoke.cpp

import <Eqx/std.hpp>;
import <Eqx/TPL/glfw/glfw.hpp>;
import <Eqx/TPL/glad/glad.hpp>;
import <Eqx/TPL/glm/glm.hpp>;

using namespace std::literals;

constexpr auto c_Width = 1920;
constexpr auto c_Height = 1080;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::format_to(std::ostream_iterator<char>(std::cout), "Start\n\n"sv);
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
        (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    auto model = glm::mat4{1.0F};
    auto view = glm::mat4{1.0F};
    auto projection = glm::mat4{1.0F};
    projection = glm::ortho(-960.0F, 960.0F, -540.0F, 540.0F,
        -1000.0F, 1000.0F);
    glUseProgram(sp);
    glUniformMatrix4fv(glGetUniformLocation(sp, "model"), 1, GL_FALSE,
        &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(sp, "view"), 1, GL_FALSE,
        &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(sp, "proj"), 1, GL_FALSE,
        &projection[0][0]);

    const char* version = std::bit_cast<const char*>(glGetString(GL_VERSION));
    std::format_to(std::ostream_iterator<char>(std::cout),
        "Version: {}\nMax Textures: {}\n"sv, version,
        GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
        glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

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
