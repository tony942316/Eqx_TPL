// Window.cpp

export module Eqx.TPL.Wrapper.glfw.Window;

import <Eqx/std.hpp>;
import <Eqx/TPL/glfw/glfw.hpp>;
import <Eqx/TPL/glad/glad.hpp>;

using namespace std::literals;

export namespace eqx::tpl::wrapper::glfw
{
    inline void init() noexcept
    {
        [[maybe_unused]] const auto ec = glfwInit();
        assert(ec != GLFW_FALSE);

        glfwSetErrorCallback([](int code, const char* msg)
            {
                std::format_to(std::ostream_iterator<char>(std::cerr),
                    "glfw Error Code: {}\n"sv
                    "glfw Message: {}\n"sv, code, msg);
                assert(false);
            });

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    inline void terminate() noexcept
    {
        glfwTerminate();
    }

    inline std::pair<int, int> get_screen_dimensions() noexcept
    {
        auto monitor = glfwGetPrimaryMonitor();
        assert(monitor != nullptr);

        auto mode = glfwGetVideoMode(monitor);
        assert(mode != nullptr);

        return std::make_pair(mode->width, mode->height);
    }

    inline void print_info() noexcept
    {
        const auto [width, height] =
            eqx::tpl::wrapper::glfw::get_screen_dimensions();

        int max_fragment_texture_units = 0;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,
            &max_fragment_texture_units);

        const char* opengl_version =
            std::bit_cast<const char*>(glGetString(GL_VERSION));
        const char* opengl_vendor =
            std::bit_cast<const char*>(glGetString(GL_VENDOR));
        const char* opengl_renderer =
            std::bit_cast<const char*>(glGetString(GL_RENDERER));
        const char* opengl_shading_language_version =
            std::bit_cast<const char*>(glGetString(
                GL_SHADING_LANGUAGE_VERSION));

        std::format_to(std::ostream_iterator<char>(std::cout),
            "OpenGL Version: {}\n"sv
            "OpenGL Vendor: {}\n"sv
            "OpenGL Renderer: {}\n"sv
            "OpenGL Shading Language Version: {}\n"sv
            "Screen Dimensions: ({} x {})\n"sv
            "Max Texture Units: {}\n"sv,
            opengl_version, opengl_vendor, opengl_renderer,
            opengl_shading_language_version, width, height,
            max_fragment_texture_units);
    }

    enum class Key : int
    {
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,
        Zero = GLFW_KEY_0,
        One = GLFW_KEY_1,
        Two = GLFW_KEY_2,
        Three = GLFW_KEY_3,
        Four = GLFW_KEY_4,
        Five = GLFW_KEY_5,
        Six = GLFW_KEY_6,
        Seven = GLFW_KEY_7,
        Eight = GLFW_KEY_8,
        Nine = GLFW_KEY_9,
        Up = GLFW_KEY_UP,
        Left = GLFW_KEY_LEFT,
        Down = GLFW_KEY_DOWN,
        Right = GLFW_KEY_RIGHT,
        Space = GLFW_KEY_SPACE,
        Left_Shift = GLFW_KEY_LEFT_SHIFT,
        Escape = GLFW_KEY_ESCAPE
    };

    enum class Mouse_Button : int
    {
        Left = GLFW_MOUSE_BUTTON_LEFT,
        Right = GLFW_MOUSE_BUTTON_RIGHT
    };

    enum class Key_State : int
    {
        Up = GLFW_RELEASE,
        Down = GLFW_PRESS
    };

    class Window
    {
    public:
        Window() = delete;
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        explicit inline Window(const int width, const int height,
            const char* name) noexcept
            :
            m_window(glfwCreateWindow(width, height, name, nullptr, nullptr))
        {
            assert(this->get_window() != nullptr);
        }

        inline Window(Window&& other) noexcept
            :
            m_window(std::exchange(other.edit_window(), nullptr))
        {
            assert(this->get_window() != nullptr);
        }

        inline Window& operator=(Window&& other) noexcept
        {
            assert(this != &other);

            std::ranges::swap(this->edit_window(), other.edit_window());
            return *this;
        }

