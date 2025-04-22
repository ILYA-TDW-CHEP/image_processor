#ifndef GS_FILTER_H
#define GS_FILTER_H
#include "filter.h"

class GsFilter : public BaseFilter {
public:
    GsFilter() = default;
    ~GsFilter() override = default;
    bool Apply(Image* img) const override;
};

#endif  // GS_FILTER_H
