// Main.cpp

import <Eqx/std.hpp>;

import Eqx.TPL.Wrapper.miniaudio;

using namespace std::literals;

inline void run() noexcept
{
    auto engine = eqx::tpl::wrapper::miniaudio::Engine{};
    auto sound = eqx::tpl::wrapper::miniaudio::Sound{ engine,
        "Resources/Sounds/Mario_Coin.mp3"sv };

    sound.start();

    while (sound.is_playing() == true)
    {
        std::this_thread::sleep_for(1s);
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    std::format_to(std::ostream_iterator<char>(std::cout), "Start\n\n"sv);

    run();

    std::format_to(std::ostream_iterator<char>(std::cout), "\nEnd\n"sv);
    return EXIT_SUCCESS;
}
