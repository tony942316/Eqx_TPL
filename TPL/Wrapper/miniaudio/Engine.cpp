// Engine.cpp

export module Eqx.TPL.Wrapper.miniaudio.Engine;

import <Eqx/std.hpp>;
import <Eqx/TPL/miniaudio/miniaudio.hpp>;

using namespace std::literals;

export namespace eqx::tpl::wrapper::miniaudio
{
    class Engine final
    {
    public:
        Engine(const Engine&) = default;
        Engine(Engine&&) = default;
        Engine& operator= (const Engine&) = default;
        Engine& operator= (Engine&&) = default;

        explicit inline Engine() noexcept
            :
            m_engine()
        {
            [[maybe_unused]] const auto ec = ma_engine_init(nullptr,
                &this->edit_engine());
            assert(ec == MA_SUCCESS);
        }

        inline ~Engine() noexcept
        {
            ma_engine_uninit(&this->edit_engine());
        }

        inline void start() noexcept
        {
            ma_engine_start(&this->edit_engine());
        }

        inline bool is_started() noexcept
        {
            auto device = ma_engine_get_device(&this->edit_engine());
            assert(device != nullptr);
            return ma_device_is_started(device);
        }

        [[nodiscard]] constexpr const ma_engine& get_engine() const noexcept
        {
            return this->m_engine;
        }

        [[nodiscard]] constexpr ma_engine& edit_engine() noexcept
        {
            return this->m_engine;
        }

    private:
        ma_engine m_engine;
    };
}
