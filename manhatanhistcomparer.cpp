#include "manhatanhistcomparer.h"
#include <cmath>

uint ManhatanHistComparer::operator ()(uint* h1, uint* h2, uint dimm) const
{
    // Manhatan distance between two histograms
    // SUM(1, N, abs(h1(i) - h2(i))
    uint ret = 0;
    for (uint i = 0; i < dimm * dimm * dimm; i++)
    {
        ret += std::abs(h1[i] - h2[i]);
    }

    return ret;
}
