//
// Created by Manolo on 14/08/2022.
//

#ifndef TOKENIZER_NODE_H
#define TOKENIZER_NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

enum class typeNode {
    null,
    leaf,
    dict,
    list,
};

class Node {
public:
    Node();
    Node(std::string data);
    Node(std::vector<Node> nodes);
    Node(std::map<std::string, Node> nodes);

    std::string get();
    Node & get(int index);
    Node & get(std::string key);

    Node & operator[](const int index);
    Node & operator[](const std::string key);

    int size();

    void add(std::string newData);
    void add(std::string key, Node newNode);
    void add(int index, Node newNode);

    void change(std::string changedData);
    void change(std::string key, Node changedNode);
    void change(int index, Node changedNode);

    friend std::ostream & operator<<(std::ostream & os, Node & root);
private:
    const void print(int level);

    typeNode _type;
    std::string _data;
    std::vector<Node> _childs_v;
    std::map<std::string, Node> _childs_m;
};

#endif //TOKENIZER_NODE_H
