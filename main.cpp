#include <fmt/core.h>
#include <iostream>

#include "inc/game.hpp"

int main(int, char**) {
    std::wcout.imbue(std::locale("en_US.UTF-8")); // Set locale for wide character output

    const game::GameHandler game_handler(11, 11);

    fmt::print("Game: {}\n", game_handler);

    std::cout << "Hello, world 🍎!" << std::endl;

    game_handler.print_frame();
}
