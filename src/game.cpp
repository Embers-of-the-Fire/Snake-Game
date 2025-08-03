#include "inc/game.hpp"

#include <fmt/core.h>
#include <string>

void game::GameHandler::print_frame() const { ui_handler.print_frame(current_frame); }

std::string game::GameHandler::to_string() const {
    return fmt::format(
        "GameHandler(width={}, height={}, current_frame={})", width, height,
        current_frame.to_string());
}

const frame::Frame& game::GameHandler::get_current_frame() const { return current_frame; }
