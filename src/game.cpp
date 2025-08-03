#include "inc/game.hpp"

#include <fmt/core.h>
#include <iostream>
#include <string>

void game::GameHandler::add_apple(const geo::Point& apple) {
    if (std::find(current_frame.apples.begin(), current_frame.apples.end(), apple)
        == current_frame.apples.end()) {
        current_frame.apples.push_back(apple);
    }
}

void game::GameHandler::set_direction(const frame::MoveDirection dir) {
    current_frame.direction = dir;
}

void game::GameHandler::print_frame() const {
    std::cout << "\x1B[2J\x1B[H"; // Clear the console
    std::cout.flush();

    ui_handler.print_frame(current_frame);
    std::cout.flush();
}

void game::GameHandler::next_frame() { current_frame = current_frame.next_frame(graph); }

std::string game::GameHandler::to_string() const {
    return fmt::format(
        "GameHandler(width={}, height={}, current_frame={})", width, height,
        current_frame.to_string());
}

const frame::Frame& game::GameHandler::get_current_frame() const { return current_frame; }
