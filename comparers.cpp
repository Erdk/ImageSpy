#include "comparers.h"
#include <cmath>

uint ManhatanHistComparer::operator ()(image_record* h1, image_record* h2)
{
    // Manhatan distance between two histograms
    // SUM(1, N, abs(h1(i) - h2(i))

    uint ret = 0;
    uint dimm = h1->dimmension;
    for (uint i = 0; i < dimm; i++)
    {
        for (uint j = 0; j < dimm; j++)
        {
            for (uint k = 0; k < dimm; k++)
            {
                uint a = h1->getVar(i, j, k);
                uint b = h2->getVar(i, j, k);
                ret += std::abs((int)(a - b));
            }
        }
    }

    return ret;
}

uint EuklidesHistComparer::operator ()(image_record* h1, image_record* h2)
{
    uint ret = 0;
    uint dimm = h1->dimmension;

    for (uint i = 0; i < dimm; i++)
    {
        for (uint j = 0; j < dimm; j++)
        {
            for (uint k = 0; k < dimm; k++)
            {
                uint a = h1->getVar(i, j, k);
                uint b = h2->getVar(i, j, k);
                ret += std::pow((double)(a - b), 2.0);
            }
        }
    }

    ret = std::sqrt((double) ret);
    return ret;
}

uint CosinusHistComparer::operator ()(image_record* h1, image_record* h2)
{
    return 0;
}

uint CrossSectionHistComparer::operator ()(image_record* h1, image_record* h2)
{
    uint ret = 0;
    uint dimm = h1->dimmension;

    for (uint i = 0; i < dimm; i++)
    {
        for (uint j = 0; j < dimm; j++)
        {
            for (uint k = 0; k < dimm; k++)
            {
                uint a = h1->getVar(i, j, k);
                uint b = h2->getVar(i, j, k);
                ret += a > b ? b : a;
            }
        }
    }

    ret = (uint)((float)ret / (float)(dimm * dimm * dimm));
    return 1 - ret;
}

uint NormCorrelationHistComparer::operator ()(image_record* h1, image_record* h2)
{
    uint ret = 0;
    double up = 0.0;
    double down = 0.0;
    uint dimm = h1->dimmension;

    for (uint i = 0; i < dimm; i++)
    {
        for (uint j = 0; j < dimm; j++)
        {
            for (uint k = 0; k < dimm; k++)
            {
                uint a = h1->getVar(i, j, k);
                uint b = h2->getVar(i, j, k);
                up += (a * b);
                down += a;
            }
        }
    }

    ret = (uint)(up / down);
    return ret;
}
