export module Eqx.TPL.Tests.Explore.Stb_Image;

import <Eqx/std.hpp>;

import Eqx.TPL.Wrapper.glad;
import Eqx.TPL.Wrapper.stb_image;

using namespace std::literals;

export namespace eqx::tpl::tests::explore
{
    class Stb_Image
    {
    public:
        Stb_Image(const Stb_Image&) = default;
        Stb_Image(Stb_Image&&) = default;
        Stb_Image& operator= (const Stb_Image&) = default;
        Stb_Image& operator= (Stb_Image&&) = default;
        ~Stb_Image() = default;

        explicit inline Stb_Image() noexcept
            :
            m_image("Resources/Textures/Brick_Wall.png"sv),
            m_tex(m_image.get_width(), m_image.get_height(), m_image.get_data(),
                m_image.get_channel_count()),
            m_context(
                eqx::tpl::wrapper::glad::Shader_Program::from_files(
                    "Resources/Shaders/Textured_Quad.vs.glsl"sv,
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
                        1u, 2u, 3u }) })
        {
            m_context.set_uniform("tex0", 0);
            this->m_context.set_texture(&m_tex);
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

        eqx::tpl::wrapper::stb_image::Image m_image;
        eqx::tpl::wrapper::glad::Texture m_tex;
        eqx::tpl::wrapper::glad::Context m_context;
    };
}
