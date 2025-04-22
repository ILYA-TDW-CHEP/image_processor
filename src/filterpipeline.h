#ifndef FILTERPIPELINE_H
#define FILTERPIPELINE_H

#include <vector>

#include "image_and_etc/dib.h"
#include "filters/filter.h"

class FilterPipeline {
public:
    using FilterCollection = std::vector<BaseFilter*>;

    ~FilterPipeline();
    bool Apply(Image* img) const;
    BaseFilter* AddFilter(BaseFilter* filter);
    size_t GetFilterCount() const {
        return coll_.size();
    }

protected:
    FilterCollection coll_;
};

#endif  // FILTERPIPELINE_H
