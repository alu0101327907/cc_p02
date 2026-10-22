#include "Tape.hpp"
#include <algorithm>
#include <sstream>

Tape::Tape(std::string blank) : blankSym(std::move(blank)) {}

std::string Tape::getCell(long long pos) const {
    auto it = cells.find(pos);
    return it == cells.end() ? blankSym : it->second;
}

void Tape::setCell(long long pos, const std::string& s) {
    if (s == blankSym) cells.erase(pos);
    else cells[pos] = s;
}

std::string Tape::read() const { return getCell(headPos); }

void Tape::write(const std::string& sym) { setCell(headPos, sym); }

void Tape::move(char dir) {
    if (dir == 'L') --headPos;
    else if (dir == 'R') ++headPos;
}

void Tape::setInput(const std::vector<std::string>& input) {
    cells.clear();
    headPos = 0;
    for (size_t i = 0; i < input.size(); ++i)
        setCell(static_cast<long long>(i), input[i]);
}

std::string Tape::toString() const {
    if (cells.empty()) return "[" + blankSym + "]";
    long long lo = std::min(headPos, cells.begin()->first);
    long long hi = std::max(headPos, cells.rbegin()->first);
    std::ostringstream oss;
    for (long long p = lo; p <= hi; ++p) {
        std::string s = getCell(p);
        if (p == headPos) oss << "[" << s << "]";
        else oss << s;
    }
    return oss.str();
}