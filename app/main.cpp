#include "stdafx.hpp"

#include "common.hpp"
#include "command_line_utils/CommandLineUtils.hpp"

namespace {

// NOTE !!!
// For interprocess communication i must use some low level IPC mechanism, for instance sockets, 
// but shared file should be the easiest one.
void writeToSharedSegment(std::string data) {
    
    if(data.empty()) {
        data = "Hello world!";
    }

    const std::lock_guard<std::mutex> lock(g_mutex);
    std::ofstream sharedSegment;
    sharedSegment.open (SharedDataPath);
    if(!sharedSegment.is_open()) {
        std::cerr << "File is not opened" << std::endl;
    }
    sharedSegment << data;
    sharedSegment.close();
}

void readFromSharedSegment() {
    const std::lock_guard<std::mutex> lock(g_mutex);
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
