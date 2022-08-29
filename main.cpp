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
 * * <vector>
 * * <numeric>
 * * "Node.h"
 */

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <numeric>
#include "Node.h"

Node parser(std::ifstream & grammarFile) {
    Node root{};
    std::stack<Node *> currentNode;
    currentNode.push(&root);

    std::string line;
    std::vector<unsigned int> tab;
    Node value;
    std::string tempValue;
    tab.push_back(0U);

    while(std::getline(grammarFile, line)) {
        while(line.back() == ' ' or line.back() == '\t') {line = line.substr(0U, line.size() - 1U);}
        if(line == "") {continue;}

        size_t i;
        for(i = 0U; line[i] == ' ' and i != std::string::npos; i++) {}

        line = line.substr(i);

        unsigned int totalTab = std::accumulate(tab.begin(), tab.end(), 0U);
        if(i > totalTab) {
            tab.push_back(static_cast<unsigned int>(i - totalTab));
            totalTab += static_cast<unsigned int>(i - totalTab);
        }

        while(i < totalTab) {
            currentNode.pop();
            tab.pop_back();
            totalTab = std::accumulate(tab.begin(), tab.end(), 0U);
        }

        if(i != totalTab) {
            std::cerr << "The tab return is incorrect." << std::endl;
            throw EXIT_FAILURE;
        }

        if(line.substr(0U, 2U) == "- " or line.substr(0U, 2U) == "-\t") {
            if(currentNode.top()->type() == typeNode::null) {
                currentNode.top()->type(typeNode::list);
            }

            if(currentNode.top()->type() == typeNode::dict) {
                currentNode.pop();
                currentNode.top()->add(Node{Node{typeNode::list}});
                currentNode.push(currentNode.top()->last());
            }

            line = line.substr(2U);

            while(line.substr(0U, 2U) == "- " or line.substr(0U, 2U) == "-\t") {
                line = line.substr(2U);

                currentNode.top()->add(Node{Node{typeNode::list}});
                currentNode.push(currentNode.top()->last());
                tab.push_back(2U);
                totalTab += 2U;
            }

            tempValue = line;
            currentNode.top()->add(Node{});
            currentNode.push(currentNode.top()->last());
            goto extract;
        }

        if(line.substr(line.size() - 1U) == ":") {
            std::string key;
            key   = line.substr(0U, line.size() - 1U);
            value = Node{};
            currentNode.top()->add(key, value);
            currentNode.push(&currentNode.top()->get(key));
            continue;
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

            tempValue = line.substr(line.find(": ") + 2U);
            currentNode.top()->add(key, Node{});
            currentNode.push(currentNode.top()->last());
            goto extract;
        }
        continue;

        extract:
        while(tempValue.front() == ' ' or tempValue.front() == '\t') {tempValue = tempValue.substr(1U);}

        if(tempValue == "|") {
            tempValue = "";
            std::string tempLine;
            std::vector<size_t> tempTab;
            std::streampos oldLine;
            do {
                oldLine = grammarFile.tellg();
                if(!static_cast<bool>(std::getline(grammarFile, tempLine))) {break;}
                size_t j;
                for(j = 0U; tempLine[j] == ' ' and j != std::string::npos; j++) {}
                tempTab.push_back(j);
                if(tempTab.back() <= totalTab) {break;}
                tempValue += tempLine.substr(tempTab.front()) + "\\n";
            } while(true);

            if(tempValue.size() > 0U) {
                tempValue = tempValue.substr(0U, tempValue.size() - 2U);
            }

            if(grammarFile.seekg(oldLine, std::ios::beg)) {}
            currentNode.top()->add(tempValue);
        } else if(tempValue == ">") {
            tempValue = "";
            std::string tempLine;
            std::vector<size_t> tempTab;
            std::streampos oldLine;
            do {
                oldLine = grammarFile.tellg();
                if(!static_cast<bool>(std::getline(grammarFile, tempLine))) {break;}
                size_t j;
                for(j = 0U; tempLine[j] == ' ' and j != std::string::npos; j++) {}
                tempTab.push_back(j);
                if(tempTab.back() <= totalTab) {break;}
                if(tempLine == "") {
                    tempLine = "\n";
                }
                tempValue += tempLine.substr(tempTab.front());
            } while(tempTab.back() > totalTab);

            if(grammarFile.seekg(oldLine, std::ios::beg)) {}
            currentNode.top()->add(tempValue);
        } else {
            currentNode.top()->add(tempValue);
        }

        currentNode.pop();
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