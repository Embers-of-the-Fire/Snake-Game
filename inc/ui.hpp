#ifndef UI_H
#define UI_H

#include <cstdint>
#include <vector>
#include <string>


namespace ui {

class UIHandler {
public:
    uint32_t width;
    uint32_t height;

    // 构造函数，默认 width 和 height 为 60，可自定义
    UIHandler(const uint32_t w = 60, const uint32_t h = 60)
        : width(w)
        , height(h) {}

    ~UIHandler() = default;

    std::string to_string() const;
};

} // namespace ui




#include <fmt/core.h>

// fmt::formatter 特化，必须放在头文件
template <>
struct fmt::formatter<ui::UIHandler> : fmt::formatter<std::string> {
    auto format(const ui::UIHandler& uih, format_context& ctx) const {
        return fmt::formatter<std::string>::format(uih.to_string(), ctx);
    }
};

// 如果 Frame 也需要格式化支持，Frame 的声明需在此头文件可见
// 你可以根据需要取消注释并补充 Frame 的声明
// template <>
// struct fmt::formatter<ui::Frame> : fmt::formatter<std::string> {
//     auto format(const ui::Frame& f, format_context& ctx) const {
//         return fmt::formatter<std::string>::format(f.to_string(), ctx);
//     }
// };

#endif // UI_H
