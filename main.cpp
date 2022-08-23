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

using namespace std;

Node parser(ifstream & grammarFile) {
    Node root{};
    stack<Node *> currentNode;
    currentNode.push(&root);

    string line;
    int tab{0};
    string key;
    Node value;

    while(getline(grammarFile, line)) {
        int i = 0;
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

        if(line.substr(line.size() - 1) == ":") {
            key   = line.substr(0, line.size() - 1);
            value = Node{};
            currentNode.top()->add(key, value);
        }

        if(line.find(": ") != string::npos) {
            key   = line.substr(0, line.find(": "));
            value = Node(line.substr(line.find(": ") + 2));
            currentNode.top()->add(key, value);
        }
    }

    cout << root;

    return root;
}

int main() {
    string const grammarNameFile("D:/workspace/Tokenizer/test.txt");
    ifstream grammarFile(grammarNameFile);

    if(grammarFile) {
        parser(grammarFile);
    } else {
        cerr << "ERROR: Unable to open grammar file." << endl;
    }

    return 0;
}