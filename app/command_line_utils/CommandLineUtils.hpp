#pragma once

namespace commandLineUtils {

class CommandLineUtils {
public:
    static std::tuple<bool, std::string> parse(int argc, const char* argv[]);
};

} // namespace fileUtils
