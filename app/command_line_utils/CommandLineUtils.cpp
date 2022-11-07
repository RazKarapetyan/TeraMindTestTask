#include "CommandLineUtils.hpp"

namespace commandLineUtils {

std::tuple<bool, std::string> CommandLineUtils::parse(int argc, const char* argv[])  {

    bool isProducer = false;
    bool isClient = false;
    std::string inputText;
    try {
        namespace po = boost::program_options;
        po::options_description description("App Usage");
        description.add_options()("help,h", "Display help message")
            ("producer,p", po::bool_switch()->default_value(false), "Act as a producer")
            ("client,c",  po::bool_switch()->default_value(false), "Act as a client")
            ("input-text,t", po::value<std::string>(&inputText)->required(), "Input text");

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(description).run(), vm);

        if (vm.count("help")) {
            std::cout << description;
            return {};
        }

        isProducer = vm["producer"].as<bool>();
        isClient = vm["client"].as<bool>();

        //TODO: clean: only for debugging
        std::cout << "isProducer: = " << isProducer << std::endl;
        std::cout << "isClient: = " << isClient << std::endl;
        std::cout << "text: = " << inputText << std::endl;
        
        if (isProducer && isClient) {
            std::cerr << "Command line arguments parsing error: please specify one kind of mode" << std::endl;
            return {};
        }

        if (!isProducer && !isClient) {
            std::cerr << "Command line arguments parsing error: please specify opeating mode" << std::endl;
            return {};
        }

        if (isClient && !inputText.empty()) {
            std::cerr << "Command line arguments parsing error: please specify text only in producer mode" << std::endl;
            return {};
        }

        po::notify(vm);
    } catch (std::exception& e) {
        std::cerr << "Command line arguments parsing error: " << e.what() << std::endl;
        return {};
    } catch (...) {
        std::cerr << "Unknown error!" << std::endl;
        return {};
    }

    return {isProducer , inputText};
}

}; // namespace commandLineUtils
