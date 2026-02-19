export module Eqx.TPL.Tests.Explore.Miniaudio;

import <Eqx/std.hpp>;

import Eqx.TPL.Wrapper.miniaudio;

using namespace std::literals;

export namespace eqx::tpl::tests::explore
{
    class Miniaudio final
    {
    public:
        Miniaudio(const Miniaudio&) = default;
        Miniaudio(Miniaudio&&) = default;
        Miniaudio& operator= (const Miniaudio&) = default;
        Miniaudio& operator= (Miniaudio&&) = default;
        ~Miniaudio() = default;

        explicit inline Miniaudio() noexcept
            :
            m_engine(),
            m_sound(m_engine, "Resources/Sounds/Mario_Coin.mp3"sv)
        {
            this->edit_sound().set_looping(true);
        }

        inline void run() noexcept
        {
            if (this->edit_sound().is_playing() == false)
            {
                this->edit_sound().start();
            }
        }

    private:
        [[nodiscard]] constexpr eqx::tpl::wrapper::miniaudio::Sound&
            edit_sound() noexcept
        {
            return this->m_sound;
        }

        eqx::tpl::wrapper::miniaudio::Engine m_engine;
        eqx::tpl::wrapper::miniaudio::Sound m_sound;
    };
}
