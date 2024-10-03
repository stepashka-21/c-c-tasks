#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "huff_archiver.h"

// void console(std::vector<std::string>& args) {
//     std::string input;
//     std::getline(std::cin, input);

//     std::istringstream iss(input);
//     std::string arg;
//     while (iss >> arg) {
//         args.push_back(arg);
//     }
// }

struct ParseResult {
    int errorCode;
    int archive;
    int unarchive;
    std::string inputFilePath;
    std::string outputFilePath;
};

ParseResult parseArguments(const std::vector<std::string>& argv) {
    ParseResult result = {0, 0, 0, "", ""};
    if (argv.size() < 5) {
        result.errorCode = 1;
    }
    for (int i = 1; i < argv.size(); ++i) {
        const std::string& arg = argv[i];
        if (arg == "-c") {
            result.archive = 1;
        } else if (arg == "-u") {
            result.unarchive = 1;
        } else if (arg == "-f" || arg == "--file") {
            if (i + 1 < argv.size()) {
                result.inputFilePath = argv[++i];
            } else {
                result.errorCode = 1;
                printf("111");
            }
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argv.size()) {
                result.outputFilePath = argv[++i];
            } else {
                result.errorCode = 1;
                printf("222");
            }
        } else {
            result.errorCode = 1;
            printf("333");
        }
    }

    if (result.inputFilePath.empty() || result.outputFilePath.empty() || result.archive * result.unarchive == 1) {
        result.errorCode = 1;
    }
    return result;
}

int main(int argc, char* argv[]) {
   std::vector<std::string> args(argv, argv + argc);
    // std::vector<std::string> args;
    // console(args);

    auto result = parseArguments(args);
    if (result.errorCode == 1) {
        std::cerr << " Error to parse commands" << std::endl;
        return 1;
    }

    std::ifstream inputFile(result.inputFilePath, std::ios::binary);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    std::ofstream outputFile(result.outputFilePath, std::ios::binary);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    try {
        if (result.archive == 1) {
            HuffmanArchiver::archive(inputFile, outputFile);
        } else if (result.unarchive == 1) {
            HuffmanArchiver::unarchive(inputFile, outputFile);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

// -c -f ../tests/sample.txt -o ../tests/out.txt
// -u -f ../tests/out.txt -o ../tests/ou.txt