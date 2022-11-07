#include "stdafx.hpp"

#include "common.hpp"
#include "command_line_utils/CommandLineUtils.hpp"

namespace {

void writeToSharedSegment(const std::string& data) {
    std::ofstream sharedSegment;
    sharedSegment.open (SharedDataPath);
    if(!sharedSegment.is_open()) {
        std::cerr << "File is not opened" << std::endl;
    }
    sharedSegment << data;
    sharedSegment.close();
}

void readFromSharedSegment() {
    std::ifstream sharedSegment;
    sharedSegment.open (SharedDataPath);
    if(!sharedSegment.is_open()) {
        std::cerr << "File is not opened" << std::endl;
    }
    std::string fileContent;
    sharedSegment >> fileContent;
    std::cout << "Shared data is: " << fileContent;
    sharedSegment.close();
}

}; // namespace

int main(int argc, const char* argv[]){
    const auto [ isProducer, inputText ] = commandLineUtils::CommandLineUtils::parse(argc, argv);

    // Start producer process and add data into shared resource
    if(isProducer) {
        std::thread producerThread([data = inputText] {
            writeToSharedSegment(data);
        });
        producerThread.join();
    }
    // Start client process and read data from shared resource 
    else {
        std::thread clientThread([] {
            readFromSharedSegment();
        });
        clientThread.join();
    }

    return 0;
}
