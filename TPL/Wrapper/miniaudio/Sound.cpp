// Sound.cpp

export module Eqx.TPL.Wrapper.miniaudio.Sound;

import Eqx.TPL.Wrapper.miniaudio.Engine;

import <Eqx/std.hpp>;
import <Eqx/TPL/miniaudio/miniaudio.hpp>;

using namespace std::literals;

export namespace eqx::tpl::wrapper::miniaudio
{
    class Sound final
    {
    public:
        enum class Flag
        {
            Stream = MA_SOUND_FLAG_STREAM,
            No_Spatialization = MA_SOUND_FLAG_NO_SPATIALIZATION
        };

        Sound() = delete;

        Sound(const Sound&) = default;
        Sound(Sound&&) = default;
        Sound& operator= (const Sound&) = default;
        Sound& operator= (Sound&&) = default;

        explicit inline Sound(Engine& engine,
            const std::filesystem::path& path) noexcept
            :
            m_sound()
        {
            assert(std::filesystem::exists(path));
            [[maybe_unused]] const auto ec = ma_sound_init_from_file(
                &engine.edit_engine(), path.string().c_str(), 0, nullptr,
                nullptr, &this->edit_sound());
            assert(ec == MA_SUCCESS);
        }

        inline ~Sound() noexcept
        {
            ma_sound_uninit(&this->edit_sound());
        }

        inline void start() noexcept
        {
            ma_sound_start(&this->edit_sound());
        }

        [[nodiscard]] inline bool is_playing() noexcept
        {
            return ma_sound_is_playing(&this->edit_sound());
        }

        [[nodiscard]] constexpr const ma_sound& get_sound() const noexcept
        {
            return this->m_sound;
        }

        [[nodiscard]] constexpr ma_sound& edit_sound() noexcept
        {
            return this->m_sound;
        }

    private:
        ma_sound m_sound;
    };
}
