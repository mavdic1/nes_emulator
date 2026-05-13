#include "Instructions.h"
#include "../../include/CPU.h"

namespace Instructions {
    // Helper to handle the 1-cycle internal operation for flag instructions
    static void Flag_Execute(CPU& cpu, int32& cycles, CPU::Flags flag, bool set) {
        CPU::consumeCycle(cycles);
        cpu.setFlag(flag, set);
    }

    void CLC_func(CPU& cpu, int32& cycles) { Flag_Execute(cpu, cycles, CPU::C, false); }
    void SEC_func(CPU& cpu, int32& cycles) { Flag_Execute(cpu, cycles, CPU::C, true); }
    
    void CLD_func(CPU& cpu, int32& cycles) { Flag_Execute(cpu, cycles, CPU::D, false); }
    void SED_func(CPU& cpu, int32& cycles) { Flag_Execute(cpu, cycles, CPU::D, true); }

    void CLI_func(CPU& cpu, int32& cycles) { Flag_Execute(cpu, cycles, CPU::I, false); }
    void SEI_func(CPU& cpu, int32& cycles) { Flag_Execute(cpu, cycles, CPU::I, true); }

    void CLV_func(CPU& cpu, int32& cycles) { Flag_Execute(cpu, cycles, CPU::V, false); }
}