#include <fmt/core.h>
#include <iostream>

#include "inc/game.hpp"

#include <cstdint>
#include <thread>

int main(int, char**) {
    std::wcout.imbue(std::locale("en_US.UTF-8")); // Set locale for wide character output

    game::GameHandler game_handler(11, 11);
    game_handler.add_apple({8, 5});

    fmt::print("Game: {}\n", game_handler);

    std::cout << "Hello, world 🍎!" << std::endl;

    game_handler.print_frame();

    int32_t score = 0;

    for (int i = 0; i < 100; ++i) {
        game_handler.next_frame();
        game_handler.print_frame();
        if (game_handler.get_current_frame().score > score) {
            frame::MoveDirection dir;
            do {
                dir = static_cast<frame::MoveDirection>(std::rand() % 4);
            } while (dir == game_handler.get_current_frame().direction);
            game_handler.set_direction(dir);
            score = game_handler.get_current_frame().score;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
