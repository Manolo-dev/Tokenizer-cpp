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

void Node::add(std::string key, Node newNode) {
    _childs.insert(std::pair<std::string, Node &>(key, newNode));
}

void Node::change(std::string key, Node changedNode) {
    std::map<std::string, Node>::iterator it = _childs.find(key);
    if (it != _childs.end())
        it->second = changedNode;
}

Node & Node::operator[](std::string key) {
    return _childs[key];
}

void Node::print(int level) {
    std::cout << _data << std::endl;
    for(auto & [key, value]: _childs) {
        std::cout << std::string(level * 4, ' ') << key << " ";
        value.print(level + 1);
    }
}

std::ostream & operator<<(std::ostream & os, Node & root) {
    root.print(0);
    return os;
}