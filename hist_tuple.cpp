#include "hist_tuple.h"

uint hist_tuple::getVar(uint i, uint j, uint k) const
{
    return *(histogram + i * dimmension * dimmension + j * dimmension + k);
}

void hist_tuple::setVar(uint i, uint j, uint k, uint var)
{
    *(histogram + i * dimmension * dimmension + j * dimmension + k) = var;
}
