#include "filtercreators.h"
#include "filters/neg_filter.h"
#include "filters/crop_filter.h"
#include "filters/edge_filter.h"
#include "filters/filter.h"
#include "filters/gs_filter.h"
#include "filters/sharp_filter.h"
#include "filters/mosaic_filter.h"
#include "filters/blur_filter.h"

#include <iostream>

BaseFilter* CreateCropFilterFromCmdArgs(const FilterDescriptor* fd) {
    if (fd->filter_name != "-crop") {
        throw std::logic_error("Invalid filter descriptor.");
    }
    if (fd->GetFilterParamsCount() != 2) {
        throw std::length_error("Invalid filter parameter count.");
    }
    size_t x_crop = atoi(fd->filter_params[0].data());
    size_t y_crop = atoi(fd->filter_params[1].data());

    CropFilter* filter = new CropFilter(x_crop, y_crop);
    return filter;
}

BaseFilter* CreateEdgeFilterFromCmdArgs(const FilterDescriptor* fd) {
    if (fd->filter_name != "-edge") {
        throw std::logic_error("Invalid filter descriptor.");
    }
    if (fd->GetFilterParamsCount() != 1) {
        throw std::length_error("Invalid filter parameter count.");
    }
    double th = atof(fd->filter_params[0].data());

    EdgeFilter* filter = new EdgeFilter(th);
    return filter;
}

BaseFilter* CreateGsFilterFromCmdArgs(const FilterDescriptor* fd) {
    if (fd->filter_name != "-gs") {
        throw std::logic_error("Invalid filter descriptor.");
    }
    GsFilter* filter = new GsFilter();
    return filter;
}

BaseFilter* CreateNegFilterFromCmdArgs(const FilterDescriptor* fd) {
    if (fd->filter_name != "-neg") {
        throw std::logic_error("Invalid filter descriptor.");
    }
    NegFilter* filter = new NegFilter();
    return filter;
}

BaseFilter* CreateSharpFilterFromCmdArgs(const FilterDescriptor* fd) {
    if (fd->filter_name != "-sharp") {
        throw std::logic_error("Invalid filter descriptor.");
    }
    SharpFilter* filter = new SharpFilter();
    return filter;
}

BaseFilter* FilterCreatorFactory::CreateFilter(const FilterDescriptor* fd) {
    auto filter_creator_it = filter_creator_mapping_.find(fd->filter_name);
    if (filter_creator_it == filter_creator_mapping_.end()) {
        return nullptr;
    }
    PFunFilterCreator filter_creator = filter_creator_it->second;
    if (!filter_creator) {
        throw std::logic_error("Creator cannot be null function.");
    }
    BaseFilter* filter = filter_creator(fd);
    return filter;
}

FilterPipeline FilterCreatorFactory::CreatePipeline(const CmdLineArgsParser::FilterDescriptors& descriptors) {
    FilterPipeline pipeline;
    for (const FilterDescriptor& descr : descriptors) {
        BaseFilter* filter = CreateFilter(&descr);
        pipeline.AddFilter(filter);
    }

    return pipeline;
}

void FilterCreatorFactory::RegisterFilterCreator(const std::string& filter_name, PFunFilterCreator filter_creator) {
    filter_creator_mapping_.insert({filter_name, filter_creator});
}

BaseFilter* CreateMosaicFilterFromCmdArgs(const FilterDescriptor* fd) {
    if (fd->filter_name != "-mosaic") {
        throw std::logic_error("Invalid filter descriptor.");
    }
    if (fd->GetFilterParamsCount() != 1) {
        throw std::length_error("Invalid filter parameter count.");
    }
    size_t dist = atoi(fd->filter_params[0].data());

    MosaicFilter* filter = new MosaicFilter(dist);
    return filter;
}

BaseFilter* CreateBlurFilterFromCmdArgs(const FilterDescriptor* fd) {
    if (fd->filter_name != "-blur") {
        throw std::logic_error("Invalid filter descriptor.");
    }
    if (fd->GetFilterParamsCount() != 1) {
        throw std::length_error("Invalid filter parameter count.");
    }
    double sigma = atof(fd->filter_params[0].data());

    BlurFilter* filter = new BlurFilter(sigma);
    return filter;
}