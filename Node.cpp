#include "Node.h"

Node::Node() {
    _data   = "";
    _childs = {};
}

Node::Node(std::map<std::string, Node> nodes) {
    _data   = "";
    _childs = nodes;
}

Node::Node(std::string data) {
    _data   = data;
    _childs = {};
}

std::map<std::string, Node> & Node::getall() {
    return _childs;
}

Node & Node::get(const std::string key) {
    return _childs[key];
}

std::string Node::get() {
    return _data;
}

int Node::size() {
    return _childs.size();
}

void print(Node & root, int level) {
    std::cout << root.get() << std::endl;
    for(auto & [key, value]: root.getall()) {
        std::cout << std::string(level * 4, ' ') << key << " ";
        print(value, level + 1);
    }
}

std::ostream& operator<<(std::ostream& os, Node & root) {
    print(root, 0);
    return os;
}