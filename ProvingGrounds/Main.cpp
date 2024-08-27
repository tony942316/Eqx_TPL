import Eqx.TPL.Tests;

#include <iostream>

int main()
{
    std::cout << "Start:\n\n";

    tests::run();

    std::cout << "\nEnd: ";

#ifdef __linux__
    std::cout << '\n';
#endif // __linux__

#ifdef _WIN32
    std::cin.get();
#endif // _WIN32
    return 0;
}
