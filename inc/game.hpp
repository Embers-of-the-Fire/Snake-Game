#ifndef MOVE_H
#define MOVE_H

#include "inc/frame.hpp"
#include "inc/geo.hpp"
#include "inc/ui.hpp"

#include <cstdint>
#include <fmt/core.h>
#include <iostream>
#include <string>

namespace game {
class GameHandler {
    uint32_t width;
    uint32_t height;

    frame::Frame current_frame;

    ui::UIHandler ui_handler;
    geo::GeoGraph graph;

public:
    GameHandler(const uint32_t w, const uint32_t h)
        : width(w)
        , height(h)
        , ui_handler(w, h)
        , graph(w, h)
        , current_frame(w, h, frame::MoveDirection::RIGHT, {w / 2, h / 2}) {
        const auto rp = graph.get_random_point();
        std::cout << fmt::format("{}", rp) << std::endl;
        current_frame.apples.push_back(rp);
    }

    const frame::Frame& get_current_frame() const;

    void add_apple(const geo::Point& apple);
    void set_direction(const frame::MoveDirection dir);
    void print_frame() const;
    void next_frame();

    std::string to_string() const;
};
} // namespace game

template <>
struct fmt::formatter<game::GameHandler> : fmt::formatter<std::string> {
    template <typename FormatContext>
    auto format(const game::GameHandler& gh, FormatContext& ctx) const {
        return fmt::formatter<std::string>::format(gh.to_string(), ctx);
    }
};

#endif // MOVE_H
