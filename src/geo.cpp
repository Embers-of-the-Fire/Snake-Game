#include "inc/geo.hpp"
#include <cstdlib>

namespace geo {

Point GeoGraph::get_left_of(const Point& p) const {
    if (p.first == 0) {
        return {width - 1, p.second};
    }
    return {p.first - 1, p.second};
}

Point GeoGraph::get_right_of(const Point& p) const {
    if (p.first == width - 1) {
        return {0, p.second};
    }
    return {p.first + 1, p.second};
}

Point GeoGraph::get_top_of(const Point& p) const {
    if (p.second == 0) {
        return {p.first, height - 1};
    }
    return {p.first, p.second - 1};
}

Point GeoGraph::get_bottom_of(const Point& p) const {
    if (p.second == height - 1) {
        return {p.first, 0};
    }
    return {p.first, p.second + 1};
}

Point GeoGraph::get_random_point() const { return {dist_x(gen), dist_y(gen)}; }

std::string GeoGraph::to_string() const {
    return fmt::format("GeoGraph(width={}, height={})", width, height);
}

std::string to_string(const Point& p) { return fmt::format("({}, {})", p.first, p.second); }

std::string to_string(const Points& ps) {
    std::string s = "[";
    bool first = true;
    for (const auto& p : ps) {
        if (!first)
            s += ", ";
        s += to_string(p);
        first = false;
    }
    s += "]";
    return s;
}

} // namespace geo
