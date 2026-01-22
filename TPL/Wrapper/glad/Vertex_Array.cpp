// Vertex_Array.cpp

export module Eqx.TPL.Wrapper.glad.Vertex_Array;

import <Eqx/std.hpp>;
import <Eqx/TPL/glad/glad.hpp>;

import Eqx.TPL.Wrapper.glad.Buffer;

using namespace std::literals;

export namespace eqx::tpl::wrapper::glad
{
    static_assert(std::same_as<GLuint, unsigned int>);

    class Vertex_Array
    {
    public:
        Vertex_Array() = delete;
        Vertex_Array(const Vertex_Array&) = delete;
        Vertex_Array& operator= (const Vertex_Array&) = delete;

        explicit inline Vertex_Array(const std::span<const float> vertex_data,
            const std::span<const unsigned int> attribs,
            const std::span<const unsigned int> index_data) noexcept
            :
            m_id(0u),
            m_vertex_buffer(vertex_data),
            m_index_buffer(index_data)
        {
            glGenVertexArrays(1, &this->edit_id());
            assert(this->get_id() != 0u);

            this->enable();

            assert(std::ranges::size(attribs) <= 8);

            const auto sum = std::reduce(std::ranges::begin(attribs),
                std::ranges::end(attribs));
            auto p_sums = std::array<unsigned int, 8>{};
            std::exclusive_scan(std::ranges::begin(attribs),
                std::ranges::end(attribs), std::ranges::begin(p_sums), 0);

            for (auto i = 0; i < std::ranges::size(attribs); ++i)
            {
                glEnableVertexAttribArray(i);
                glVertexAttribPointer(i, attribs[i], GL_FLOAT, GL_FALSE,
                    sum * sizeof(float), (void*)(p_sums.at(i) * sizeof(float)));
            }

            this->get_index_buffer().enable();
            this->edit_index_count() = std::ranges::size(index_data);
        }

        inline Vertex_Array(Vertex_Array&& other) noexcept
            :
            m_id(std::exchange(other.edit_id(), 0u)),
            m_index_count(std::exchange(
                other.edit_index_count(), std::size_t{ 0 })),
            m_vertex_buffer(std::move(other.edit_vertex_buffer())),
            m_index_buffer(std::move(other.edit_index_buffer()))
        {
        }

        inline Vertex_Array& operator= (Vertex_Array&& other) noexcept
        {
            std::swap(this->edit_id(), other.edit_id());
            std::swap(this->edit_index_count(), other.edit_index_count());
            this->edit_vertex_buffer() = std::move(other.edit_vertex_buffer());
            this->edit_index_buffer() = std::move(other.edit_index_buffer());

            return *this;
        }

        inline ~Vertex_Array() noexcept
        {
            glDeleteVertexArrays(1, &this->edit_id());
        }

        inline void enable() const noexcept
        {
            assert(this->get_id() != 0u);

            glBindVertexArray(this->get_id());
        }

        inline void disable() const noexcept
        {
            assert(this->get_id() != 0u);

            glBindVertexArray(0u);
        }

        [[nodiscard]] constexpr unsigned int get_id() const noexcept
        {
            return this->m_id;
        }

        [[nodiscard]] constexpr std::size_t get_index_count() const noexcept
        {
            return this->m_index_count;
        }

    private:
        [[nodiscard]] constexpr const Vertex_Buffer&
            get_vertex_buffer() const noexcept
        {
            return this->m_vertex_buffer;
        }

        [[nodiscard]] constexpr const Index_Buffer&
            get_index_buffer() const noexcept
        {
            return this->m_index_buffer;
        }

        [[nodiscard]] constexpr unsigned int& edit_id() noexcept
        {
            return this->m_id;
        }

        [[nodiscard]] constexpr std::size_t& edit_index_count() noexcept
        {
            return this->m_index_count;
        }

        [[nodiscard]] constexpr Vertex_Buffer& edit_vertex_buffer() noexcept
        {
            return this->m_vertex_buffer;
        }

        [[nodiscard]] constexpr Index_Buffer& edit_index_buffer() noexcept
        {
            return this->m_index_buffer;
        }

        unsigned int m_id;
        std::size_t m_index_count;

        Vertex_Buffer m_vertex_buffer;
        Index_Buffer m_index_buffer;
    };
}
