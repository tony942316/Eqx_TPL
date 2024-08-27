import <Eqx/TPL/stb/stb_image.hpp>;

#include <iostream>

int main()
{
    std::cout << "Start:\n\n";

    stbi_set_flip_vertically_on_load(true);

    std::cout << "\nEnd: ";
    std::cin.get();
    return 0;
}
