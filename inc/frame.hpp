#ifndef FRAME_H
#define FRAME_H

#include "inc/geo.hpp"

#include <cstdint>
#include <string>

namespace frame {

enum class MoveDirection { UP, DOWN, LEFT, RIGHT };

enum class FrameValidity {
    Valid,
    HitBorder,
    HitSelf,
};

class Frame {
public:
    uint32_t width;
    uint32_t height;
    MoveDirection direction;

    geo::Points apples;
    geo::Point snake_head;

    // The body is stored as a deque to allow efficient insertion at the front
    // and removal from the back.
    geo::Points snake_body;

    uint32_t score;
    uint32_t tick;

    Frame(
        const uint32_t w, const uint32_t h, const MoveDirection dir,
        const geo::Point& initial_snake_head)
        : width(w)
        , height(h)
        , direction(dir)
        , apples()
        , snake_head(initial_snake_head)
        , snake_body()
        , score(0)
        , tick(0) {}

    Frame(const Frame&) = default;
    Frame& operator=(const Frame&) = default;
    Frame(Frame&&) = default;
    Frame& operator=(Frame&&) = default;
    ~Frame() = default;

    Frame next_frame(const geo::GeoGraph& graph) const;
    FrameValidity will_be_valid() const;
    std::string to_string() const;
};

} // namespace frame

template <>
struct fmt::formatter<frame::Frame> : fmt::formatter<std::string> {
    template <typename FormatContext>
    auto format(const frame::Frame& f, FormatContext& ctx) const {
        return fmt::formatter<std::string>::format(f.to_string(), ctx);
    }
};

#endif // FRAME_H
