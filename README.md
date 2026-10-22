# Práctica 2 — Simulador de Máquina de Turing determinista multicinta

## Autor
- Nombre: Alejandro David Castro Afonso
- Asignatura: CC 26/27

## Opciones elegidas
- Escritura y movimientos **independientes** por cinta.
- Movimientos posibles: **L, R, S**.
- Cinta infinita en **ambas direcciones** (`std::map<long long, std::string>`).

## Requisitos
- C++17
- CMake ≥ 3.15

## Compilación
```bash
mkdir build && cd build
cmake ..
make