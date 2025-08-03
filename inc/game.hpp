#ifndef MOVE_H
#define MOVE_H

#include "inc/geo.hpp"
#include "inc/ui.hpp"

#include <cstdint>
#include <fmt/core.h>
#include <string>

namespace game {

enum class MoveDirection { UP, DOWN, LEFT, RIGHT };

class Frame {
    uint32_t width;
    uint32_t height;
    MoveDirection direction;

    geo::Points apples;
    geo::Point snake_head;

    // The body is stored as a deque to allow efficient insertion at the front
    // and removal from the back.
    geo::Points snake_body;

public:
    Frame(
        const uint32_t w, const uint32_t h, const MoveDirection dir,
        const geo::Point& initial_snake_head)
        : width(w)
        , height(h)
        , direction(dir)
        , apples()
        , snake_head(initial_snake_head)
        , snake_body() {}

    Frame(const Frame&) = default;
    Frame& operator=(const Frame&) = default;
    Frame(Frame&&) = default;
    Frame& operator=(Frame&&) = default;
    ~Frame() = default;

    Frame next_frame() const;
    std::string to_string() const;
};

class GameHandler {
    uint32_t width;
    uint32_t height;

    Frame current_frame;

    ui::UIHandler ui_handler;
    geo::GeoGraph graph;

public:
    GameHandler(const uint32_t w, const uint32_t h)
        : width(w)
        , height(h)
        , ui_handler(w, h)
        , graph(w, h)
        , current_frame(w, h, MoveDirection::RIGHT, {w / 2, h / 2}) {}

    const Frame& get_current_frame() const;

    std::string to_string() const;
};
} // namespace game

template <>
struct fmt::formatter<game::Frame> : fmt::formatter<std::string> {
    template <typename FormatContext>
    auto format(const game::Frame& f, FormatContext& ctx) const {
        return fmt::formatter<std::string>::format(f.to_string(), ctx);
    }
};

template <>
struct fmt::formatter<game::GameHandler> : fmt::formatter<std::string> {
    template <typename FormatContext>
    auto format(const game::GameHandler& gh, FormatContext& ctx) const {
        return fmt::formatter<std::string>::format(gh.to_string(), ctx);
    }
};

#endif // MOVE_H