        inline ~Window() noexcept
        {
            glfwDestroyWindow(this->edit_window());
        }

        inline void make_context_current() noexcept
        {
            glfwMakeContextCurrent(this->edit_window());
        }

        inline void load_glad() noexcept
        {
            [[maybe_unused]] const auto ec = gladLoadGLLoader(
                std::bit_cast<GLADloadproc>(&glfwGetProcAddress));
            assert(ec != 0);

            glfwSetFramebufferSizeCallback(this->edit_window(),
                []([[maybe_unused]] GLFWwindow* window, int width, int height)
                {
                    glViewport(0, 0, width, height);
                });

            glEnable(GL_BLEND);
            glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

            const auto [width, height] = this->get_window_size();

            glViewport(0, 0, width, height);
        }

        inline void clear(const float r, const float g,
            const float b) const noexcept
        {
            glClearColor(r, g, b, 1.0F);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        inline void swap_interval(const int interval) const noexcept
        {
            assert(glfwGetCurrentContext() == this->get_window());
            glfwSwapInterval(interval);
        }

        [[nodiscard]] inline bool window_should_close() noexcept
        {
            return glfwWindowShouldClose(this->edit_window()) == GLFW_TRUE;
        }

        inline std::pair<double, double> get_cursor_pos() noexcept
        {
            auto pos = std::make_pair(0.0, 0.0);
            glfwGetCursorPos(this->edit_window(), &pos.first, &pos.second);
            return pos;
        }

        inline void set_window_title(const std::string_view name) noexcept
        {
            glfwSetWindowTitle(this->edit_window(), name.data());
        }

        inline void set_window_should_close() noexcept
        {
            glfwSetWindowShouldClose(this->edit_window(), GL_TRUE);
        }

        inline void swap_buffers() noexcept
        {
            glfwSwapBuffers(this->edit_window());
        }

        inline void poll_events() const noexcept
        {
            glfwPollEvents();
        }

        [[nodiscard]] inline Key_State key_state(Key key) noexcept
        {
            return static_cast<Key_State>(glfwGetKey(this->edit_window(),
                static_cast<decltype(GLFW_KEY_W)>(key)));
        }

        [[nodiscard]] inline bool key_down(Key key) noexcept
        {
            return this->key_state(key) == Key_State::Down;
        }

        [[nodiscard]] inline bool key_up(Key key) noexcept
        {
            return !this->key_down(key);
        }

        inline void set_key_callback(void (*func)(Key, Key_State)) noexcept
        {
            static auto user_callback = static_cast<
                void (*)(Key, Key_State)>(nullptr);

            user_callback = func;

            glfwSetKeyCallback(this->edit_window(), []
                ([[maybe_unused]] GLFWwindow* window, int key,
                [[maybe_unused]] int scancode, int action,
                [[maybe_unused]] int mods) -> void
                {
                    std::invoke(user_callback, static_cast<Key>(key),
                        static_cast<Key_State>(action));
                });
        }

        inline void set_mouse_button_callback(void (*func)(Mouse_Button,
            Key_State)) noexcept
        {
            static auto user_callback = static_cast<
                void (*)(Mouse_Button, Key_State)>(nullptr);

            user_callback = func;

            glfwSetMouseButtonCallback(this->edit_window(), []
                ([[maybe_unused]] GLFWwindow* window, int button, int action,
                [[maybe_unused]] int mods) -> void
                {
                    std::invoke(user_callback,
                        static_cast<Mouse_Button>(button),
                        static_cast<Key_State>(action));
                });
        }

        [[nodiscard]] inline std::pair<int, int> get_window_size() noexcept
        {
            auto dimensions = std::make_pair(0, 0);

            glfwGetWindowSize(this->edit_window(), &dimensions.first,
                &dimensions.second);

            return dimensions;
        }

    private:
        constexpr const GLFWwindow* const get_window() const noexcept
        {
            return this->m_window;
        }

        constexpr GLFWwindow*& edit_window() noexcept
        {
            return this->m_window;
        }

        GLFWwindow* m_window;
    };
}
