#pragma once
#include <map>
#include <string>
#include <vector>

/// Cinta infinita con un cabezal de lectura y escritura propio.
class Tape {
public:
    /// Crea una cinta vacia con el simbolo indicado como blanco.
    explicit Tape(std::string blank);
    /// Lee el simbolo bajo el cabezal.
    std::string read() const;
    /// Escribe un simbolo en la posicion actual del cabezal.
    void write(const std::string& sym);
    /// Desplaza el cabezal a izquierda (L), derecha (R) o lo deja quieto (S).
    void move(char dir);                       // 'L', 'R', 'S'
    /// Inicializa la cinta con la entrada y coloca el cabezal al inicio.
    void setInput(const std::vector<std::string>& input);
    /// Devuelve la posicion actual del cabezal.
    long long head() const { return headPos; }
    /// Representa la cinta y marca el cabezal entre corchetes.
    std::string toString() const;              // p.ej. "ab[c]d"
private:
    std::map<long long, std::string> cells;
    long long headPos = 0;
    std::string blankSym;
    std::string getCell(long long pos) const;
    void setCell(long long pos, const std::string& s);
};