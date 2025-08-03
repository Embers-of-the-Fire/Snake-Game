#ifndef GEO_H
#define GEO_H

#include <cstdint>
#include <deque>
#include <fmt/core.h>
#include <random>
#include <string>
#include <utility>

namespace geo {

using Point = std::pair<uint32_t, uint32_t>;
using Points = std::deque<Point>;

class GeoGraph {
    uint32_t width;
    uint32_t height;

    mutable std::mt19937 gen;
    mutable std::uniform_int_distribution<uint32_t> dist_x;
    mutable std::uniform_int_distribution<uint32_t> dist_y;

public:
    GeoGraph(const uint32_t w, const uint32_t h)
        : width(w)
        , height(h) {
        std::random_device rd;
        gen = std::mt19937{rd()};
        dist_x = std::uniform_int_distribution<uint32_t>(0, w - 1);
        dist_y = std::uniform_int_distribution<uint32_t>(0, h - 1);
    }

    ~GeoGraph() = default;

    Point get_left_of(const Point& p) const;

    Point get_right_of(const Point& p) const;

    Point get_top_of(const Point& p) const;

    Point get_bottom_of(const Point& p) const;

    Point get_random_point() const;

    std::string to_string() const;
};

std::string to_string(const Point& p);
std::string to_string(const Points& ps);

} // namespace geo

template <>
struct fmt::formatter<geo::GeoGraph> : fmt::formatter<std::string> {
    template <typename FormatContext>
    auto format(const geo::GeoGraph& g, FormatContext& ctx) const {
        return fmt::formatter<std::string>::format(g.to_string(), ctx);
    }
};

template <>
struct fmt::formatter<geo::Point> : fmt::formatter<std::string> {
    template <typename FormatContext>
    auto format(const geo::Point& p, FormatContext& ctx) const {
        return fmt::formatter<std::string>::format(geo::to_string(p), ctx);
    }
};

template <>
struct fmt::formatter<geo::Points> : fmt::formatter<std::string> {
    template <typename FormatContext>
    auto format(const geo::Points& ps, FormatContext& ctx) const {
        return fmt::formatter<std::string>::format(geo::to_string(ps), ctx);
    }
};

#endif // GEO_H