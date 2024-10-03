#include "huff_tree.h"
#include <queue>
#include <iostream>
#include <memory>

HuffmanTreeNode::HuffmanTreeNode(char data, size_t freq) : data(data), frequency(freq), left(nullptr), right(nullptr) {}

char HuffmanTreeNode::getData() const {
    return data;
}

size_t HuffmanTreeNode::getFrequency() const {
    return frequency;
}

void HuffmanTreeNode::setLeft(std::unique_ptr<HuffmanTreeNode> node) {
    left = std::move(node);
}

void HuffmanTreeNode::setRight(std::unique_ptr<HuffmanTreeNode> node) {
    right = std::move(node);
}

HuffmanTreeNode* HuffmanTreeNode::getLeft() const {
    return left.get();
}

HuffmanTreeNode* HuffmanTreeNode::getRight() const {
    return right.get();;
}

void HuffmanTreeNode::setData(char dat) {
    this->data = dat;
}

bool HuffmanTreeNode::isLeaf() const {
    return !left && !right;
}

bool
Comparator::operator()(const std::unique_ptr<HuffmanTreeNode>& l, const std::unique_ptr<HuffmanTreeNode>& r) const {
    return l->getFrequency() > r->getFrequency();
}

HuffmanTree::HuffmanTree(const std::unordered_map<char, size_t>& frequencies) {
    std::priority_queue<std::unique_ptr<HuffmanTreeNode>, std::vector<std::unique_ptr<HuffmanTreeNode>>, Comparator> heap;

    for (const auto& pair : frequencies) {
        heap.push(std::make_unique<HuffmanTreeNode>(pair.first, pair.second));
    }

    if (heap.size() == 1) {
        auto root_node = std::move(const_cast<std::unique_ptr<HuffmanTreeNode>&>(heap.top()));
        heap.pop();
        auto fake_root = std::make_unique<HuffmanTreeNode>('\0', root_node->getFrequency());
        fake_root->setLeft(std::move(root_node));
        heap.push(std::move(fake_root));
    }

    while (heap.size() > 1) {
        auto left = std::move(const_cast<std::unique_ptr<HuffmanTreeNode>&>(heap.top()));
        heap.pop();
        auto right = std::move(const_cast<std::unique_ptr<HuffmanTreeNode>&>(heap.top()));
        heap.pop();

        auto comb = std::make_unique<HuffmanTreeNode>('\0', left->getFrequency() + right->getFrequency());
        comb->setLeft(std::move(left));
        comb->setRight(std::move(right));
        heap.push(std::move(comb));
    }

    root = std::move(const_cast<std::unique_ptr<HuffmanTreeNode>&>(heap.top()));
    heap.pop();
}

HuffmanTree::HuffmanTree() : root(std::make_unique<HuffmanTreeNode>()) {}

HuffmanTreeNode* HuffmanTree::getRoot() const {
    return root.get();
}

void HuffmanTree::getCode(HuffmanTreeNode* node, const std::string& code, std::unordered_map<char, std::string>& codes) {
    if (!node) return;
    if (node->getLeft() == nullptr && node->getRight() == nullptr) {
        codes[node->getData()] = code;
    }
    getCode(node->getLeft(), code + "0", codes);
    getCode(node->getRight(), code + "1", codes);
}

void HuffmanTree::writeTable(std::ostream& output, const std::unordered_map<char, std::string>& codes) {
    output.put(static_cast<char>(codes.size()));
    for (const auto& pair : codes) {
        output.put(pair.first);
        auto length = static_cast<char>(pair.second.size());
        output.put(length);
        for (char bit : pair.second) {
            output.put(bit == '1' ? 1 : 0);
        }
    }
}

void HuffmanTree::readTable(std::istream& input, std::unordered_map<char, std::string>& codes) {
    auto size = static_cast<size_t>(input.get());
    if (size == 0) { // если длина 256, то будет 256 mod 256 = 0, но таблица непустая
        size = 256;
    }
    for (size_t i = 0; i < size; ++i) {
        char symbol = input.get();
        uint8_t length = input.get();
        std::string code;
        for (uint8_t j = 0; j < length; ++j) {
            code += (input.get() == 1 ? '1' : '0');
        }
        codes[symbol] = code;
    }
}

void HuffmanTree::buildTree(const std::unordered_map<char, std::string>& codes) {
    if (codes.size() == 1) {
        root->setLeft(std::make_unique<HuffmanTreeNode>());
    }
    for (const auto& pair : codes) {
        HuffmanTreeNode* node = root.get();
        for (char bit : pair.second) {
            if (bit == '0') {
                if (!node->getLeft()) {
                    node->setLeft(std::make_unique<HuffmanTreeNode>());
                }
                node = node->getLeft();
            } else {
                if (!node->getRight()) {
                    node->setRight(std::make_unique<HuffmanTreeNode>());
                }
                node = node->getRight();
            }
        }
        node->setData(pair.first);
    }
}
