#include "inc/ai.hpp"

#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using Node = geo::Point;

struct NodeHash {
    size_t operator()(const Node& p) const noexcept {
        return (static_cast<size_t>(p.first) << 32) ^ static_cast<size_t>(p.second);
    }
};

inline int manhattan(const Node& a, const Node& b) {
    int dx = std::abs(static_cast<int>(a.first) - static_cast<int>(b.first));
    int dy = std::abs(static_cast<int>(a.second) - static_cast<int>(b.second));
    return dx + dy;
}

static std::vector<Node> neighbors(const Node& p, uint32_t w, uint32_t h) {
    std::vector<Node> ns;
    ns.reserve(4);
    // clang-format off
    if (p.first > 0)        ns.emplace_back(p.first - 1, p.second);           // left
    if (p.first + 1 < w)    ns.emplace_back(p.first + 1, p.second);       // right
    if (p.second > 0)       ns.emplace_back(p.first, p.second - 1);          // up
    if (p.second + 1 < h)   ns.emplace_back(p.first, p.second + 1);      // down
    // clang-format on
    return ns;
}

static std::vector<Node>
    reconstruct_path(const std::unordered_map<Node, Node, NodeHash>& came_from, Node cur) {
    std::vector<Node> path;
    path.push_back(cur);
    auto it = came_from.find(cur);
    while (it != came_from.end()) {
        cur = it->second;
        path.push_back(cur);
        it = came_from.find(cur);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

namespace ai {

std::optional<frame::MoveDirection> next_move_astar(const frame::Frame& f) {
    if (f.apples.empty())
        return std::nullopt;
    const auto w = f.width;
    const auto h = f.height;

    const Node start = f.snake_head;
    const Node goal = f.apples.front();

    std::unordered_set<Node, NodeHash> blocked(f.snake_body.begin(), f.snake_body.end());

    auto in_blocked = [&](const Node& n) {
        if (n == start)
            return false;
        return blocked.count(n) > 0;
    };

    struct Item {
        Node node;
        int f;
        int g;
    };

    struct Cmp {
        bool operator()(const Item& a, const Item& b) const { return a.f > b.f; }
    };

    std::priority_queue<Item, std::vector<Item>, Cmp> open;
    std::unordered_map<Node, int, NodeHash> gscore; // cost from start
    std::unordered_map<Node, int, NodeHash> fscore; // g + h
    std::unordered_map<Node, Node, NodeHash> came_from;

    gscore[start] = 0;
    fscore[start] = manhattan(start, goal);
    open.push({start, fscore[start], gscore[start]});

    std::unordered_set<Node, NodeHash> closed;

    auto push_open = [&](const Node& n, int g, int f, const Node& parent) {
        auto it = gscore.find(n);
        if (it == gscore.end() || g < it->second) {
            gscore[n] = g;
            fscore[n] = f;
            came_from[n] = parent;
            open.push({n, f, g});
        }
    };

    while (!open.empty()) {
        Item cur = open.top();
        open.pop();
        if (closed.count(cur.node))
            continue;
        if (cur.node == goal) {
            auto path = reconstruct_path(came_from, cur.node);
            if (path.size() >= 2) {
                const Node& nxt = path[1];
                const int dx = static_cast<int>(nxt.first) - static_cast<int>(start.first);
                const int dy = static_cast<int>(nxt.second) - static_cast<int>(start.second);
                if (dx == -1 && dy == 0)
                    return frame::MoveDirection::LEFT;
                if (dx == 1 && dy == 0)
                    return frame::MoveDirection::RIGHT;
                if (dx == 0 && dy == -1)
                    return frame::MoveDirection::UP;
                if (dx == 0 && dy == 1)
                    return frame::MoveDirection::DOWN;
            }
            return std::nullopt;
        }
        closed.insert(cur.node);

        for (const auto& nb : neighbors(cur.node, w, h)) {
            if (in_blocked(nb))
                continue;
            if (closed.count(nb))
                continue;

            int tentative_g = cur.g + 1;
            int hval = manhattan(nb, goal);
            int fval = tentative_g + hval;
            push_open(nb, tentative_g, fval, cur.node);
        }
    }

    // Simple solution
    // Might have a better solution?
    const auto ns = neighbors(start, w, h);
    for (const auto& nb : ns) {
        if (!in_blocked(nb)) {
            const int dx = static_cast<int>(nb.first) - static_cast<int>(start.first);
            const int dy = static_cast<int>(nb.second) - static_cast<int>(start.second);
            if (dx == -1 && dy == 0)
                return frame::MoveDirection::LEFT;
            if (dx == 1 && dy == 0)
                return frame::MoveDirection::RIGHT;
            if (dx == 0 && dy == -1)
                return frame::MoveDirection::UP;
            if (dx == 0 && dy == 1)
                return frame::MoveDirection::DOWN;
        }
    }

    return std::nullopt;
}

} // namespace ai
