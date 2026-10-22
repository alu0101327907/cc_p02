#include "ConfigParser.hpp"
#include "TuringMachine.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

static std::vector<std::string> parseInputLine(const std::string& line) {
    std::vector<std::string> syms;
    for (char c : line) {
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') continue;
        syms.push_back(std::string(1, c));
    }
    return syms;
}

int main(int argc, char** argv) {
    std::string configFile, inputFile;
    bool hasInput = false;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "-config" && i + 1 < argc) configFile = argv[++i];
        else if (a == "-in" && i + 1 < argc) { inputFile = argv[++i]; hasInput = true; }
        else { std::cerr << "Argumento desconocido: " << a << "\n"; return 1; }
    }
    if (configFile.empty()) {
        std::cerr << "Uso: turing -config <f> [-in <f>]\n";
        return 1;
    }

    MTDefinition def;
    try { def = parseConfig(configFile); }
    catch (std::exception& e) { std::cerr << "Error: " << e.what() << "\n"; return 1; }

    TuringMachine tm(def);
    std::vector<std::string> inputs;

    if (hasInput) {
        std::ifstream f(inputFile);
        if (!f) { std::cerr << "No se puede abrir: " << inputFile << "\n"; return 1; }
        std::string line;
        while (std::getline(f, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            inputs.push_back(line);
        }
    } else {
        std::cout << "Introduce cadenas (línea vacía para terminar):\n";
        std::string line;
        while (std::getline(std::cin, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) break;
            inputs.push_back(line);
        }
    }

    for (const auto& s : inputs) {
        std::cout << "Entrada: " << s << "\n";
        tm.run(parseInputLine(s), std::cout);
        std::cout << "---\n";
    }
    return 0;
}