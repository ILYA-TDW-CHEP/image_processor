#include "filterpipeline.h"

FilterPipeline::~FilterPipeline() {
    for (auto filter : coll_) {
        delete filter;
    }
}

bool FilterPipeline::Apply(Image* img) const {
    for (const BaseFilter* filter : coll_) {
        if (!filter) {
            throw std::invalid_argument("Filter is null.");
        }
        filter->Apply(img);
    }
    return true;
}

BaseFilter* FilterPipeline::AddFilter(BaseFilter* filter) {
    coll_.push_back(filter);
    return filter;
}