// Texture.cpp

export module Eqx.TPL.Wrapper.glad.Texture;

import <Eqx/std.hpp>;
import <Eqx/TPL/glad/glad.hpp>;

using namespace std::literals;

export namespace eqx::tpl::wrapper::glad
{
    static_assert(std::same_as<GLuint, unsigned int>);

    class Texture
    {
    public:
        Texture(const Texture&) = delete;
        Texture& operator= (const Texture&) = delete;

        explicit inline Texture(const int width, const int height,
            const unsigned char* const data, const int channels) noexcept
            :
            m_id(0u)
        {
            assert(channels == 1 || channels == 3 || channels == 4);

            glGenTextures(1, &this->edit_id());
            assert(this->get_id() != 0u);

            this->enable();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            auto src_format = GL_RED;
            auto internal_format = GL_R8;
            switch (channels)
            {
            case 1:
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                break;
            case 3:
                src_format = GL_RGB;
                internal_format = GL_RGB8;
                break;
            case 4:
                src_format = GL_RGBA;
                internal_format = GL_RGBA8;
                break;
            }

            glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0,
                src_format, GL_UNSIGNED_BYTE, data);
        }

        inline Texture(Texture&& other) noexcept
            :
            m_id(std::exchange(other.edit_id(), 0u))
        {
            assert(this->get_id() != 0u);
        }

        inline Texture& operator= (Texture&& other) noexcept
        {
            assert(this != &other);

            std::ranges::swap(this->edit_id(), other.edit_id());

            return *this;
        }

        inline ~Texture() noexcept
        {
            glDeleteTextures(1, &this->edit_id());
        }

        inline void enable() const noexcept
        {
            glBindTexture(GL_TEXTURE_2D, this->get_id());
        }

        inline void disable() const noexcept
        {
            glBindTexture(GL_TEXTURE_2D, 0u);
        }

        [[nodiscard]] unsigned int get_id() const noexcept
        {
            return this->m_id;
        }

        static inline void active_texture(const int i) noexcept
        {
            assert(i >= 0 && i <= 16);
            glActiveTexture(GL_TEXTURE0 + i);
        }

    private:
        [[nodiscard]] unsigned int& edit_id() noexcept
        {
            return this->m_id;
        }

        unsigned int m_id;
    };
}
