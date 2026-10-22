#pragma once
#include <string>
#include <vector>

struct Transition {
    std::string from;
    std::vector<std::string> reads;
    std::string to;
    std::vector<std::string> writes;
    std::vector<char> moves;
};