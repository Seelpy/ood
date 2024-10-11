#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <ios>

typedef std::vector<uint8_t> SubstitutionTable;

SubstitutionTable GenerateSubstitutionTable(uint32_t key) {
    SubstitutionTable table(256);
    std::iota(table.begin(), table.end(), 0);

    std::mt19937 rng(key);
    std::shuffle(table.begin(), table.end(), rng);

    return table;
}

SubstitutionTable GenerateReverseSubstitutionTable(uint32_t key) {
    auto table = GenerateSubstitutionTable(key);
    SubstitutionTable reverseTable(256);
    for (int i = 0; i < 256; i++)
    {
        reverseTable[table[i]] = i;
    }
    return reverseTable;
}
