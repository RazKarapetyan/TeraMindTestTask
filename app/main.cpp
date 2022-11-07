#include "stdafx.hpp"

#include "command_line_utils/CommandLineUtils.hpp"

int main(int argc, const char* argv[]){

    std::cout << "Hello world" << std::endl;
    const auto [ isProducer, inputText ] = commandLineUtils::CommandLineUtils::parse(argc, argv);

    return 0;
}
