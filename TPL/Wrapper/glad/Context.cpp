// Context.cpp

export module Eqx.TPL.Wrapper.glad.Context;

import <Eqx/std.hpp>;
import <Eqx/TPL/glad/glad.hpp>;

import Eqx.TPL.Wrapper.glad.Shader_Program;
import Eqx.TPL.Wrapper.glad.Vertex_Array;
import Eqx.TPL.Wrapper.glad.Texture;

using namespace std::literals;

export namespace eqx::tpl::wrapper::glad
{
    class Context
    {
    public:
        Context() = default;
        Context(const Context&) = default;
        Context(Context&&) = default;
        Context& operator= (const Context&) = default;
        Context& operator= (Context&&) = default;
        ~Context() = default;

        explicit inline Context(Shader_Program&& sp, Vertex_Array&& va) noexcept
            :
            m_shader_program(std::move(sp)),
            m_vertex_array(std::move(va)),
            m_texture(nullptr)
        {
        }

        explicit inline Context(Shader_Program&& sp, Vertex_Array&& va,
            const Texture* tex) noexcept
            :
            m_shader_program(std::move(sp)),
            m_vertex_array(std::move(va)),
            m_texture(tex)
        {
            assert(this->get_texture() != nullptr);
        }

        inline void draw() const noexcept
        {
            this->get_shader_program().enable();
            this->get_vertex_array().enable();

            if (this->get_texture() != nullptr)
            {
                Texture::active_texture(0);
                this->get_texture()->enable();
            }

            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(
                this->get_vertex_array().get_index_count()), GL_UNSIGNED_INT,
                0);
        }

        inline void set_texture(const Texture* tex) noexcept
        {
            this->edit_texture() = tex;
        }

        template <typename T>
            requires requires (const char* name, const T& value)
                { this->get_shader_program().set_uniform(name, value); }
        inline void set_uniform(const char* name, const T& value) const noexcept
        {
            this->get_shader_program().set_uniform(name, value);
        }

    private:
        [[nodiscard]] constexpr const Shader_Program&
            get_shader_program() const noexcept
        {
            return this->m_shader_program;
        }

        [[nodiscard]] constexpr const Vertex_Array&
            get_vertex_array() const noexcept
        {
            return this->m_vertex_array;
        }

        [[nodiscard]] constexpr const Texture*
            get_texture() const noexcept
        {
            return this->m_texture;
        }

        [[nodiscard]] constexpr Shader_Program& edit_shader_program() noexcept
        {
            return this->m_shader_program;
        }

        [[nodiscard]] constexpr Vertex_Array& edit_vertex_array() noexcept
        {
            return this->m_vertex_array;
        }

        [[nodiscard]] constexpr const Texture*& edit_texture() noexcept
        {
            return this->m_texture;
        }

        Shader_Program m_shader_program;
        Vertex_Array m_vertex_array;
        const Texture* m_texture;
    };
}
