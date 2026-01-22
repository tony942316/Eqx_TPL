// FT_Library.cpp

export module Eqx.TPL.Wrapper.freetype.FT_Library;

import <Eqx/std.hpp>;

import <Eqx/TPL/freetype/freetype.hpp>;

using namespace std;

export namespace eqx::tpl::wrapper::freetype
{
    class FT_Library final
    {
    public:
        FT_Library(const FT_Library&) = delete;
        FT_Library(FT_Library&&) = delete;
        FT_Library& operator= (const FT_Library&) = delete;
        FT_Library& operator= (FT_Library&&) = delete;

        explicit inline FT_Library() noexcept
            :
            m_lib()
        {
            [[maybe_unused]] const auto ec =
                FT_Init_FreeType(&this->edit_lib());
            assert(ec == 0);
        }

        inline ~FT_Library() noexcept
        {
            FT_Done_FreeType(this->get_lib());
        }

        [[nodiscard]] constexpr const ::FT_Library& get_lib() const noexcept
        {
            return this->m_lib;
        }

    private:
        [[nodiscard]] constexpr ::FT_Library& edit_lib() noexcept
        {
            return this->m_lib;
        }

        ::FT_Library m_lib;
    };
}
