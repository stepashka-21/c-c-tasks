#ifndef HW_02_HUFFMAN_HUFF_ARCHIVER_H
#define HW_02_HUFFMAN_HUFF_ARCHIVER_H

#include <string>
#include <unordered_map>
#include <bitset>

class HuffmanArchiver {
public:
    static void archive(std::istream& input, std::ostream& output);
    static void unarchive(std::istream& input, std::ostream& output);
};

namespace bit {
    inline uint8_t stringToByte(const std::string& str) {
        return static_cast<uint8_t>(std::bitset<8>(str).to_ulong());
    }

    inline std::string byteToString(uint8_t byte) {
        return std::bitset<8>(byte).to_string();
    }
}

#endif //HW_02_HUFFMAN_HUFF_ARCHIVER_H
