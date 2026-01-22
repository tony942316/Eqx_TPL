// Glm_Freetype.cpp

export module Eqx.TPL.Tests.Explore.Glm_Freetype;

import <Eqx/std.hpp>;

import Eqx.TPL.Wrapper.glad;
import Eqx.TPL.Wrapper.glm;
import Eqx.TPL.Wrapper.freetype;

using namespace std::literals;

class Atlas final
{
public:
    struct Glyph final
    {
        eqx::tpl::wrapper::glad::Texture tex;
        float width;
        float height;
        float bitmap_left;
        float bitmap_top;
        float advance;
    };

    Atlas() = delete;

    Atlas(const Atlas&) = default;
    Atlas(Atlas&&) = default;
    Atlas& operator= (const Atlas&) = default;
    Atlas& operator= (Atlas&&) = default;
    ~Atlas() = default;

    explicit inline Atlas(const char* const font, const int size) noexcept
        :
        m_lib(),
        m_face(m_lib, font)
    {
        this->get_face().set_pixel_sizes(size);

        this->add_glyphs("ABCDEFGHIJKLMNOPQRSTUVWXYZ"sv
            "abcdefghijklmnopqrstuvwxyz"sv
            " ~`!@#$%^&*()_-+={[}]|\\:;\"'<,>.?/"sv);
    }

    [[nodiscard]] inline const Glyph& get_glyph(const char c) const noexcept
    {
        return this->get_atlas().at(c);
    }

private:
    inline void add_glyphs(const std::string_view str) noexcept
    {
        for (const auto c : str)
        {
            this->add_glyph(c);
        }
    }

    inline void add_glyph(const char c) noexcept
    {
        this->get_face().load_char(c);

        this->edit_atlas().emplace(std::make_pair(c, Glyph{
            eqx::tpl::wrapper::glad::Texture{
                this->get_face().get_width(), this->get_face().get_height(),
                this->get_face().get_buffer(), 1 },
            static_cast<float>(this->get_face().get_width()),
            static_cast<float>(this->get_face().get_height()),
            static_cast<float>(this->get_face().get_face()->glyph->bitmap_left),
            static_cast<float>(this->get_face().get_face()->glyph->bitmap_top),
            static_cast<float>(
                this->get_face().get_face()->glyph->advance.x >> 6) }));
    }

    [[nodiscard]] constexpr const eqx::tpl::wrapper::freetype::FT_Face&
        get_face() const noexcept
    {
        return this->m_face;
    }

    [[nodiscard]] constexpr const std::unordered_map<char, Glyph>&
        get_atlas() const noexcept
    {
        return this->m_atlas;
    }

    [[nodiscard]] constexpr eqx::tpl::wrapper::freetype::FT_Face&
        edit_face() noexcept
    {
        return this->m_face;
    }

    [[nodiscard]] constexpr std::unordered_map<char, Glyph>&
        edit_atlas() noexcept
    {
        return this->m_atlas;
    }

    eqx::tpl::wrapper::freetype::FT_Library m_lib;
    eqx::tpl::wrapper::freetype::FT_Face m_face;
    std::unordered_map<char, Glyph> m_atlas;
};

export namespace eqx::tpl::tests::explore
{
    class Glm_Freetype final
    {
    public:
        Glm_Freetype(const Glm_Freetype&) = default;
        Glm_Freetype(Glm_Freetype&&) = default;
        Glm_Freetype& operator= (const Glm_Freetype&) = default;
        Glm_Freetype& operator= (Glm_Freetype&&) = default;
        ~Glm_Freetype() = default;

        explicit inline Glm_Freetype(const int width, const int height) noexcept
            :
            m_context(
                eqx::tpl::wrapper::glad::Shader_Program::from_files(
                    "Resources/Shaders/MVP_Textured_Quad.vs.glsl"sv,
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
                        1u, 2u, 3u }) }),
            m_atlas("Resources/Fonts/Hack-Regular.ttf", 64)
        {
            auto model = eqx::tpl::wrapper::glm::Mat4{ 1.0f };
            model.translate(
                eqx::tpl::wrapper::glm::Vec3{ 100.0f, -100.0f, 0.0f });
            model.scale(eqx::tpl::wrapper::glm::Vec3{ 100.0f, 100.0f, 1.0f });
            auto view = eqx::tpl::wrapper::glm::Mat4{ 1.0f };
            auto projection = eqx::tpl::wrapper::glm::Mat4::ortho(
                0.0f, static_cast<float>(width), -static_cast<float>(height),
                0.0f);

            this->get_context().set_uniform("model", model.value_ptr());
            this->get_context().set_uniform("view", view.value_ptr());
            this->get_context().set_uniform("proj", projection.value_ptr());

            this->get_context().set_uniform("tex0", 0);
        }

        inline void run(const char c, const float x, const float y) noexcept
        {
            this->draw_char(c, x, -y);

            this->draw_string("abcdefghijklmnopqrstuvwxyz"sv, 500.0f, -300.0f);
            this->draw_string("ABCDEFGHIJKLMNOPQRSTUVWXYZ"sv, 500.0f, -400.0f);
            this->draw_string("Hello World!"sv, 500.0f, -500.0f);
            this->draw_string("Goodbye World!"sv, 500.0f, -600.0f);
            this->draw_string("The quick brown fox jumps over the lazy dog"sv,
                500.0f, -700.0f);
            this->draw_string("~`!@#$%^&*()_-+={[}]|\\:;\"'<,>.?/"sv, 500.0f,
                -800.0f);
        }

    private:
        inline float draw_char(const char c, const float x,
            const float y) noexcept
        {
            const auto& glyph = this->get_atlas().get_glyph(c);

            const auto x_offset = glyph.bitmap_left;
            const auto y_offset = glyph.height - glyph.bitmap_top;

            auto model = eqx::tpl::wrapper::glm::Mat4{ 1.0f };
            model.translate(eqx::tpl::wrapper::glm::Vec3{ x + x_offset,
                y + (glyph.height / 2.0f) - y_offset, 0.0f });
            model.scale(eqx::tpl::wrapper::glm::Vec3{
                glyph.width, glyph.height, 1.0f });

            this->get_context().set_uniform("model", model.value_ptr());

            this->edit_context().set_texture(&glyph.tex);

            this->get_context().draw();

            return glyph.advance;
        }

        inline void draw_string(const std::string_view str, const float x,
            const float y) noexcept
        {
            auto advance = 0.0f;

            for (int i = 0; i < std::ranges::size(str); ++i)
            {
                advance += this->draw_char(str[i], x + advance, y);
            }
        }

        [[nodiscard]] constexpr const eqx::tpl::wrapper::glad::Context&
            get_context() const noexcept
        {
            return this->m_context;
        }

        [[nodiscard]] constexpr const Atlas& get_atlas() const noexcept
        {
            return this->m_atlas;
        }

        [[nodiscard]] constexpr eqx::tpl::wrapper::glad::Context&
            edit_context() noexcept
        {
            return this->m_context;
        }

        eqx::tpl::wrapper::glad::Context m_context;
        Atlas m_atlas;
    };
}
