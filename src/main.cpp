#include "cmd_line_parser/cmd_line_args_parser.h"
#include "filtercreators.h"
#include <iostream>

void AppRun(const int argc, char* argv[]) {
    FilterCreatorFactory factory;
    factory.RegisterFilterCreator("-crop", CreateCropFilterFromCmdArgs);
    factory.RegisterFilterCreator("-gs", CreateGsFilterFromCmdArgs);
    factory.RegisterFilterCreator("-neg", CreateNegFilterFromCmdArgs);
    factory.RegisterFilterCreator("-sharp", CreateSharpFilterFromCmdArgs);
    factory.RegisterFilterCreator("-edge", CreateEdgeFilterFromCmdArgs);
    factory.RegisterFilterCreator("-mosaic", CreateMosaicFilterFromCmdArgs);
    factory.RegisterFilterCreator("-blur", CreateBlurFilterFromCmdArgs);
    CmdLineArgsParser cmd_parser;
    CmdLineArgsParser::ErrorCode res = cmd_parser.Parse(argc, argv);
    if (res != CmdLineArgsParser::ErrorCode::Ok) {
        return;
    }
    Image img;
    if (!img.ReadFromBMPFile(cmd_parser.GetInFileName())) {
        return;
    }
    FilterPipeline pipeline{factory.CreatePipeline(cmd_parser.GetFilterDescriptors())};
    pipeline.Apply(&img);
    img.SaveToBMPFile(cmd_parser.GetOutFileName());
}

int main(const int argc, char* argv[]) {
    try {
        AppRun(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "К сожалению, работа програмыы завершилось исключением, просьба убедиться, "
                     "что приложение используется стандартно его назначению. \n "
                     "Для получения справки заупстите приложение без аргументов командной строки \n"
                     "Текст исключения: "
                  << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
