#include "huff_archiver.h"
#include "huff_tree.h"
#include <unordered_map>
#include <vector>
#include <iostream>

void HuffmanArchiver::archive(std::istream &input, std::ostream &output) {
    std::unordered_map<char, size_t> frequencies;
    size_t originalSize = 0;

    char i;
    while (input.get(i)) {
        frequencies[i]++;
        originalSize++;
    }
    if (originalSize == 0) {
        std::cout << 0 << '\n' << 0 << '\n' << 0 << std::endl;
        return;
    }
    input.clear();
    input.seekg(0, std::ios::beg);

    HuffmanTree huffmanTree(frequencies);
    std::unordered_map<char, std::string> codes;
    HuffmanTree::getCode(huffmanTree.getRoot(), "", codes);

    std::streampos bef = output.tellp();
    output.write(reinterpret_cast<char *>(&originalSize), sizeof (decltype(originalSize)));
    HuffmanTree::writeTable(output, codes);
    std::streampos af = output.tellp();
    auto tableSize = af - bef;

    std::string buffer;
    size_t compressedSize = 0;
    char ch;
    while (input.get(ch)) {
        buffer += codes[ch];
        while (buffer.size() >= 8) {
            uint8_t byte = bit::stringToByte(buffer.substr(0, 8));
            output.put(byte);
            buffer = buffer.substr(8);
            compressedSize++;
        }
    }

    uint8_t last = buffer.size();
    if (last > 0) {
        buffer.append(8 - last, '0');
        uint8_t byte = bit::stringToByte(buffer);
        output.put(byte);
        compressedSize++;
    }

    output.put(static_cast<char>(last));

    std::cout << originalSize << '\n' << compressedSize << '\n' << tableSize + 1 << std::endl;
}

void HuffmanArchiver::unarchive(std::istream &input, std::ostream &output) {
    std::unordered_map<char, std::string> codes;
    size_t originalSize = 0;

    std::streampos bef = input.tellg();
    if (!input.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize))) {
        std::cout << 0 << '\n' << 0 << '\n' << 0 << std::endl;
        return;
    }

    HuffmanTree::readTable(input, codes);
    std::streampos af = input.tellg();
    auto tableSize = af - bef;

    HuffmanTree huffmanTree;
    huffmanTree.buildTree(codes);

    input.seekg(-1, std::ios::end);
    uint8_t last = input.get();
    std::streampos end = input.tellg();
    input.seekg(sizeof(originalSize), std::ios::beg);

    input.get();
    for (const auto& [symbol, code]: codes) {
        input.get();
        uint8_t length = input.get();
        for (uint8_t j = 0; j < length; ++j) {
            input.get();
        }
    }

    HuffmanTreeNode *root = huffmanTree.getRoot();
    HuffmanTreeNode *currentNode = root;
    size_t compressedSize = 0;
    uint8_t buffer = 0;
    int bitsLeft = 0;

    size_t bytesRead = 0;
    input.seekg(af);

    while (bytesRead < -tableSize || bitsLeft > 0) {
        if (bitsLeft == 0) {
            if (!input.read(reinterpret_cast<char*>(&buffer), 1)) {
                break;
            }
            compressedSize++;
            bytesRead++;
            bitsLeft = 8;
        }

        bool bit = buffer & (1 << (bitsLeft - 1));
        bitsLeft--;

        currentNode = bit ? currentNode->getRight() : currentNode->getLeft();

        if (currentNode->isLeaf()) {
            char d = currentNode->getData();
            output.write(reinterpret_cast<const char*>(&d), 1);
            currentNode = root;
            if (--originalSize == 0) {
                break;
            }
        }

        if (bytesRead == (end - af) && bitsLeft <= 8 - last) {
            break;
        }
    }

    size_t decompressedSize = output.tellp();
    std::cout << compressedSize << '\n' << decompressedSize << '\n' << tableSize + 1 << std::endl;
}