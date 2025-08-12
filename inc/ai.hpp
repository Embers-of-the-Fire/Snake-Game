#ifndef AI_H
#define AI_H

#include "inc/frame.hpp"
#include "inc/geo.hpp"

#include <optional>

namespace ai {

std::optional<frame::MoveDirection> next_move_astar(const frame::Frame& frame);

}

#endif // AI_H
