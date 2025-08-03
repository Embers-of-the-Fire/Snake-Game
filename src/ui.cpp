#include "inc/ui.hpp"
#include "inc/geo.hpp"

#include <fmt/core.h>
#include <fmt/xchar.h>
#include <format>
#include <string>

namespace ui {

constexpr wchar_t FRAME_TOP_LEFT = L'╔';
constexpr wchar_t FRAME_TOP_RIGHT = L'╗';
constexpr wchar_t FRAME_BOTTOM_LEFT = L'╚';
constexpr wchar_t FRAME_BOTTOM_RIGHT = L'╝';
constexpr wchar_t FRAME_HORIZONTAL = L'═';
constexpr wchar_t FRAME_VERTICAL = L'║';
constexpr wchar_t FRAME_FILL = L' ';

constexpr wchar_t ICON_APPLE = L'🍎';
constexpr wchar_t ICON_SNAKE_HEAD = L'🐍';
constexpr wchar_t ICON_SNAKE_BODY = L'◯';

class UIFrame {
public:
    UIFrame(const UIHandler& ui_handler)
        : width(ui_handler.width)
        , height(ui_handler.height)
        , apples()
        , snake_head({0, 0})
        , snake_body() {}

    uint32_t width;
    uint32_t height;

    geo::Points apples;

    geo::Point snake_head;
    geo::Points snake_body;

    std::string to_string() const {
        return fmt::format(
            "UIFrame(width={}, height={}, apples={}, snake_head=({}, {}), snake_body={})", width,
            height, apples.size(), snake_head.first, snake_head.second, snake_body.size());
    }
};

static void _print_frame(const UIFrame& frame) {
    fmt::print(L"{}", FRAME_TOP_LEFT);
    for (uint32_t i = 0; i < frame.width; ++i) {
        fmt::print(L"{}", FRAME_HORIZONTAL);
    }
    fmt::print(L"{}", FRAME_TOP_RIGHT);
    fmt::print("\n");

    for (uint32_t i = 0; i < frame.height; ++i) {
        fmt::print(L"{}", FRAME_VERTICAL);
        for (uint32_t j = 0; j < frame.width; ++j) {
            if (i == 0 || i == frame.height - 1) {
                fmt::print(L"{}", FRAME_FILL);
            } else {
                if (std::find(frame.apples.begin(), frame.apples.end(), geo::Point{j, i})
                    != frame.apples.end()) {
                    fmt::print(L"{}", ICON_APPLE);
                } else if (frame.snake_head == geo::Point{j, i}) {
                    fmt::print(L"{}", ICON_SNAKE_HEAD);
                } else if (
                    std::find(frame.snake_body.begin(), frame.snake_body.end(), geo::Point{j, i})
                    != frame.snake_body.end()) {
                    fmt::print(L"{}", ICON_SNAKE_BODY);
                } else {
                    fmt::print(L"{}", FRAME_FILL);
                }
            }
        }
        fmt::print(L"{}", FRAME_VERTICAL);
        fmt::print("\n");
    }

    fmt::print(L"{}", FRAME_BOTTOM_LEFT);
    for (uint32_t i = 0; i < frame.width; ++i) {
        fmt::print(L"{}", FRAME_HORIZONTAL);
    }
    fmt::print(L"{}", FRAME_BOTTOM_RIGHT);
    fmt::print("\n");
}

std::string UIHandler::to_string() const {
    return fmt::format("UIHandler(width={}, height={})", width, height);
}

} // namespace ui
