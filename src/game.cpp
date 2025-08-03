#include "inc/game.hpp"
#include <algorithm>

#include <fmt/core.h>
#include <string>

game::Frame game::Frame::next_frame() const {
    Frame next_frame(*this);

    // Update snake head position based on direction
    switch (direction) {
    case MoveDirection::UP:
        next_frame.snake_head = geo::GeoGraph(width, height).get_top_of(snake_head);
        break;
    case MoveDirection::DOWN:
        next_frame.snake_head = geo::GeoGraph(width, height).get_bottom_of(snake_head);
        break;
    case MoveDirection::LEFT:
        next_frame.snake_head = geo::GeoGraph(width, height).get_left_of(snake_head);
        break;
    case MoveDirection::RIGHT:
        next_frame.snake_head = geo::GeoGraph(width, height).get_right_of(snake_head);
        break;
    }

    if (std::find(next_frame.apples.begin(), next_frame.apples.end(), next_frame.snake_head)
        != next_frame.apples.end()) {
        next_frame.apples.erase(
            std::remove(next_frame.apples.begin(), next_frame.apples.end(), next_frame.snake_head),
            next_frame.apples.end());
    } else if (next_frame.snake_body.size() > 1) {
        next_frame.snake_body.pop_back(); // Remove the tail if the snake has grown
    }
    return next_frame;
}

std::string game::Frame::to_string() const {
    return fmt::format(
        "Frame(width={}, height={}, direction={}, apples={}, snake_head={}, snake_body={})", width,
        height, static_cast<int>(direction), geo::to_string(apples), geo::to_string(snake_head),
        geo::to_string(snake_body));
}

const game::Frame& game::GameHandler::get_current_frame() const { return current_frame; }

std::string game::GameHandler::to_string() const {
    return fmt::format(
        "GameHandler(width={}, height={}, current_frame={})", width, height,
        current_frame.to_string());
}
