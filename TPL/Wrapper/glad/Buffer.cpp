// Buffer.cpp

export module Eqx.TPL.Wrapper.glad.Buffer;

import <Eqx/std.hpp>;
import <Eqx/TPL/glad/glad.hpp>;

using namespace std::literals;

export namespace eqx::tpl::wrapper::glad
{
    static_assert(std::same_as<GLuint, unsigned int>);
    static_assert(std::same_as<decltype(GL_ARRAY_BUFFER), int>);
    static_assert(std::same_as<decltype(GL_ELEMENT_ARRAY_BUFFER), int>);

    template <int t_buffer>
    class Buffer
    {
    public:
        Buffer(const Buffer&) = delete;
        Buffer& operator= (const Buffer&) = delete;

        explicit inline Buffer(const std::span<const std::conditional_t<
            t_buffer == GL_ARRAY_BUFFER, float, unsigned int>> data) noexcept
            :
            m_id(0u)
        {
            glGenBuffers(1, &m_id);
            assert(this->get_id() != 0u);

            this->enable();
            glBufferData(t_buffer, std::ranges::size(data)
                * sizeof(std::conditional_t<
                    t_buffer == GL_ARRAY_BUFFER, float, unsigned int>),
                std::ranges::data(data), GL_STATIC_DRAW);
        }

        inline Buffer(Buffer&& other) noexcept
            :
            m_id(std::exchange(other.edit_id(), 0u))
        {
        }

        inline Buffer& operator= (Buffer&& other) noexcept
        {
            std::swap(this->edit_id(), other.edit_id());
            return *this;
        }

        inline ~Buffer() noexcept
        {
            glDeleteBuffers(1, &this->edit_id());
        }

        inline void enable() const noexcept
        {
            assert(this->get_id() != 0u);

            glBindBuffer(t_buffer, this->get_id());
        }

        inline void disable() const noexcept
        {
            assert(this->get_id() != 0u);

            glBindBuffer(t_buffer, 0u);
        }

        [[nodiscard]] constexpr GLuint get_id() const noexcept
        {
            return this->m_id;
        }

    private:
        [[nodiscard]] constexpr unsigned int& edit_id() noexcept
        {
            return this->m_id;
        }

        unsigned int m_id;
    };

    using Vertex_Buffer = Buffer<GL_ARRAY_BUFFER>;
    using Index_Buffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;
}
