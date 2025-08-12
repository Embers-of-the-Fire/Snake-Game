#include <fmt/core.h>
#include <iostream>

#include "inc/ai.hpp"
#include "inc/frame.hpp"
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

    for (int i = 0; i < 1000; ++i) {
        if (auto dir = ai::next_move_astar(game_handler.get_current_frame())) {
            game_handler.set_direction(*dir);
        }
        const auto validity = game_handler.next_frame();
        if (validity != frame::FrameValidity::Valid) {
            std::cout << "\x1B[2J\x1B[H";         // Clear the console
            std::cout << "Game Over: " << frame::describe_validity(validity) << std::endl;
            break;
        }
        game_handler.print_frame();
        if (game_handler.get_current_frame().score > score) {
            frame::MoveDirection dir;
            score = game_handler.get_current_frame().score;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
