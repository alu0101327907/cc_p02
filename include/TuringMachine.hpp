#pragma once
#include "Tape.hpp"
#include "Transition.hpp"
#include <map>
#include <set>
#include <string>
#include <vector>
#include <ostream>

struct MTDefinition {
    std::set<std::string> Q;
    std::set<std::string> Sigma;
    std::set<std::string> Gamma;
    std::string s;
    std::string blank;
    std::set<std::string> F;
    int numTapes = 1;
    std::map<std::string, Transition> delta;   // clave: estado|a1|a2|...
};

class TuringMachine {
public:
    explicit TuringMachine(MTDefinition def);
    bool run(const std::vector<std::string>& input, std::ostream& out);
private:
    MTDefinition def;
    std::vector<Tape> tapes;
    std::string currentState;
    std::string keyFor(const std::string& state,
                       const std::vector<std::string>& reads) const;
};