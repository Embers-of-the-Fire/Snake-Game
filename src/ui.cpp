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
constexpr std::string ICON_SNAKE_BODY = "◯";

void UIHandler::print_frame(const frame::Frame& frame) const {
    fmt::print("{}", FRAME_TOP_LEFT);
    for (uint32_t i = 0; i < frame.width; ++i) {
        fmt::print("{}", FRAME_HORIZONTAL);
    }
    fmt::print("{}", FRAME_TOP_RIGHT);
    fmt::print("\n");

    for (uint32_t i = 0; i < frame.height; ++i) {
        fmt::print("{}", FRAME_VERTICAL);
        for (uint32_t j = 0; j < frame.width; ++j) {
            if (i == 0 || i == frame.height - 1) {
                fmt::print("{}", FRAME_FILL);
            } else {
                if (std::find(frame.apples.begin(), frame.apples.end(), geo::Point{j, i})
                    != frame.apples.end()) {
                    fmt::print("{}", ICON_APPLE);
                } else if (frame.snake_head == geo::Point{j, i}) {
                    fmt::print("{}", ICON_SNAKE_HEAD);
                } else if (
                    std::find(frame.snake_body.begin(), frame.snake_body.end(), geo::Point{j, i})
                    != frame.snake_body.end()) {
                    fmt::print("{}", ICON_SNAKE_BODY);
                } else {
                    fmt::print("{}", FRAME_FILL);
                }
            }
        }
        fmt::print("{}", FRAME_VERTICAL);
        fmt::print("\n");
    }

    fmt::print("{}", FRAME_BOTTOM_LEFT);
    for (uint32_t i = 0; i < frame.width; ++i) {
        fmt::print("{}", FRAME_HORIZONTAL);
    }
    fmt::print("{}", FRAME_BOTTOM_RIGHT);
    fmt::print("\n");
}

std::string UIHandler::to_string() const {
    return fmt::format("UIHandler(width={}, height={})", width, height);
}

} // namespace ui
