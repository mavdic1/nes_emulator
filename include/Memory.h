#pragma once
#include <array>

#include "Types.h"

struct Memory
{
    static constexpr int32 MAX_MEM = 64 * 1024;
    std::array<Byte, MAX_MEM> Data;

    void Initialize(); //Initialize memory (set all values to 0)

    [[nodiscard]] Byte Read(Word address) const;
    void Write( Word address, Byte value);
};
