#include <iostream>
#include <fmt/core.h>

#include <inc/ui.hpp>
#include <inc/geo.hpp>

int main(int, char**) {
    const ui::UIHandler ui_handler(80, 40);

    fmt::print("UIHandler: {}\n", ui_handler);
}
