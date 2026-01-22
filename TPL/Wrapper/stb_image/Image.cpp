// Image.cpp

export module Eqx.TPL.Wrapper.stb_image.Image;

import <Eqx/std.hpp>;

import <Eqx/TPL/stb/stb_image.hpp>;

using namespace std::literals;

export namespace eqx::tpl::wrapper::stb_image
{
    class Image
    {
    public:
        Image(const Image&) = delete;
        Image& operator= (const Image&) = delete;

        explicit inline Image(const std::filesystem::path& path) noexcept
            :
            m_width(0),
            m_height(0),
            m_channel_count(0),
            m_data(stbi_load(path.string().c_str(), &this->edit_width(),
                &this->edit_height(), &this->edit_channel_count(), 0))
        {
            assert(std::invoke([data = this->get_data()]() noexcept -> bool
                {
                    if (data == nullptr) [[unlikely]]
                    {
                        std::format_to(std::ostream_iterator<char>(std::cerr),
                            "stb_image Load Failure: {}\n"sv,
                            stbi_failure_reason());
                    }
                    return data != nullptr;
                }));
        }

        inline Image(Image&& other) noexcept
            :
            m_width(std::exchange(other.edit_width(), 0)),
            m_height(std::exchange(other.edit_height(), 0)),
            m_channel_count(std::exchange(other.edit_channel_count(), 0)),
            m_data(std::exchange(other.edit_data(), nullptr))
        {
            assert(this->get_data() != nullptr);
        }

        inline Image& operator= (Image&& other) noexcept
        {
            assert(this != &other);

            std::ranges::swap(this->edit_width(), other.edit_width());
            std::ranges::swap(this->edit_height(), other.edit_height());
            std::ranges::swap(this->edit_channel_count(),
                other.edit_channel_count());
            std::ranges::swap(this->edit_data(), other.edit_data());

            return *this;
        }

        inline ~Image() noexcept
        {
            stbi_image_free(this->get_data());
        }

        [[nodiscard]] constexpr int get_width() const noexcept
        {
            return this->m_width;
        }

        [[nodiscard]] constexpr int get_height() const noexcept
        {
            return this->m_height;
        }

        [[nodiscard]] constexpr int get_channel_count() const noexcept
        {
            return this->m_channel_count;
        }

        [[nodiscard]] constexpr unsigned char* const get_data() const noexcept
        {
            return this->m_data;
        }

    private:
        [[nodiscard]] constexpr int& edit_width() noexcept
        {
            return this->m_width;
        }

        [[nodiscard]] constexpr int& edit_height() noexcept
        {
            return this->m_height;
        }

        [[nodiscard]] constexpr int& edit_channel_count() noexcept
        {
            return this->m_channel_count;
        }

        [[nodiscard]] constexpr unsigned char*& edit_data() noexcept
        {
            return this->m_data;
        }

        int m_width;
        int m_height;
        int m_channel_count;
        unsigned char* m_data;
    };
}
