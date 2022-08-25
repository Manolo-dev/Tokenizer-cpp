#pragma once

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
    explicit Node(typeNode && type);
    explicit Node(typeNode & type);
    explicit Node(std::string && data);
    explicit Node(std::string & data);
    explicit Node(std::vector<Node> && nodes);
    explicit Node(std::vector<Node> & nodes);
    explicit Node(std::map<std::string, Node> && nodes);
    explicit Node(std::map<std::string, Node> & nodes);

    std::string get();
    typeNode type();
    void type(typeNode newType);

    Node & get(unsigned int index);
    Node & get(const std::string && key);
    Node & get(const std::string & key);

    Node & operator[](unsigned int index);
    Node & operator[](const std::string && key);
    Node & operator[](const std::string & key);

    unsigned long long size();

    Node * last();

    void add(std::string && newData);
    void add(std::string & newData);
    void add(Node && newNode);
    void add(Node & newNode);
    void add(std::string && key, Node && newNode);
    void add(std::string && key, Node & newNode);
    void add(std::string & key, Node && newNode);
    void add(std::string & key, Node & newNode);

    void change(std::string && changedData);
    void change(std::string & changedData);
    void change(unsigned int index, Node && changedNode);
    void change(unsigned int index, Node & changedNode);
    void change(std::string && key, Node && changedNode);
    void change(std::string && key, Node & changedNode);
    void change(std::string & key, Node && changedNode);
    void change(std::string & key, Node & changedNode);

    friend std::ostream & operator<<(std::ostream & os, Node & root);
private:
    void print(unsigned int level);

    typeNode _type;
    std::string _data;
    std::vector<Node> _childs_v;
    std::map<std::string, Node> _childs_m;
    Node * _lastElement;
};
