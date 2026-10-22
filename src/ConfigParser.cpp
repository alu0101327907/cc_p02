#include "ConfigParser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

static std::vector<std::string> tokenize(const std::string& line) {
    std::string s = line;
    auto pos = s.find('#');
    if (pos != std::string::npos) s = s.substr(0, pos);
    std::istringstream iss(s);
    std::vector<std::string> tokens;
    std::string t;
    while (iss >> t) tokens.push_back(t);
    return tokens;
}

MTDefinition parseConfig(const std::string& filename) {
    std::ifstream f(filename);
    if (!f) throw std::runtime_error("No se puede abrir: " + filename);

    std::vector<std::vector<std::string>> lines;
    std::string line;
    while (std::getline(f, line)) {
        auto toks = tokenize(line);
        if (!toks.empty()) lines.push_back(toks);
    }
    if (lines.size() < 7) throw std::runtime_error("Configuración incompleta");

    MTDefinition def;
    size_t idx = 0;

    for (auto& t : lines[idx]) def.Q.insert(t);     ++idx;   // Q
    for (auto& t : lines[idx]) def.Sigma.insert(t); ++idx;   // Σ
    for (auto& t : lines[idx]) def.Gamma.insert(t); ++idx;   // Γ
    def.s     = lines[idx][0];                      ++idx;   // s
    def.blank = lines[idx][0];                      ++idx;   // b
    for (auto& t : lines[idx]) def.F.insert(t);     ++idx;   // F
    def.numTapes = std::stoi(lines[idx][0]);        ++idx;   // nº cintas

    if (!def.Q.count(def.s))
        throw std::runtime_error("s no está en Q");
    if (!def.Gamma.count(def.blank))
        throw std::runtime_error("blanco no está en Γ");
    for (auto& st : def.F)
        if (!def.Q.count(st))
            throw std::runtime_error("estado final fuera de Q: " + st);
    for (auto& sym : def.Sigma)
        if (!def.Gamma.count(sym))
            throw std::runtime_error("Σ ⊄ Γ: " + sym);

    for (; idx < lines.size(); ++idx) {
        auto& toks = lines[idx];
        int expected = 1 + def.numTapes + 1 + def.numTapes + def.numTapes;
        if ((int)toks.size() != expected)
            throw std::runtime_error("transición con tamaño incorrecto");

        Transition tr;
        int p = 0;
        tr.from = toks[p++];
        for (int i = 0; i < def.numTapes; ++i) tr.reads.push_back(toks[p++]);
        tr.to = toks[p++];
        for (int i = 0; i < def.numTapes; ++i) tr.writes.push_back(toks[p++]);
        for (int i = 0; i < def.numTapes; ++i) tr.moves.push_back(toks[p++][0]);

        if (!def.Q.count(tr.from)) throw std::runtime_error("estado: " + tr.from);
        if (!def.Q.count(tr.to))   throw std::runtime_error("estado: " + tr.to);
        for (auto& r : tr.reads)  if (!def.Gamma.count(r)) throw std::runtime_error("símbolo: " + r);
        for (auto& w : tr.writes) if (!def.Gamma.count(w)) throw std::runtime_error("símbolo: " + w);
        for (char m : tr.moves)
            if (m != 'L' && m != 'R' && m != 'S')
                throw std::runtime_error("movimiento inválido");

        std::string key = tr.from;
        for (auto& r : tr.reads) key += "|" + r;
        if (def.delta.count(key))
            throw std::runtime_error("transición no determinista en: " + key);
        def.delta[key] = tr;
    }
    return def;
}