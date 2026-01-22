export module Eqx.TPL.Tests.Explore.Glm_Image;

import <Eqx/std.hpp>;

import Eqx.TPL.Wrapper.glad;
import Eqx.TPL.Wrapper.stb_image;
import Eqx.TPL.Wrapper.glm;

using namespace std::literals;

export namespace eqx::tpl::tests::explore
{
    class Glm_Image
    {
    public:
        Glm_Image(const Glm_Image&) = default;
        Glm_Image(Glm_Image&&) = default;
        Glm_Image& operator= (const Glm_Image&) = default;
        Glm_Image& operator= (Glm_Image&&) = default;
        ~Glm_Image() = default;

        explicit inline Glm_Image(const int width, const int height) noexcept
            :
            m_image("Resources/Textures/Brick_Wall.png"sv),
            m_tex(m_image.get_width(), m_image.get_height(), m_image.get_data(),
                m_image.get_channel_count()),
            m_context(
                eqx::tpl::wrapper::glad::Shader_Program::from_files(
                    "Resources/Shaders/MVP_Textured_Quad.vs.glsl"sv,
                    "Resources/Shaders/Textured_Quad.fs.glsl"sv),
                eqx::tpl::wrapper::glad::Vertex_Array{
                    std::to_array({
                        0.5f, 0.5f, 1.0f, 0.0f,
                        0.5f, -0.5f, 1.0f, 1.0f,
                        -0.5f, -0.5f, 0.0f, 1.0f,
                        -0.5f, 0.5f, 0.0f, 0.0f }),
                    std::to_array({ 2u, 2u }),
                    std::to_array({
                        0u, 1u, 3u,
                        1u, 2u, 3u }) },
                &m_tex)
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

            m_context.set_uniform("tex0", 0);
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

        eqx::tpl::wrapper::stb_image::Image m_image;
        eqx::tpl::wrapper::glad::Texture m_tex;
        eqx::tpl::wrapper::glad::Context m_context;
    };
}
