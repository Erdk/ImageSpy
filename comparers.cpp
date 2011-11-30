#include "comparers.h"
#include <cmath>

// ok
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

//ok
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

// TODO
uint CosinusHistComparer::operator ()(image_record* h1, image_record* h2)
{
    return 0;
}

// ok
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

// ok
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

// ok
uint MediumLumaHistComparer::operator ()(image_record* h1, image_record* h2)
{
    double luma_h1 = 0.0;
    double norm_h1 = 0.0;

    double luma_h2 = 0.0;
    double norm_h2 = 0.0;

    for (int i = 0; i < h1->dimmension; i++)
    {
        for (int j = 0; j < h1->dimmension; j++)
        {
            for (int k = 0; k < h1->dimmension; k++)
            {
                double i_d, j_d, k_d;
                i_d = (double) i;
                j_d = (double) j;
                k_d = (double) k;
                luma_h1 += (double)h1->getVar(i, j, k) * ((i_d * 16.0 + 8.0) * 0.2126 +
                                                          (j_d * 16.0 + 8.0) * 0.7152 +
                                                          (k_d * 16.0 + 8.0) * 0.0722);
                norm_h1 += (double)h1->getVar(i, j, k);
                luma_h2 += (double)h2->getVar(i, j, k) * ((i_d * 16.0 + 8.0) * 0.2126 +
                                                          (j_d * 16.0 + 8.0) * 0.7152 +
                                                          (k_d * 16.0 + 8.0) * 0.0722);
                norm_h2 += (double)h2->getVar(i, j, k);
            }
        }
    }

    luma_h1 /= norm_h1;
    luma_h2 /= norm_h2;

    return (uint) luma_h1 - luma_h2;
}

// TODO
uint VarianceHistComparer::operator ()(image_record* h1, image_record* h2)
{
    double luma_h1 = 0.0;
    double norm_h1 = 0.0;

    double luma_h2 = 0.0;
    double norm_h2 = 0.0;

    for (int i = 0; i < h1->dimmension; i++)
    {
        for (int j = 0; j < h1->dimmension; j++)
        {
            for (int k = 0; k < h1->dimmension; k++)
            {
                double i_d, j_d, k_d;
                i_d = (double) i;
                j_d = (double) j;
                k_d = (double) k;
                luma_h1 += (double)h1->getVar(i, j, k) * ((i_d * 16.0 + 8.0) * 0.2126 +
                                                          (j_d * 16.0 + 8.0) * 0.7152 +
                                                          (k_d * 16.0 + 8.0) * 0.0722);
                norm_h1 += (double)h1->getVar(i, j, k);
                luma_h2 += (double)h2->getVar(i, j, k) * ((i_d * 16.0 + 8.0) * 0.2126 +
                                                          (j_d * 16.0 + 8.0) * 0.7152 +
                                                          (k_d * 16.0 + 8.0) * 0.0722);
                norm_h2 += (double)h2->getVar(i, j, k);
            }
        }
    }

    luma_h1 /= (norm_h1 * norm_h1);
    luma_h2 /= (norm_h2 * norm_h2);

    return (uint) luma_h1 - luma_h2;
}

//TODO
uint JeffreyHistComparer::operator ()(image_record* h1, image_record* h2)
{
    double ret = 0.0;

    for (int i = 0; i < h1->dimmension * h1->dimmension * h1->dimmension; i++)
    {
        if (h1->histogram[i] > 0)
            ret += (double)h1->histogram[i] * std::log((2.0 * (double)h1->histogram[i]) / ((double)h1->histogram[i] + (double)h2->histogram[i]));
        if (h2->histogram[i] > 0)
            ret += (double)h2->histogram[i] * std::log((2.0 * (double)h2->histogram[i]) / ((double)h1->histogram[i] + (double)h2->histogram[i]));
    }

    return (uint)ret;
}

// TODO
uint KullbackHistComparer::operator ()(image_record* h1, image_record* h2)
{

}
