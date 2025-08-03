#include "inc/frame.hpp"

#include <algorithm>

frame::Frame frame::Frame::next_frame(const geo::GeoGraph& graph) const {
    Frame next_frame(*this);

    // Update snake head position based on direction
    // clang-format off: keep padding here for readability
    switch (direction) {
    case frame::MoveDirection::UP:    next_frame.snake_head = graph.get_top_of(snake_head);    break;
    case frame::MoveDirection::DOWN:  next_frame.snake_head = graph.get_bottom_of(snake_head); break;
    case frame::MoveDirection::LEFT:  next_frame.snake_head = graph.get_left_of(snake_head);   break;
    case frame::MoveDirection::RIGHT: next_frame.snake_head = graph.get_right_of(snake_head);  break;
    }
    // clang-format on

    next_frame.snake_body.push_front(next_frame.snake_head);
    if (std::find(next_frame.apples.begin(), next_frame.apples.end(), next_frame.snake_head)
        != next_frame.apples.end()) {
        next_frame.apples.erase(
            std::remove(next_frame.apples.begin(), next_frame.apples.end(), next_frame.snake_head),
            next_frame.apples.end());
        geo::Point random;
        do {
            random = graph.get_random_point();
        } while (std::find(next_frame.snake_body.begin(), next_frame.snake_body.end(), random)
                     != next_frame.snake_body.end()
                 || random == next_frame.snake_head);
        next_frame.apples.push_back(random);
        next_frame.score++;
    } else if (next_frame.snake_body.size() > 1) {
        next_frame.snake_body.pop_back(); // Remove the tail if the snake has grown
    }

    next_frame.tick++;
    return next_frame;
}

std::string frame::Frame::to_string() const {
    return fmt::format(
        "Frame(width={}, height={}, direction={}, apples={}, snake_head={}, snake_body={})", width,
        height, static_cast<int>(direction), geo::to_string(apples), geo::to_string(snake_head),
        geo::to_string(snake_body));
}
