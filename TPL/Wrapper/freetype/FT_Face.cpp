// FT_Face.cpp

export module Eqx.TPL.Wrapper.freetype.FT_Face;

import Eqx.TPL.Wrapper.freetype.FT_Library;

import <Eqx/std.hpp>;

import <Eqx/TPL/freetype/freetype.hpp>;

using namespace std;

export namespace eqx::tpl::wrapper::freetype
{
    class FT_Face final
    {
    public:
        FT_Face() = delete;
        FT_Face(const FT_Face&) = delete;
        FT_Face(FT_Face&&) = delete;
        FT_Face& operator= (const FT_Face&) = delete;
        FT_Face& operator= (FT_Face&&) = delete;

        explicit inline FT_Face(const FT_Library& lib,
            const char* const font) noexcept
            :
            m_face()
        {
            [[maybe_unused]] const auto ec =
                FT_New_Face(lib.get_lib(), font, 0, &this->edit_face());
            assert(ec == 0);
        }

        inline ~FT_Face() noexcept
        {
            FT_Done_Face(this->get_face());
        }

        inline void set_pixel_sizes(const int pixels) const noexcept
        {
            [[maybe_unused]] const auto ec =
                FT_Set_Pixel_Sizes(this->get_face(), 0, pixels);
            assert(ec == 0);
        }

        inline void load_char(const char c) const noexcept
        {
            [[maybe_unused]] const auto ec =
                FT_Load_Char(this->get_face(), c, FT_LOAD_RENDER);
            assert(ec == 0);
        }

        [[nodiscard]] inline int get_width() const noexcept
        {
            return this->get_face()->glyph->bitmap.width;
        }

        [[nodiscard]] inline int get_height() const noexcept
        {
            return this->get_face()->glyph->bitmap.rows;
        }

        [[nodiscard]] const unsigned char* get_buffer() const noexcept
        {
            return this->get_face()->glyph->bitmap.buffer;
        }

        [[nodiscard]] constexpr const ::FT_Face& get_face() const noexcept
        {
            return this->m_face;
        }

    private:
        [[nodiscard]] constexpr ::FT_Face& edit_face() noexcept
        {
            return this->m_face;
        }

        ::FT_Face m_face;
    };
}
