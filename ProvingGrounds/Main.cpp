import <Eqx/TPL/stb/stb_image.hpp>;

#include <iostream>

int main()
{
    stbi_set_flip_vertically_on_load(true);
    std::cout << "Hello World\n";
    return 0;
}
