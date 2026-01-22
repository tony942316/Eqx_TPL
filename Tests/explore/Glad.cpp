export module Eqx.TPL.Tests.Explore.Glad;

import <Eqx/std.hpp>;

import Eqx.TPL.Wrapper.glad;

using namespace std::literals;

export namespace eqx::tpl::tests::explore
{
    class Glad
    {
    public:
        Glad(const Glad&) = default;
        Glad(Glad&&) = default;
        Glad& operator= (const Glad&) = default;
        Glad& operator= (Glad&&) = default;
        ~Glad() = default;

        explicit inline Glad() noexcept
            :
            m_context(
            eqx::tpl::wrapper::glad::Shader_Program::from_files(
                "Resources/Shaders/Basic.vs.glsl"sv,
                "Resources/Shaders/Basic.fs.glsl"sv),
            eqx::tpl::wrapper::glad::Vertex_Array{
                std::to_array({
                    0.5f, 0.5f, 0.0f,
                    0.5f, -0.5f, 0.0f,
                    -0.5f, -0.5f, 0.0f,
                    -0.5f, 0.5f, 0.0f }),
                std::to_array({ 3u }),
                std::to_array({
                    0u, 1u, 3u,
                    1u, 2u, 3u }) })
        {
        }

        inline void run() const noexcept
        {
            this->get_context().draw();
        }

    private:
        [[nodiscard]] constexpr const eqx::tpl::wrapper::glad::Context&
            get_context() const noexcept
        {
            return this->m_context;
        }

        eqx::tpl::wrapper::glad::Context m_context;
    };
}
