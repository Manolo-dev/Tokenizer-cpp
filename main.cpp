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

    std::string line;
    unsigned int tab{0U};
    std::string key;
    Node value;

    while(getline(grammarFile, line)) {
        unsigned int i = 0U;
        while(line[i] == '\t' and i < line.size()) i++;

        line = line.substr(i);

        if(i > tab) {
            currentNode.push(&currentNode.top()->get(key));
            tab++;
        }

        while(i < tab) {
            currentNode.pop();
            tab--;
        }

        if(line.substr(line.size() - 1U) == ":") {
            key   = line.substr(0U, line.size() - 1U);
            value = Node{};
            currentNode.top()->add(key, value);
        }

        if(line.find(": ") != std::string::npos) {
            key   = line.substr(0U, line.find(": "));
            value = Node(line.substr(line.find(": ") + 2U));
            currentNode.top()->add(key, value);
        }
    }

    std::cout << root;

    return root;
}

int main() {
    const std::string grammarNameFile("D:/workspace/Tokenizer/test.txt");
    std::ifstream grammarFile(grammarNameFile);

    if(grammarFile) {
        Node grammar{parser(grammarFile)};
    } else {
        std::cerr << "ERROR: Unable to open grammar file." << std::endl;
    }

    return 0;
}