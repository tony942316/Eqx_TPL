export module Eqx.TPL.Tests.Lib.Frame_Timer;

import <Eqx/std.hpp>;

using namespace std::literals;

export namespace eqx::tpl::tests::lib
{
    class Frame_Timer
    {
    public:
        Frame_Timer() = default;
        Frame_Timer(const Frame_Timer&) = default;
        Frame_Timer(Frame_Timer&&) = default;
        Frame_Timer& operator= (const Frame_Timer&) = default;
        Frame_Timer& operator= (Frame_Timer&&) = default;
        ~Frame_Timer() = default;

        inline void start() noexcept
        {
            this->edit_fps() = 0.0f;
            this->edit_frames() = 0ull;
            this->edit_start() = std::chrono::steady_clock::now();
        }

        inline void end() noexcept
        {
            ++this->edit_frames();
            const auto end = std::chrono::steady_clock::now();
            if ((end - this->get_start()) > 1'000ms) [[unlikely]]
            {
                this->edit_fps() = (this->get_frames() * 1'000.0f)
                    / std::chrono::duration_cast<std::chrono::milliseconds>(
                        end - this->get_start()).count();

                this->edit_frames() = 0ull;
                this->edit_start() = end;
            }
        }

        [[nodiscard]] constexpr float get_fps() const noexcept
        {
            return this->m_fps;
        }

        [[nodiscard]] constexpr unsigned long long get_frames() const noexcept
        {
            return this->m_frames;
        }

    private:
        [[nodiscard]] constexpr const
            std::chrono::time_point<std::chrono::steady_clock>&
            get_start() const noexcept
        {
            return this->m_start;
        }

        [[nodiscard]] constexpr float& edit_fps() noexcept
        {
            return this->m_fps;
        }

        [[nodiscard]] constexpr unsigned long long& edit_frames() noexcept
        {
            return this->m_frames;
        }

        [[nodiscard]] constexpr std::chrono::time_point<std::chrono::steady_clock>&
            edit_start() noexcept
        {
            return this->m_start;
        }

        float m_fps;
        unsigned long long m_frames;
        std::chrono::time_point<std::chrono::steady_clock> m_start;
    };
}
