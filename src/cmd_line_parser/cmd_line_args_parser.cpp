#include "cmd_line_args_parser.h"
#include <iostream>

void PrintHelpMenu() {
    std::cout << R"(
        ****************************************
        |            Image Processor           |
        ========================================

        Формат ввода:
          ./image_processor <input> <output> [-<filter1> [options]] [-<filter2> [options]] ...

        Список фильтров:
          Crop (-crop width height)                 Обрезает изображение до заданных ширины и высоты
          Grayscale (-gs)                           Преобразует изображение в оттенки серого
          Negative (-neg)                           Преобразует изображение в негатив
          Sharpening (-sharp)                       Повышение резкости изображения
          Edge Detection (-edge threshold)          Выделение границ (0 <= threshold <= 1)
          Blur (-blur sigma)                        Размытие изображения
          Mosaic (-mosaic distance)                 Создаёт мозаику (рекомендуется distance > 40)

        Примеры:
          ./image_processor input.bmp output.bmp -gs
          ./image_processor in.bmp out.bmp -mosaic 60
        )";
}

CmdLineArgsParser::ErrorCode CmdLineArgsParser::Parse(int argc, char *argv[]) {
    if (argc == 1) {
        PrintHelpMenu();
        return ErrorCode::Help;
    }
    if (argc < MIN_ARG_COUNT) {
        std::cout << "You must provide at least two arguments." << std::endl;
        return ErrorCode::NotEnoughArgs;
    }

    in_file_name_ = argv[InputFilePos];
    out_file_name_ = argv[OutputFilePos];

    for (int i = FilterStartPos; i < argc; ++i) {
        FilterDescriptor filter;
        filter.filter_name = argv[i];
        ++i;
        while (i < argc && argv[i][0] != FilterStartSign) {
            filter.filter_params.push_back(argv[i]);
            ++i;
        }
        --i;
        filter_descriptors_.push_back(filter);
    }

    return ErrorCode::Ok;
}
