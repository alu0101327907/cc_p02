#pragma once
#include "Tape.hpp"
#include "Transition.hpp"
#include <map>
#include <set>
#include <string>
#include <vector>
#include <ostream>

/// Definicion de una maquina de Turing determinista multicinta.
struct MTDefinition {
    /// Conjunto de estados.
    std::set<std::string> Q;
    /// Alfabeto de entrada.
    std::set<std::string> Sigma;
    /// Alfabeto de cinta, incluido el blanco.
    std::set<std::string> Gamma;
    /// Estado inicial.
    std::string s;
    /// Simbolo blanco de las cintas.
    std::string blank;
    /// Estados de aceptacion.
    std::set<std::string> F;
    /// Numero de cintas de la maquina.
    int numTapes = 1;
    /// Transiciones indexadas por estado y simbolos leidos.
    std::map<std::string, Transition> delta;   // clave: estado|a1|a2|...
};

/// Ejecuta una definicion de maquina sobre una o varias cintas.
class TuringMachine {
public:
    /// Construye la maquina a partir de su definicion.
    explicit TuringMachine(MTDefinition def);
    /// Ejecuta la entrada e imprime el resultado y el contenido final de las cintas.
    bool run(const std::vector<std::string>& input, std::ostream& out);
private:
    MTDefinition def;
    std::vector<Tape> tapes;
    std::string currentState;
    std::string keyFor(const std::string& state, const std::vector<std::string>& reads) const;
};