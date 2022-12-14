#include "associative_operation.h"

bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    for (int x = 0; x < table.size(); ++x) {
        for (int y = 0; y < table[x].size(); ++y) {
            for (int z = 0; z < table.size(); ++z) {
                if (table[table[x][y]][z] != table[x][table[y][z]]) {
                    return false;
                }
            }
        }
    }
    return true;
}
