// Mat4.cpp

export module Eqx.TPL.Wrapper.glm.Mat4;

import Eqx.TPL.Wrapper.glm.Vec3;

import <Eqx/std.hpp>;

import <Eqx/TPL/glm/glm.hpp>;

using namespace std::literals;

export namespace eqx::tpl::wrapper::glm
{
    class Mat4
    {
    public:
        Mat4() = default;
        Mat4(const Mat4&) = default;
        Mat4(Mat4&&) = default;
        Mat4& operator= (const Mat4&) = default;
        Mat4& operator= (Mat4&&) = default;
        ~Mat4() = default;

        explicit inline Mat4(const float v) noexcept
            :
            m_mat(v)
        {
        }

        inline void translate(const Vec3& vec) noexcept
        {
            this->edit_mat() = ::glm::translate(this->get_mat(), vec.get_vec());
        }

        inline void scale(const Vec3& vec) noexcept
        {
            this->edit_mat() = ::glm::scale(this->get_mat(), vec.get_vec());
        }

        [[nodiscard]] constexpr const float* value_ptr() const noexcept
        {
            return &this->get_mat()[0][0];
        }

        [[nodiscard]] constexpr const ::glm::mat4& get_mat() const noexcept
        {
            return this->m_mat;
        }

        [[nodiscard]] inline static Mat4 ortho(const float x1, const float x2,
            const float y1, const float y2) noexcept
        {
            auto result = Mat4{};
            result.edit_mat() = ::glm::ortho(x1, x2, y1, y2);
            return result;
        }

    private:
        [[nodiscard]] constexpr ::glm::mat4& edit_mat() noexcept
        {
            return this->m_mat;
        }

        ::glm::mat4 m_mat;
    };
}
