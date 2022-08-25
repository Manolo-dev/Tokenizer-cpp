/**
 * Module C++ d'analyse syntaxique et de grammaire, tokenization
 * @name: Tokenizer
 * @version: 0.1
 * @date: 14/08/2022
 * @authors: Manolo Sardo
 * @functions:
 * @datas:
 * @imports:
 * * <iostream>
 * * <fstream>
 * * <stack>
 * * "Node.h"
 */

#include <iostream>
#include <fstream>
#include <stack>
#include "Node.h"

Node parser(std::ifstream & grammarFile) {
    Node root{};
    std::stack<Node *> currentNode;
    currentNode.push(&root);

    std::string  line;
    unsigned int tab{0U};
    Node         value;

    while(getline(grammarFile, line)) {
        unsigned int i;
        for(i = 0U; line[i] == ' ' and i < line.size(); i++);

        line = line.substr(i);

        if(i/2U > tab) {
            tab++;
        }

        while(i/2U < tab) {
            currentNode.pop();
            tab--;
        }

        if(line.substr(0U, 2U) == "- ") {
            if(currentNode.top()->type() == typeNode::null) {
                currentNode.top()->type(typeNode::list);
            }

            if(currentNode.top()->type() == typeNode::dict) {
                currentNode.pop();
                currentNode.top()->add(Node{Node{typeNode::list}});
                currentNode.push(currentNode.top()->last());
            }

            line = line.substr(2U);

            while(line.substr(0U, 2U) == "- ") {
                line = line.substr(2U);

                currentNode.top()->add(Node{Node{typeNode::list}});
                currentNode.push(currentNode.top()->last());
            }

            value = Node(line);
            currentNode.top()->add(value);
        }

        if(line.substr(line.size() - 1U) == ":") {
            std::string key;
            key   = line.substr(0U, line.size() - 1U);
            value = Node{};
            currentNode.top()->add(key, value);
            currentNode.push(&currentNode.top()->get(key));
        }

        if(line.find(": ") != std::string::npos) {
            if(currentNode.top()->type() == typeNode::null) {
                currentNode.top()->type(typeNode::dict);
            }

            if(currentNode.top()->type() == typeNode::list) {
                currentNode.pop();
                currentNode.top()->add(Node{Node{typeNode::dict}});
                currentNode.push(currentNode.top()->last());
            }

            std::string key;
            key   = line.substr(0U, line.find(": "));
            value = Node(line.substr(line.find(": ") + 2U));
            currentNode.top()->add(key, value);
        }
    }

    std::cout << root;

    return root;
}

int main() {
    const std::string grammarNameFile("../test.txt");
    std::ifstream grammarFile(grammarNameFile);

    if(grammarFile) {
        Node grammar{parser(grammarFile)};
    } else {
        std::cerr << "ERROR: Unable to open grammar file." << std::endl;
    }

    return 0;
}