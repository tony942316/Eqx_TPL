// Main.cpp

import <Eqx/std.hpp>;

import Eqx.TPL.Tests.Explore;

using namespace std::literals;

// 1920 x 1080
// 2560 x 1440
// 4096 x 2160

/*
namespace eqx::exp
{
    class Key_Press final
    {
    public:
        Key_Press() = default;
        Key_Press(const Key_Press&) = default;
        Key_Press(Key_Press&&) = default;
        Key_Press& operator= (const Key_Press&) = default;
        Key_Press& operator= (Key_Press&&) = default;
        ~Key_Press() = default;

        explicit constexpr Key_Press(
            const eqx::tpl::wrapper::glfw::Key key) noexcept
            :
            m_key(key);
        {
        }

        [[nodiscard]] constexpr eqx::tpl::wrapper::glfw::Key
            get_key() const noexcept
        {
            return this->m_key;
        }

    private:
        eqx::tpl::wrapper::glfw::Key m_key;
    };

    class Event_Listener final
    {
    public:
        Event_Listener() = default;
        Event_Listener(const Event_Listener&) = default;
        Event_Listener(Event_Listener&&) = default;
        Event_Listener& operator= (const Event_Listener&) = default;
        Event_Listener& operator= (Event_Listener&&) = default;
        ~Event_Listener() = default;

        [[nodiscard]] inline Key_Press pop() noexcept
        {
            auto result = Key_Press{ this->get_queue().front() };
            this->edit_queue().pop();
            return result;
        }

    private:
        [[nodiscard]] constexpr const std::queue<Key_Press>&
            get_queue() const noexcept
        {
            return this->m_queue;
        }

        [[nodiscard]] constexpr std::queue<Key_Press>& edit_queue() noexcept
        {
            return this->m_queue;
        }

        std::queue<Key_Press> m_queue;
    };
}
*/


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::format_to(std::ostream_iterator<char>(std::cout), "Start\n\n"sv);

    eqx::tpl::tests::Explore::run();

    std::format_to(std::ostream_iterator<char>(std::cout), "\nEnd\n"sv);
    return EXIT_SUCCESS;
}
