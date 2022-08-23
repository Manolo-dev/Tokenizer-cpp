#include "Node.h"

Node::Node() {
    _data     = "";
    _childs_m = {};
    _childs_v = {};
    _type     = typeNode::null;
}

Node::Node(std::string data) {
    _data     = data;
    _childs_m = {};
    _childs_m = {};
    _type     = typeNode::leaf;
}

Node::Node(std::vector<Node> nodes) {
    _data     = "";
    _childs_m = {};
    _childs_v = nodes;
    _type     = typeNode::list;
}

Node::Node(std::map<std::string, Node> nodes) {
    _data     = "";
    _childs_m = nodes;
    _childs_v = {};
    _type     = typeNode::dict;
}

std::string Node::get() {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw 1;
    }
    if(_type == typeNode::leaf)
        return _data;
    else {
        std::cerr << "ERROR: You cannot call a leaf in a node list or in a node map." << std::endl;
        throw 1;
    }
    return "";
}

Node & Node::get(const int index) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw 1;
    }
    if(_type == typeNode::list)
        return _childs_v[index];
    else {
        std::cerr << "ERROR: You cannot call a numbered node in a node map or leaf." << std::endl;
        throw 1;
    }
}

Node & Node::get(const std::string key) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw 1;
    }
    if(_type == typeNode::dict)
        return _childs_m[key];
    else {
        std::cerr << "ERROR: You cannot call a named node in a node list or leaf." << std::endl;
        throw 1;
    }
}

Node & Node::operator[](const int index) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw 1;
    }
    if(_type == typeNode::list)
        return _childs_v[index];
    else {
        std::cerr << "ERROR: You cannot call a numbered node in a node map or leaf." << std::endl;
        throw 1;
    }
}

Node & Node::operator[](const std::string key) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw 1;
    }
    if(_type == typeNode::dict)
        return _childs_m[key];
    else {
        std::cerr << "ERROR: You cannot call a named node in a node list or leaf." << std::endl;
        throw 1;
    }
}

int Node::size() {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw 1;
    }
    if(_type == typeNode::leaf) {
        std::cerr << "ERROR: You can only get the size of a leaf." << std::endl;
        throw 1;
    }
    else if(_type == typeNode::list)
        return _childs_v.size();
    else if(_type == typeNode::dict)
        return _childs_m.size();
    else
        throw 1;
}

void Node::add(std::string newData) {
    if(_type == typeNode::null)
        _type = typeNode::leaf;
    if(_type == typeNode::leaf)
        _data = newData;
    else {
        std::cerr << "ERROR: You cannot give value to anything other than a leaf." << std::endl;
        throw 1;
    }
}

void Node::add(int index, Node newNode) {
    if(_type == typeNode::null)
        _type = typeNode::list;
    if(_type == typeNode::list)
        _childs_v.push_back(newNode);
    else {
        std::cerr << "ERROR: You cannot give numbered node to anything other than a node list." << std::endl;
        throw 1;
    }
}

void Node::add(std::string key, Node newNode) {
    if(_type == typeNode::null)
        _type = typeNode::dict;
    if(_type == typeNode::dict)
        _childs_m.insert(std::pair<std::string, Node &>(key, newNode));
    else {
        std::cerr << "ERROR: You cannot give named node to anything other than a node map." << std::endl;
        throw 1;
    }
}

void Node::change(std::string changedData) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw 1;
    }
    if(_type == typeNode::leaf)
        _data = changedData;
    else {
        std::cerr << "ERROR: You cannot give value to anything other than a leaf." << std::endl;
        throw 1;
    }
}

void Node::change(int index, Node changedNode) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw 1;
    }
    if(_type == typeNode::list) {
        if(0 < index and index < _childs_v.size())
            _childs_v[index] = changedNode;
        else {
            std::cerr << "ERROR: The item you want to change does not exist." << std::endl;
            throw 1;
        }
    } else {
        std::cerr << "ERROR: You cannot give numbered node to anything other than a node list." << std::endl;
        throw 1;
    }
}

void Node::change(std::string key, Node changedNode) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw 1;
    }
    if(_type == typeNode::list) {
        if(_childs_m.count(key) > 0)
            _childs_m[key] = changedNode;
        else {
            std::cerr << "ERROR: The item you want to change does not exist." << std::endl;
            throw 1;
        }
    } else {
        std::cerr << "ERROR: You cannot give named node to anything other than a node map." << std::endl;
        throw 1;
    }
}

const void Node::print(int level) {
    if(_type == typeNode::leaf)
        std::cout << _data << std::endl;
    else if(_type == typeNode::list) {
        for(Node & child : _childs_v) {
            std::cout << std::string(level * 4, ' ') << "- " << std::endl;
            child.print(level + 1);
        }
    } else if(_type == typeNode::dict) {
        for(auto & [key, child] : _childs_m) {
            std::cout << std::string(level * 4, ' ') << key << ": " << std::endl;
            child.print(level + 1);
        }
    }
}

std::ostream & operator<<(std::ostream & os, Node & root) {
    root.print(0);
    return os;
}