#include <fmt/core.h>
#include <format>
#include <inc/geo.hpp>
#include <inc/ui.hpp>
#include <string>

namespace ui {

constexpr wchar_t FRAME_TOP_LEFT = L'╔';
constexpr wchar_t FRAME_TOP_RIGHT = L'╗';
constexpr wchar_t FRAME_BOTTOM_LEFT = L'╚';
constexpr wchar_t FRAME_BOTTOM_RIGHT = L'╝';
constexpr wchar_t FRAME_HORIZONTAL = L'═';
constexpr wchar_t FRAME_VERTICAL = L'║';

class Frame {
public:
    uint32_t width;
    uint32_t height;

    geo::Points apples;

    geo::Point snake_head;
    geo::Points snake_body;

    Frame(const UIHandler& ui_handler)
        : width(ui_handler.width)
        , height(ui_handler.height)
        , apples()
        , snake_head({0, 0})
        , snake_body() {}

    std::string to_string() const {
        return fmt::format(
            "Frame(width={}, height={}, apples={}, snake_head=({}, {}), snake_body={})", width,
            height, apples.size(), snake_head.first, snake_head.second, snake_body.size());
    }
};

std::string UIHandler::to_string() const {
    return fmt::format("UIHandler(width={}, height={})", width, height);
}

} // namespace ui

// namespace ui
