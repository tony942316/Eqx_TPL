// Shader_Source.cpp

export module Eqx.TPL.Wrapper.glad.Shader_Source;

import <Eqx/std.hpp>;
import <Eqx/TPL/glad/glad.hpp>;

using namespace std::literals;

export namespace eqx::tpl::wrapper::glad
{
    static_assert(std::same_as<GLuint, unsigned int>);
    static_assert(std::same_as<decltype(GL_VERTEX_SHADER), int>);
    static_assert(std::same_as<decltype(GL_FALSE), int>);
    static_assert(std::same_as<GLint, int>);
    static_assert(std::same_as<GLsizei, int>);

    template <int t_shader_type>
    class Shader_Source
    {
    public:
        Shader_Source() = delete;
        Shader_Source(const Shader_Source&) = delete;
        Shader_Source& operator= (const Shader_Source&) = delete;

        explicit inline Shader_Source(const char* source) noexcept
            :
            m_id(glCreateShader(t_shader_type))
        {
            assert(this->get_id() != 0u);

            glShaderSource(this->get_id(), 1, &source, nullptr);
            glCompileShader(this->get_id());

            assert(std::invoke([id = this->get_id()]() noexcept -> bool
                {
                    auto result = GL_FALSE;
                    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

                    auto log_len = 0;
                    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_len);

                    auto log = std::array<char, std::size_t{ 512 }>{};
                    assert(log_len < 512);

                    if (log_len > 1) [[unlikely]]
                    {
                        int written = 0;
                        glGetShaderInfoLog(id, log_len, &written,
                            std::ranges::data(log));
                        std::format_to(std::ostream_iterator<char>(std::cerr),
                            "[Shader {}]: {}\n"sv,
                            result == GL_TRUE ? "Warning"sv : "Error"sv,
                            std::ranges::data(log));
                    }
                    return result == GL_TRUE;
                }));
        }

        inline Shader_Source(Shader_Source&& other) noexcept
            :
            m_id(std::exchange(other.edit_id(), 0u))
        {
        }

        inline Shader_Source& operator= (Shader_Source&& other) noexcept
        {
            std::swap(this->edit_id(), other.edit_id());
            return *this;
        }

        inline ~Shader_Source() noexcept
        {
            glDeleteShader(this->get_id());
        }

        [[nodiscard]] constexpr unsigned int get_id() const noexcept
        {
            return this->m_id;
        }

        [[nodiscard]] static inline Shader_Source<t_shader_type> from_file(
            const std::filesystem::path& path) noexcept
        {
            assert(std::filesystem::exists(path));

            auto file = std::ifstream{ path, std::ios::in };
            assert(file.is_open());

            return Shader_Source<t_shader_type>{
                (std::stringstream{} << file.rdbuf()).str().c_str() };
        }

    private:
        [[nodiscard]] constexpr unsigned int& edit_id() noexcept
        {
            this->m_id;
        }

        unsigned int m_id;
    };

    using Vertex_Shader_Source = Shader_Source<GL_VERTEX_SHADER>;
    using Fragment_Shader_Source = Shader_Source<GL_FRAGMENT_SHADER>;
}
