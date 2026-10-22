#pragma once
#include <map>
#include <string>
#include <vector>

class Tape {
public:
    explicit Tape(std::string blank);
    std::string read() const;
    void write(const std::string& sym);
    void move(char dir);                       // 'L', 'R', 'S'
    void setInput(const std::vector<std::string>& input);
    long long head() const { return headPos; }
    std::string toString() const;              // p.ej. "ab[c]d"
private:
    std::map<long long, std::string> cells;
    long long headPos = 0;
    std::string blankSym;
    std::string getCell(long long pos) const;
    void setCell(long long pos, const std::string& s);
};