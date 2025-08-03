#ifndef UI_H
#define UI_H

#include "inc/geo.hpp"

#include <cstdint>
#include <fmt/core.h>
#include <string>
#include <vector>

namespace ui {

class UIHandler {
public:
    uint32_t width;
    uint32_t height;

    UIHandler(const uint32_t w = 60, const uint32_t h = 60)
        : width(w)
        , height(h) {}

    ~UIHandler() = default;

    std::string to_string() const;
};

} // namespace ui

template <>
struct fmt::formatter<ui::UIHandler> : fmt::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ui::UIHandler& uih, FormatContext& ctx) const {
        return fmt::formatter<std::string>::format(uih.to_string(), ctx);
    }
};

#endif // UI_H
