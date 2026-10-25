#include "TuringMachine.hpp"

TuringMachine::TuringMachine(MTDefinition def) : def(std::move(def)) {}

std::string TuringMachine::keyFor(const std::string& state,
                                  const std::vector<std::string>& reads) const {
    std::string k = state;
    for (const auto& r : reads) k += "|" + r;
    return k;
}

bool TuringMachine::run(const std::vector<std::string>& input, std::ostream& out) {
    tapes.clear();
    
    // Cada cinta conserva sus propias celdas y la posicion de su cabezal.
    for (int i = 0; i < def.numTapes; ++i) tapes.emplace_back(def.blank);
    tapes[0].setInput(input);
    currentState = def.s;

    while (true) {
        std::vector<std::string> reads;
        for (auto& t : tapes) reads.push_back(t.read());
        std::string key = keyFor(currentState, reads);
        auto it = def.delta.find(key);
        if (it == def.delta.end()) break;
        const Transition& tr = it->second;

        // Cada indice aplica a una cinta su escritura y movimiento propios.
        for (int i = 0; i < def.numTapes; ++i) {
            tapes[i].write(tr.writes[i]);
            tapes[i].move(tr.moves[i]);
        }
        currentState = tr.to;
    }

    bool accepted = def.F.count(currentState) > 0;
    out << (accepted ? "ACEPTADA" : "RECHAZADA") << "\n";
    out << "Estado final: " << currentState << "\n";
    for (int i = 0; i < def.numTapes; ++i)
        out << "Cinta " << (i + 1) << ": " << tapes[i].toString() << "\n";
    return accepted;
}