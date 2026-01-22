// Shader_Source.cpp

export module Eqx.TPL.Wrapper.glad.Shader_Program;

import <Eqx/std.hpp>;
import <Eqx/TPL/glad/glad.hpp>;

import Eqx.TPL.Wrapper.glad.Shader_Source;

using namespace std::literals;

export namespace eqx::tpl::wrapper::glad
{
    static_assert(std::same_as<GLuint, unsigned int>);

    class Shader_Program
    {
    public:
        Shader_Program() = delete;
        Shader_Program(const Shader_Program&) = delete;
        Shader_Program& operator= (const Shader_Program&) = delete;

        explicit inline Shader_Program(const Vertex_Shader_Source& vs,
            const Fragment_Shader_Source& fs) noexcept
            :
            m_id(glCreateProgram())
        {
            assert(this->get_id() != 0u);
            assert(vs.get_id() != 0u);
            assert(fs.get_id() != 0u);

            glAttachShader(this->get_id(), vs.get_id());
            glAttachShader(this->get_id(), fs.get_id());
            glLinkProgram(this->get_id());
        }

        inline Shader_Program(Shader_Program&& other) noexcept
            :
            m_id(std::exchange(other.edit_id(), 0u))
        {
        }

        inline Shader_Program& operator= (Shader_Program&& other) noexcept
        {
            std::swap(this->edit_id(), other.edit_id());
            return *this;
        }

        inline ~Shader_Program() noexcept
        {
            glDeleteProgram(this->get_id());
        }

        inline void enable() const noexcept
        {
            assert(this->get_id() != 0u);

            glUseProgram(this->get_id());
        }

        inline void disable() const noexcept
        {
            assert(this->get_id() != 0u);

            glUseProgram(0u);
        }

        inline void set_uniform(const char* name,
            const int value) const noexcept
        {
            this->enable();
            glUniform1i(glGetUniformLocation(this->get_id(), name), value);
        }

        inline void set_uniform(const char* name,
            const float* value) const noexcept
        {
            this->enable();
            glUniformMatrix4fv(glGetUniformLocation(this->get_id(), name), 1,
                GL_FALSE, value);
        }

        /*
        inline void set_mat4(const std::string_view name,
            const glm::mat4& mat) const noexcept
        {
            assert(this->valid());

            this->enable();
            glUniformMatrix4fv(glGetUniformLocation(this->m_id, name.data()),
                1, GL_FALSE, &mat[0][0]);
        }

        inline void activate_texture(const std::string_view name,
            const int tex) const noexcept
        {
            this->enable();
            glUniform1i(glGetUniformLocation(this->m_id, name.data()), tex);
        }
        */

        [[nodiscard]] static inline Shader_Program from_source(const char* vss,
            const char* fss) noexcept
        {
            return Shader_Program{ Vertex_Shader_Source{ vss },
                Fragment_Shader_Source{ fss }};
        }

        [[nodiscard]] static inline Shader_Program from_files(
            const std::filesystem::path& vsf,
            const std::filesystem::path& fsf) noexcept
        {
            return Shader_Program{ Vertex_Shader_Source::from_file(vsf),
                Fragment_Shader_Source::from_file(fsf) };
        }

    private:
        [[nodiscard]] constexpr unsigned int get_id() const noexcept
        {
            return this->m_id;
        }

        [[nodiscard]] constexpr unsigned int& edit_id() noexcept
        {
            return this->m_id;
        }

        unsigned int m_id;
    };
}
