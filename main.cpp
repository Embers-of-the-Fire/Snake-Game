#include <fmt/core.h>
#include <iostream>

#include "inc/game.hpp"

int main(int, char**) {
    const game::GameHandler game_handler(60, 60);

    fmt::print("Game: {}\n", game_handler);
}
