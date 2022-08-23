#include "Node.h"

Node::Node() {
    _data     = "";
    _childs_m = {};
    _childs_v = {};
    _type     = typeNode::null;
}

Node::Node(std::string && data) {
    _data     = data;
    _childs_m = {};
    _childs_v = {};
    _type     = typeNode::leaf;
}

Node::Node(std::string & data) {
    _data     = data;
    _childs_m = {};
    _childs_v = {};
    _type     = typeNode::leaf;
}

Node::Node(std::vector<Node> && nodes) {
    _data     = "";
    _childs_m = {};
    _childs_v = nodes;
    _type     = typeNode::list;
}

Node::Node(std::vector<Node> & nodes) {
    _data     = "";
    _childs_m = {};
    _childs_v = nodes;
    _type     = typeNode::list;
}

Node::Node(std::map<std::string, Node> && nodes) {
    _data     = "";
    _childs_m = nodes;
    _childs_v = {};
    _type     = typeNode::dict;
}

Node::Node(std::map<std::string, Node> & nodes) {
    _data     = "";
    _childs_m = nodes;
    _childs_v = {};
    _type     = typeNode::dict;
}

std::string Node::get() {
    if(_type != typeNode::leaf) {
        if(_type == typeNode::null) {
            std::cerr << "ERROR: This node is empty." << std::endl;
        } else {
            std::cerr << "ERROR: You cannot call a leaf in a node list or in a node map." << std::endl;
        }
        throw EXIT_FAILURE;
    }

    return _data;
}

Node & Node::get(const unsigned int index) {
    if(_type != typeNode::list) {
        if(_type == typeNode::null) {
            std::cerr << "ERROR: This node is empty." << std::endl;
        } else {
            std::cerr << "ERROR: You cannot call a numbered node in a node map or leaf." << std::endl;
        }
        throw EXIT_FAILURE;
    }

    return _childs_v[index];
}

Node & Node::get(const std::string && key) {
    if(_type != typeNode::dict) {
        if(_type == typeNode::null) {
            std::cerr << "ERROR: This node is empty." << std::endl;
        } else {
            std::cerr << "ERROR: You cannot call a named node in a node list or leaf." << std::endl;
        }
        throw EXIT_FAILURE;
    }

    return _childs_m[key];
}

Node & Node::get(const std::string & key) {
    if(_type != typeNode::dict) {
        if(_type == typeNode::null) {
            std::cerr << "ERROR: This node is empty." << std::endl;
        } else {
            std::cerr << "ERROR: You cannot call a named node in a node list or leaf." << std::endl;
        }
        throw EXIT_FAILURE;
    }

    return _childs_m[key];
}

Node & Node::operator[](const unsigned int index) {
    if(_type != typeNode::list) {
        if(_type == typeNode::null) {
            std::cerr << "ERROR: This node is empty." << std::endl;
        } else {
            std::cerr << "ERROR: You cannot call a numbered node in a node map or leaf." << std::endl;
        }
        throw EXIT_FAILURE;
    }

    return _childs_v[index];
}

Node & Node::operator[](const std::string && key) {
    if(_type == typeNode::dict) {
        if(_type == typeNode::null) {
            std::cerr << "ERROR: This node is empty." << std::endl;
        } else {
            std::cerr << "ERROR: You cannot call a named node in a node list or leaf." << std::endl;
        }
        throw EXIT_FAILURE;
    }

    return _childs_m[key];
}

Node & Node::operator[](const std::string & key) {
    if(_type == typeNode::dict) {
        if(_type == typeNode::null) {
            std::cerr << "ERROR: This node is empty." << std::endl;
        } else {
            std::cerr << "ERROR: You cannot call a named node in a node list or leaf." << std::endl;
        }
        throw EXIT_FAILURE;
    }

    return _childs_m[key];
}

unsigned long long Node::size() {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw EXIT_FAILURE;
    }
    if(_type == typeNode::leaf) {
        std::cerr << "ERROR: You can only get the size of a leaf." << std::endl;
        throw EXIT_FAILURE;
    }
    unsigned long long sizeNode;
    if(_type == typeNode::list) {
        sizeNode = _childs_v.size();
    } else {
        sizeNode = _childs_m.size();
    }

    return sizeNode;
}

