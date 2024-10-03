#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "huff_archiver.h"
#include "huff_tree.h"
#include <sstream>
#include <string>
#include <cstdlib>
#include <random>

// это нужно?
TEST_CASE("bit test") {
    std::string str, str0;
    uint8_t bit, bit0;

    str0 = "010";
    bit = bit::stringToByte(str0);
    str = bit::byteToString(bit);
    CHECK_EQ("00000" + str0, str);

    str0 = "01000000";
    bit = bit::stringToByte(str0);
    str = bit::byteToString(bit);
    CHECK_EQ(str0, str);

    bit0 = 42;
    str = bit::byteToString(bit0);
    bit = bit::stringToByte(str);
    CHECK_EQ(bit0, bit);

    bit0 = 255;
    str = bit::byteToString(bit0);
    bit = bit::stringToByte(str);
    CHECK_EQ(bit0, bit);
}
// а это?
TEST_CASE("huff_tree test") {
    std::unordered_map<char, size_t> freq = {{'A', 5}, {'B', 3}, {'C', 1}, {'D', 1}, {'E', 1}};
    HuffmanTree tree(freq);
    std::unordered_map<char, std::string> codes;
    tree.getCode(tree.getRoot(), "", codes);
    std::unordered_map<char, std::string> expectedCodes = {
            {'D', "1111"},
            {'E', "1110"},
            {'C', "110"},
            {'B', "10"},
            {'A', "0"},
    };
    for (const auto& pair : expectedCodes) {
        CHECK_EQ(codes[pair.first], pair.second);
    }
}

////////////////////////////////////////////////

//void writeToFile(const std::string &filePath, const std::string &content) {
//    std::ofstream outFile(filePath, std::ios::binary);
//    outFile.write(content.c_str(), content.size());
//}
//
//std::string readFromFile(const std::string &filePath) {
//    std::ifstream inFile(filePath, std::ios::binary);
//    std::ostringstream oss;
//    oss << inFile.rdbuf();
//    return oss.str();
//}

class OutputCatcher {
public:
    OutputCatcher() {
        oldBuf = std::cout.rdbuf();
        std::cout.rdbuf(buffer.rdbuf());
    }

    ~OutputCatcher() {
        std::cout.rdbuf(oldBuf);
    }

    std::string getOutput() {
        return buffer.str();
    }

private:
    std::ostringstream buffer;
    std::streambuf* oldBuf;
};

TEST_SUITE("archiver") {
    TEST_CASE("archive/unarchive empty file") {
        std::string str = "";
        std::stringstream input(str);
        std::stringstream compressed;
        std::stringstream decompressed;
        OutputCatcher outputCatcher1;
        HuffmanArchiver::archive(input, compressed);

        std::istringstream stream1(outputCatcher1.getOutput());
        size_t s1, s2, s3;
        stream1 >> s1 >> s2 >> s3;

        CHECK(s1 == 0);
        CHECK(s2 == 0);
        CHECK(s3 == 0);

        OutputCatcher outputCatcher2;
        HuffmanArchiver::unarchive(compressed, decompressed);

        std::istringstream stream2(outputCatcher2.getOutput());
        size_t ss1, ss2, ss3;
        stream2 >> ss1 >> ss2 >> ss3;

        CHECK(ss1 == 0);
        CHECK(ss2 == 0);
        CHECK(ss3 == 0);

        CHECK(decompressed.str() == str);
    }
    TEST_CASE("archive/unarchive empty file") {
        std::string str(100, 'a');
        str.append(100, 'b');
        str.append(100, 'c');
        std::stringstream input(str);
        std::stringstream compressed;
        std::stringstream decompressed;
        OutputCatcher outputCatcher1;
        HuffmanArchiver::archive(input, compressed);

        std::istringstream stream1(outputCatcher1.getOutput());
        size_t s1, s2, s3;
        stream1 >> s1 >> s2 >> s3;

        CHECK(s1 > s2);

        OutputCatcher outputCatcher2;
        HuffmanArchiver::unarchive(compressed, decompressed);

        std::istringstream stream2(outputCatcher2.getOutput());
        size_t ss1, ss2, ss3;
        stream2 >> ss1 >> ss2 >> ss3;

        CHECK(ss1 < ss2);
        CHECK(ss2 == s1);
        CHECK(ss1 == s2);

        CHECK(decompressed.str() == str);
    }
    TEST_CASE("archive/unarchive str random file") {
        const std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*ƒçˆ˙ç∑øµ˜∫å“∑œ≥æ…()_+Œ„´ÅÎ¸";
        std::string str;
        size_t length = rand() % 1000000 + 1;
        for (size_t i = 0; i < length; ++i) {
            str += letters[rand() % letters.size()];
        }

        std::stringstream input(str);
        std::stringstream compressed;
        std::stringstream decompressed;
        OutputCatcher outputCatcher1;
        HuffmanArchiver::archive(input, compressed);

        std::istringstream stream1(outputCatcher1.getOutput());
        size_t s1, s2, s3;
        stream1 >> s1 >> s2 >> s3;

        CHECK(s1 > s2); // так проверять на то, что случилось сжатие?

        OutputCatcher outputCatcher2;
        HuffmanArchiver::unarchive(compressed, decompressed);

        std::istringstream stream2(outputCatcher2.getOutput());
        size_t ss1, ss2, ss3;
        stream2 >> ss1 >> ss2 >> ss3;

        CHECK(ss1 < ss2);
        CHECK(ss2 == s1);
        CHECK(ss1 == s2);
//        std::cerr << str << " " << decompressed.str() << " " << s1 << " " << s3 << std::endl;
        CHECK(decompressed.str() == str);
    }
    TEST_CASE("archive/unarchive byte random file") {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<> distribution(0, 255);

        std::string str;
        size_t length = rand() % 1000000 + 1;
        for (size_t i = 0; i < length; ++i) {
            str += static_cast<char>(distribution(generator));
        }

        std::stringstream input(str);
        std::stringstream compressed;
        std::stringstream decompressed;
        OutputCatcher outputCatcher1;
        HuffmanArchiver::archive(input, compressed);

        std::istringstream stream1(outputCatcher1.getOutput());
        size_t s1, s2, s3;
        stream1 >> s1 >> s2 >> s3;

        OutputCatcher outputCatcher2;
        HuffmanArchiver::unarchive(compressed, decompressed);

        std::istringstream stream2(outputCatcher2.getOutput());
        size_t ss1, ss2, ss3;
        stream2 >> ss1 >> ss2 >> ss3;

        CHECK(decompressed.str() == str);
    }
}
