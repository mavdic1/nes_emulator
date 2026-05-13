#include  "CPU.h"

namespace Instructions {
    void Branch(CPU &cpu, const Bus& bus, int32& cycles, bool condition) {
        auto offset = static_cast<SByte>(cpu.fetchByte(bus, cycles));

        if (condition) {
            CPU::consumeCycle(cycles);
            Word oldPC=cpu.PC;
            Word newPC=oldPC+offset;

            if ((oldPC & 0xFF00) != (newPC & 0xFF00)) {
                CPU::consumeCycle(cycles);
            }

            cpu.PC = newPC;
        }
    }
}