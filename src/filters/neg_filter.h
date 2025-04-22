#ifndef NEG_FILTER_H
#define NEG_FILTER_H

#include "filter.h"

class NegFilter : public BaseFilter {
public:
    NegFilter() = default;
    ~NegFilter() override = default;
    bool Apply(Image* img) const override;
};

#endif  // NEG_FILTER_H
