#ifndef FILTERCREATORS_H
#define FILTERCREATORS_H

#include <map>

#include "cmd_line_parser/cmd_line_args_parser.h"
#include "filters/filter.h"
#include "filterpipeline.h"

BaseFilter* CreateMyFilterFromCmdArgs(const FilterDescriptor* fd);
BaseFilter* CreateBlurFilterFromCmdArgs(const FilterDescriptor* fd);
BaseFilter* CreateCropFilterFromCmdArgs(const FilterDescriptor* fd);
BaseFilter* CreateEdgeFilterFromCmdArgs(const FilterDescriptor* fd);
BaseFilter* CreateGsFilterFromCmdArgs(const FilterDescriptor* fd);
BaseFilter* CreateNegFilterFromCmdArgs(const FilterDescriptor* fd);
BaseFilter* CreateSharpFilterFromCmdArgs(const FilterDescriptor* fd);
BaseFilter* CreateMosaicFilterFromCmdArgs(const FilterDescriptor* fd);
BaseFilter* CreateBlurFilterFromCmdArgs(const FilterDescriptor* fd);

class FilterCreatorFactory {
public:
    using PFunFilterCreator = BaseFilter* (*)(const FilterDescriptor* fd);
    using FilterName2CreatorMap = std::map<std::string, PFunFilterCreator>;

    BaseFilter* CreateFilter(const FilterDescriptor* fd);
    FilterPipeline CreatePipeline(const CmdLineArgsParser::FilterDescriptors& descriptors);
    void RegisterFilterCreator(const std::string& filter_name, PFunFilterCreator filter_creator);

protected:
    FilterName2CreatorMap filter_creator_mapping_;
};

#endif  // FILTERCREATORS_H
