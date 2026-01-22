// Freetype.cpp

export module Eqx.TPL.Tests.Explore.Freetype;

import <Eqx/std.hpp>;

import Eqx.TPL.Wrapper.glad;
import Eqx.TPL.Wrapper.freetype;

using namespace std::literals;

export namespace eqx::tpl::tests::explore
{
    class Freetype final
    {
    public:
        Freetype(const Freetype&) = default;
        Freetype(Freetype&&) = default;
        Freetype& operator= (const Freetype&) = default;
        Freetype& operator= (Freetype&&) = default;
        ~Freetype() = default;

        explicit inline Freetype() noexcept
            :
            m_lib(),
            m_face(m_lib, "Resources/Fonts/Hack-Regular.ttf"),
            m_tex(),
            m_context()
        {
            this->get_face().set_pixel_sizes(1024);
            this->get_face().load_char('Q');

            this->edit_tex().emplace(this->get_face().get_width(),
                this->get_face().get_height(), this->get_face().get_buffer(),
                1);
            this->edit_context().emplace(
                eqx::tpl::wrapper::glad::Shader_Program::from_files(
                    "Resources/Shaders/Textured_Quad.vs.glsl"sv,
                    "Resources/Shaders/Text.fs.glsl"sv),
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
                &this->get_tex().value());

            this->get_context()->set_uniform("tex0", 0);
        }

        inline void run(const char c) noexcept
        {
            this->get_face().load_char(c);

            this->edit_tex().emplace(this->get_face().get_width(),
                this->get_face().get_height(), this->get_face().get_buffer(),
                1);

            this->edit_context()->set_texture(&this->get_tex().value());

            this->get_context()->draw();
        }

    private:
        [[nodiscard]] constexpr const eqx::tpl::wrapper::freetype::FT_Face&
            get_face() const noexcept
        {
            return this->m_face;
        }

        [[nodiscard]] constexpr const
            std::optional<eqx::tpl::wrapper::glad::Texture>&
            get_tex() const noexcept
        {
            return this->m_tex;
        }

        [[nodiscard]] constexpr const
            std::optional<eqx::tpl::wrapper::glad::Context>&
            get_context() const noexcept
        {
            return this->m_context;
        }

        [[nodiscard]] constexpr std::optional<eqx::tpl::wrapper::glad::Texture>&
            edit_tex() noexcept
        {
            return this->m_tex;
        }

        [[nodiscard]] constexpr std::optional<eqx::tpl::wrapper::glad::Context>&
            edit_context() noexcept
        {
            return this->m_context;
        }

        eqx::tpl::wrapper::freetype::FT_Library m_lib;
        eqx::tpl::wrapper::freetype::FT_Face m_face;
        std::optional<eqx::tpl::wrapper::glad::Texture> m_tex;
        std::optional<eqx::tpl::wrapper::glad::Context> m_context;
    };
}
