#ifndef CMD_LINE_ARGS_PARSER_H
#define CMD_LINE_ARGS_PARSER_H

#include <string>
#include <vector>

struct FilterDescriptor {
    size_t GetFilterParamsCount() const {
        return filter_params.size();
    }
    const char* GetFilterName() const {
        return filter_name.data();
    }

    std::string filter_name;
    std::vector<std::string> filter_params;
};

class CmdLineArgsParser {
public:
    enum class ErrorCode {
        Ok,
        NotEnoughArgs,
        Help,
    };

    using FilterDescriptors = std::vector<FilterDescriptor>;

    const int MIN_ARG_COUNT = 3;
    const int InputFilePos = 1;
    const int OutputFilePos = 2;
    const int FilterStartPos = 3;
    const char FilterStartSign = '-';

    CmdLineArgsParser() : in_file_name_{nullptr}, out_file_name_{nullptr} {
    }
    ErrorCode Parse(int argc, char* argv[]);
    size_t GetFiltersCount() const {
        return filter_descriptors_.size();
    }
    const char* GetInFileName() const {
        return in_file_name_;
    }
    const char* GetOutFileName() const {
        return out_file_name_;
    }
    const FilterDescriptors& GetFilterDescriptors() const {
        return filter_descriptors_;
    }

protected:
    char* in_file_name_;
    char* out_file_name_;

    FilterDescriptors filter_descriptors_;
};

#endif  // CMD_LINE_ARGS_PARSER_H
