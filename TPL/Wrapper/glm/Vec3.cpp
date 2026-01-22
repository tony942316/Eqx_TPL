// Vec3.cpp

export module Eqx.TPL.Wrapper.glm.Vec3;

import <Eqx/std.hpp>;

import <Eqx/TPL/glm/glm.hpp>;

using namespace std::literals;

export namespace eqx::tpl::wrapper::glm
{
    class Vec3
    {
    public:
        Vec3() = default;
        Vec3(const Vec3&) = default;
        Vec3(Vec3&&) = default;
        Vec3& operator= (const Vec3&) = default;
        Vec3& operator= (Vec3&&) = default;
        ~Vec3() = default;

        explicit inline Vec3(const float x, const float y,
            const float z) noexcept
            :
            m_vec(x, y, z)
        {
        }

        [[nodiscard]] constexpr const ::glm::vec3& get_vec() const noexcept
        {
            return this->m_vec;
        }

    private:
        ::glm::vec3 m_vec;
    };
}
