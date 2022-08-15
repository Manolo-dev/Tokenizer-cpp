//
// Created by Manolo on 14/08/2022.
//

#ifndef TOKENIZER_NODE_H
#define TOKENIZER_NODE_H

#include <iostream>
#include <string>
#include <map>

class Node {
public:
    Node();
    Node(std::map<std::string, Node> nodes);
    Node(std::string data);
    std::map<std::string, Node> & getall();
    Node & get(std::string index);
    std::string get();
    int size();
private:
    std::string _data;
    std::map<std::string, Node> _childs;
};

void print(const Node & root, int level);
std::ostream& operator<<(std::ostream& os, Node & root);

#endif //TOKENIZER_NODE_H
