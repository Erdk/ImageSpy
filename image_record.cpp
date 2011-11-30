#include "image_record.h"

uint image_record::getVar(uint i, uint j, uint k) const
{
    return *(histogram + i * dimmension * dimmension + j * dimmension + k);
}

void image_record::setVar(uint i, uint j, uint k, uint var)
{
    *(histogram + i * dimmension * dimmension + j * dimmension + k) = var;
}
