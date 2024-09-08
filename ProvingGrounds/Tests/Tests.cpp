export module Eqx.TPL.Tests;

import <Stdlib.hpp>;

import Eqx.TPL.Tests.Glfw;
import Eqx.TPL.Tests.Glad;
import Eqx.TPL.Tests.Stb_Image;
import Eqx.TPL.Tests.Glm;
import Eqx.TPL.Tests.FreeType;

namespace tests
{
    enum class State : std::int8_t
    {
        None = 0,
        Glfw = 1,
        Glad = 2,
        Stb_Image = 3,
        Glm = 4,
        FreeType = 5,
        Exit = -1
    };

    // NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
    constinit auto s_State = State::None;
    // NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

    export inline void run() noexcept;
}

namespace tests
{
    inline void run() noexcept
    {
        auto input = 0;
        while (s_State != State::Exit)
        {
            std::cout << "===========Menu===========\n";
            std::cout << "1) glfw Test\n";
            std::cout << "2) glad Test\n";
            std::cout << "3) stb_image Test\n";
            std::cout << "4) glm Test\n";
            std::cout << "5) freetype Test\n";
            std::cout << "-1) Exit\n";
            std::cout << "==========================\n";
            std::cout << "Input: ";
            std::cin >> input;
            s_State = static_cast<State>(input);

            switch (s_State)
            {
            case State::Glfw:
                tests::glfw::run();
                break;
            case State::Glad:
                tests::glad::run();
                break;
            case State::Stb_Image:
                tests::stb_image::run();
                break;
            case State::Glm:
                tests::glm::run();
                break;
            case State::FreeType:
                tests::freetype::run();
                break;
            case State::Exit:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << input << " Is An Invalid Input\n";
                break;
            }
            std::cout << "\n";
        }
    }
}
