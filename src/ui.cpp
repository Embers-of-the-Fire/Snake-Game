#include "inc/ui.hpp"
#include "inc/geo.hpp"

#include <fmt/core.h>
#include <format>
#include <string>

namespace ui {

constexpr std::string FRAME_TOP_LEFT = "╔";
constexpr std::string FRAME_TOP_RIGHT = "╗";
constexpr std::string FRAME_BOTTOM_LEFT = "╚";
constexpr std::string FRAME_BOTTOM_RIGHT = "╝";
constexpr std::string FRAME_HORIZONTAL = "══";
constexpr std::string FRAME_VERTICAL = "║";
constexpr std::string FRAME_FILL = "  ";

constexpr std::string ICON_APPLE = "🍎";
constexpr std::string ICON_SNAKE_HEAD = "🐍";
constexpr std::string ICON_SNAKE_HEAD_UP = ICON_SNAKE_HEAD;
constexpr std::string ICON_SNAKE_HEAD_DOWN = ICON_SNAKE_HEAD;
constexpr std::string ICON_SNAKE_HEAD_LEFT = ICON_SNAKE_HEAD;
constexpr std::string ICON_SNAKE_HEAD_RIGHT = ICON_SNAKE_HEAD;
constexpr std::string ICON_SNAKE_BODY = "██";

void UIHandler::print_frame(const frame::Frame& frame) const {
    fmt::print(
        "Frame ({}x{}) - {} - Score: {}\nDirection: {} - Snake Head: {}, Apples: {}, Snake Body: "
        "{}\n",
        frame.width, frame.height, frame.tick, frame.score, static_cast<int>(frame.direction),
        geo::to_string(frame.snake_head), geo::to_string(frame.apples),
        geo::to_string(frame.snake_body));

    fmt::print("{}", FRAME_TOP_LEFT);
    for (uint32_t i = 0; i < frame.width; ++i) {
        fmt::print("{}", FRAME_HORIZONTAL);
    }
    fmt::print("{}\n", FRAME_TOP_RIGHT);

    for (uint32_t i = 0; i < frame.height; ++i) {
        fmt::print("{}", FRAME_VERTICAL);
        for (uint32_t j = 0; j < frame.width; ++j) {
            if (std::find(frame.apples.begin(), frame.apples.end(), geo::Point{j, i})
                != frame.apples.end()) {
                fmt::print("{}", ICON_APPLE);
            } else if (frame.snake_head == geo::Point{j, i}) {
                // clang-format off: keep padding here for readability
                switch (frame.direction) {
                case frame::MoveDirection::UP:    fmt::print("{}", ICON_SNAKE_HEAD_UP); break;
                case frame::MoveDirection::DOWN:  fmt::print("{}", ICON_SNAKE_HEAD_DOWN); break;
                case frame::MoveDirection::LEFT:  fmt::print("{}", ICON_SNAKE_HEAD_LEFT); break;
                case frame::MoveDirection::RIGHT: fmt::print("{}", ICON_SNAKE_HEAD_RIGHT); break;
                }
                // clang-format on
            } else if (
                std::find(frame.snake_body.begin(), frame.snake_body.end(), geo::Point{j, i})
                != frame.snake_body.end()) {
                fmt::print("{}", ICON_SNAKE_BODY);
            } else {
                fmt::print("{}", FRAME_FILL);
            }
        }
        fmt::print("{}\n", FRAME_VERTICAL);
    }

    fmt::print("{}", FRAME_BOTTOM_LEFT);
    for (uint32_t i = 0; i < frame.width; ++i) {
        fmt::print("{}", FRAME_HORIZONTAL);
    }
    fmt::print("{}\n", FRAME_BOTTOM_RIGHT);
}

std::string UIHandler::to_string() const {
    return fmt::format("UIHandler(width={}, height={})", width, height);
}

} // namespace ui
