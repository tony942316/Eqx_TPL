export module Eqx.TPL.Tests.Explore.Glm;

import <Eqx/std.hpp>;

import Eqx.TPL.Wrapper.glad;
import Eqx.TPL.Wrapper.glm;

using namespace std::literals;

export namespace eqx::tpl::tests::explore
{
    class Glm
    {
    public:
        Glm(const Glm&) = default;
        Glm(Glm&&) = default;
        Glm& operator= (const Glm&) = default;
        Glm& operator= (Glm&&) = default;
        ~Glm() = default;

        explicit inline Glm(const int width, const int height) noexcept
            :
            m_context(
                eqx::tpl::wrapper::glad::Shader_Program::from_files(
                    "Resources/Shaders/MVP_Quad.vs.glsl"sv,
                    "Resources/Shaders/Basic.fs.glsl"sv),
                eqx::tpl::wrapper::glad::Vertex_Array{
                    std::to_array({
                        0.5f, 0.5f,
                        0.5f, -0.5f,
                        -0.5f, -0.5f,
                        -0.5f, 0.5f }),
                    std::to_array({ 2u }),
                    std::to_array({
                        0u, 1u, 3u,
                        1u, 2u, 3u }) })
        {
            auto model = eqx::tpl::wrapper::glm::Mat4{ 1.0f };
            model.translate(
                eqx::tpl::wrapper::glm::Vec3{ 100.0f, -100.0f, 0.0f });
            model.scale(eqx::tpl::wrapper::glm::Vec3{ 100.0f, 100.0f, 1.0f });
            auto view = eqx::tpl::wrapper::glm::Mat4{ 1.0f };
            auto projection = eqx::tpl::wrapper::glm::Mat4::ortho(
                0.0f, static_cast<float>(width), -static_cast<float>(height),
                0.0f);

            m_context.set_uniform("model", model.value_ptr());
            m_context.set_uniform("view", view.value_ptr());
            m_context.set_uniform("proj", projection.value_ptr());
        }

        inline void run(const float x, const float y) const noexcept
        {
            auto model = eqx::tpl::wrapper::glm::Mat4{ 1.0f };
            model.translate(eqx::tpl::wrapper::glm::Vec3{ x, -y, 0.0f });
            model.scale(eqx::tpl::wrapper::glm::Vec3{ 100.0f, 100.0f, 1.0f });

            m_context.set_uniform("model", model.value_ptr());

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
