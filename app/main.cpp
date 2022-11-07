#include "stdafx.hpp"

#include "common.hpp"
#include "command_line_utils/CommandLineUtils.hpp"


int main(int argc, const char* argv[]){
    const auto [ isProducer, inputText ] = commandLineUtils::CommandLineUtils::parse(argc, argv);

    std::ofstream sharedSegment;
    sharedSegment.open (SharedDataPath);
    if(!sharedSegment.is_open()) {
        std::cerr << "File is not opened" << std::endl;
        return -1;
    }
    sharedSegment << inputText;
    sharedSegment.close();

    return 0;
}
