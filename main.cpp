/**
 * Module C++ d'analyse syntaxique et de grammaire, tokenization
 * @name: Tokenizer
 * @version: 0.1
 * @date: 14/08/2022
 * @authors: Manolo Sardo
 * @functions:
 * @datas:
 * @imports:
 */

#include <iostream>
#include "Node.h"

using namespace std;

int main() {
    Node root({
        {"variables", Node({
            {"open", Node("(")},
            {"close", Node(")")}
        })},
        {"main", Node({
            {"match", Node("\\s\\S")},
            {"save", Node("empty")}
        })}
    });
    cout << root;
    return 0;
}