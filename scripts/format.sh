#!/bin/bash

clang-format -i main.cpp

find src/ -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -i {} +

find inc/ -type f -name "*.h" -exec clang-format -i {} +