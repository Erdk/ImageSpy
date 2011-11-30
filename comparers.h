#ifndef COMPARERS_H
#define COMPARERS_H

#include "image_record.h"

class AbstractHistComparer
{
public:
    virtual uint operator ()(image_record* h1, image_record* h2) = 0;
};

class ManhatanHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(image_record* h1, image_record* h2);
};

class EuklidesHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(image_record* h1, image_record* h2);
};

class CosinusHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(image_record* h1, image_record* h2);
};

class CrossSectionHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(image_record* h1, image_record* h2);
};

class NormCorrelationHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(image_record* h1, image_record* h2);
};

class MediumLumaHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(image_record* h1, image_record* h2);
};

class VarianceHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(image_record* h1, image_record* h2);
};

class JeffreyHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(image_record* h1, image_record* h2);
};

class KullbackHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(image_record* h1, image_record* h2);
};

class ChiHistComparer : public AbstractHistComparer
{
public:
    uint operator ()(image_record* h1, image_record* h2);
};

#endif // COMPARERS_H
