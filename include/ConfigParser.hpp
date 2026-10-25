#pragma once
#include "TuringMachine.hpp"
#include <string>

/// Lee un archivo de configuracion y devuelve la definicion de la maquina.
MTDefinition parseConfig(const std::string& filename);