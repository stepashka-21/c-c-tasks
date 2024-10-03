#ifndef HW_02_HUFFMAN_HUFF_TREE_H
#define HW_02_HUFFMAN_HUFF_TREE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include <istream>

class HuffmanTreeNode {
public:
    explicit HuffmanTreeNode(char data = '\0', size_t freq = 0);
    [[nodiscard]] char getData() const;
    [[nodiscard]] size_t getFrequency() const;
    [[nodiscard]] HuffmanTreeNode* getLeft() const;
    [[nodiscard]] HuffmanTreeNode* getRight() const;
    void setData(char dat);
    void setLeft(std::unique_ptr<HuffmanTreeNode> node);
    void setRight(std::unique_ptr<HuffmanTreeNode> node);
    [[nodiscard]] bool isLeaf() const;
private:
    char data;
    size_t frequency;
    std::unique_ptr<HuffmanTreeNode> left;
    std::unique_ptr<HuffmanTreeNode> right;
};

struct Comparator {
    bool operator()(const std::unique_ptr<HuffmanTreeNode>& l, const std::unique_ptr<HuffmanTreeNode>& r) const;
};

class HuffmanTree {
public:
    HuffmanTree();
    explicit HuffmanTree(const std::unordered_map<char, size_t>& frequencies);
    [[nodiscard]] HuffmanTreeNode* getRoot() const;
    static void getCode(HuffmanTreeNode* node, const std::string& code, std::unordered_map<char, std::string>& codes);
    static void writeTable(std::ostream& os, const std::unordered_map<char, std::string>& codes);
    static void readTable(std::istream& is, std::unordered_map<char, std::string>& codes);
    void buildTree(const std::unordered_map<char, std::string>& codes);

private:
    std::unique_ptr<HuffmanTreeNode> root;
};

#endif //HW_02_HUFFMAN_HUFF_TREE_H
