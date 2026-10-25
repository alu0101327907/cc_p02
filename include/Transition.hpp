#pragma once
#include <string>
#include <vector>

/// Acciones de una transicion, con una lectura, escritura y movimiento por cinta.
struct Transition {
    /// Estado desde el que se aplica la transicion.
    std::string from;
    /// Simbolos leidos, ordenados por cinta.
    std::vector<std::string> reads;
    /// Estado al que se pasa.
    std::string to;
    /// Simbolos escritos, ordenados por cinta.
    std::vector<std::string> writes;
    /// Movimientos del cabezal, ordenados por cinta (L, R o S).
    std::vector<char> moves;
};