void Node::add(std::string && newData) {
    if(_type == typeNode::null) {
        _type = typeNode::leaf;
    }
    if(_type == typeNode::leaf) {
        _data = newData;
    } else {
        std::cerr << "ERROR: You cannot give value to anything other than a leaf." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::add(std::string & newData) {
    if(_type == typeNode::null) {
        _type = typeNode::leaf;
    }
    if(_type == typeNode::leaf) {
        _data = newData;
    } else {
        std::cerr << "ERROR: You cannot give value to anything other than a leaf." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::add(Node && newNode) {
    if(_type == typeNode::null) {
        _type = typeNode::list;
    }
    if(_type == typeNode::list) {
        _childs_v.push_back(newNode);
    } else {
        std::cerr << "ERROR: You cannot give numbered node to anything other than a node list." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::add(Node & newNode) {
    if(_type == typeNode::null) {
        _type = typeNode::list;
    }
    if(_type == typeNode::list) {
        _childs_v.push_back(newNode);
    } else {
        std::cerr << "ERROR: You cannot give numbered node to anything other than a node list." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::add(std::string && key, Node && newNode) {
    if(_type == typeNode::null) {
        _type = typeNode::dict;
    }
    if(_type == typeNode::dict) {
        auto it = _childs_m.find(key);
        if(it != _childs_m.end()) {
            std::cerr << "ERROR: You cannot add a key that already exists." << std::endl;
            throw EXIT_FAILURE;
        }
        _childs_m[key] = newNode;
    } else {
        std::cerr << "ERROR: You cannot give named node to anything other than a node map." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::add(std::string && key, Node & newNode) {
    if(_type == typeNode::null) {
        _type = typeNode::dict;
    }
    if(_type == typeNode::dict) {
        auto it = _childs_m.find(key);
        if(it != _childs_m.end()) {
            std::cerr << "ERROR: You cannot add a key that already exists." << std::endl;
            throw EXIT_FAILURE;
        }
        _childs_m[key] = newNode;
    } else {
        std::cerr << "ERROR: You cannot give named node to anything other than a node map." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::add(std::string & key, Node && newNode) {
    if(_type == typeNode::null) {
        _type = typeNode::dict;
    }
    if(_type == typeNode::dict) {
        auto it = _childs_m.find(key);
        if(it != _childs_m.end()) {
            std::cerr << "ERROR: You cannot add a key that already exists." << std::endl;
            throw EXIT_FAILURE;
        }
        _childs_m[key] = newNode;
    } else {
        std::cerr << "ERROR: You cannot give named node to anything other than a node map." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::add(std::string & key, Node & newNode) {
    if(_type == typeNode::null) {
        _type = typeNode::dict;
    }
    if(_type == typeNode::dict) {
        auto it = _childs_m.find(key);
        if(it != _childs_m.end()) {
            std::cerr << "ERROR: You cannot add a key that already exists." << std::endl;
            throw EXIT_FAILURE;
        }
        _childs_m[key] = newNode;
    } else {
        std::cerr << "ERROR: You cannot give named node to anything other than a node map." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::change(std::string && changedData) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw EXIT_FAILURE;
    }
    if(_type == typeNode::leaf) {
        _data = changedData;
    } else {
        std::cerr << "ERROR: You cannot give value to anything other than a leaf." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::change(std::string & changedData) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw EXIT_FAILURE;
    }
    if(_type == typeNode::leaf) {
        _data = changedData;
    } else {
        std::cerr << "ERROR: You cannot give value to anything other than a leaf." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::change(unsigned int index, Node && changedNode) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw EXIT_FAILURE;
    }
    if(_type == typeNode::list) {
        if(0U < index and index < _childs_v.size()) {
            _childs_v[index] = changedNode;
        } else {
            std::cerr << "ERROR: The item you want to change does not exist." << std::endl;
            throw EXIT_FAILURE;
        }
    } else {
        std::cerr << "ERROR: You cannot give numbered node to anything other than a node list." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::change(unsigned int index, Node & changedNode) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw EXIT_FAILURE;
    }
    if(_type == typeNode::list) {
        if(0U < index and index < _childs_v.size()) {
            _childs_v[index] = changedNode;
        } else {
            std::cerr << "ERROR: The item you want to change does not exist." << std::endl;
            throw EXIT_FAILURE;
        }
    } else {
        std::cerr << "ERROR: You cannot give numbered node to anything other than a node list." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::change(std::string && key, Node && changedNode) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw EXIT_FAILURE;
    }
    if(_type == typeNode::list) {
        auto it = _childs_m.find(key);
        if(it != _childs_m.end()) {
            _childs_m[key] = changedNode;
        } else {
            std::cerr << "ERROR: The item you want to change does not exist." << std::endl;
            throw EXIT_FAILURE;
        }
    } else {
        std::cerr << "ERROR: You cannot give named node to anything other than a node map." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::change(std::string && key, Node & changedNode) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw EXIT_FAILURE;
    }
    if(_type == typeNode::list) {
        auto it = _childs_m.find(key);
        if(it != _childs_m.end()) {
            _childs_m[key] = changedNode;
        } else {
            std::cerr << "ERROR: The item you want to change does not exist." << std::endl;
            throw EXIT_FAILURE;
        }
    } else {
        std::cerr << "ERROR: You cannot give named node to anything other than a node map." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::change(std::string & key, Node && changedNode) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw EXIT_FAILURE;
    }
    if(_type == typeNode::list) {
        auto it = _childs_m.find(key);
        if(it != _childs_m.end()) {
            _childs_m[key] = changedNode;
        } else {
            std::cerr << "ERROR: The item you want to change does not exist." << std::endl;
            throw EXIT_FAILURE;
        }
    } else {
        std::cerr << "ERROR: You cannot give named node to anything other than a node map." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::change(std::string & key, Node & changedNode) {
    if(_type == typeNode::null) {
        std::cerr << "ERROR: This node is empty." << std::endl;
        throw EXIT_FAILURE;
    }
    if(_type == typeNode::list) {
        auto it = _childs_m.find(key);
        if(it != _childs_m.end()) {
            _childs_m[key] = changedNode;
        } else {
            std::cerr << "ERROR: The item you want to change does not exist." << std::endl;
            throw EXIT_FAILURE;
        }
    } else {
        std::cerr << "ERROR: You cannot give named node to anything other than a node map." << std::endl;
        throw EXIT_FAILURE;
    }
}

void Node::print(unsigned int level) {
    if(_type == typeNode::leaf) {
        std::cout << _data;
    } else if(_type == typeNode::list) {
        for(Node & child: _childs_v) {
            std::cout << std::string(level * 4U, ' ') << "- " << std::endl;
            child.print(level + 1U);
        }
    } else if(_type == typeNode::dict) {
        for(auto &[key, child]: _childs_m) {
            std::cout << std::endl << std::string(level * 4U, ' ') << key << ": ";
            child.print(level + 1U);
        }
    } else {
        std::cout << "[]" << std::endl;
    }
}

std::ostream & operator<<(std::ostream & os, Node & root) {
    root.print(0U);

    return os;
}