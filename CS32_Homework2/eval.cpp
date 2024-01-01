//
//  eval.cpp
//  infixBool
//
//  Created by Tom Slavonia on 2/3/23.
//

#include "Set.h"
#include <string>
#include <cstring>
#include <iostream>
#include <stack>
#include <cassert>
#include <cctype>

int evaluate(std::string infix, const Set& trueValues, const Set& falseValues, std::string& postfix, bool& result);
bool isValid(const std::string& infix);
int presedence(const char c);



int evaluate(std::string infix, const Set& trueValues, const Set& falseValues, std::string& postfix, bool& result){
    
    std::stack<char> operators;
    
    postfix = "";
    
    if (isValid(infix) == false) {
        return(1);
    }
    
    for (int i = 0; i < infix.length(); i++) {
        
        if (islower(infix.at(i))) { // case operand
            postfix = postfix + infix.at(i); // appends to end of postfix
            continue;
        }
        else if (infix.at(i) == '(') {
            operators.push(infix.at(i));
            continue;
        }
        else if (infix.at(i) == ')') {
            int count_characters = 0;
            while (operators.top() != '(') {
                postfix = postfix + operators.top();
                operators.pop();
                
                if (operators.empty()) { // there is no '('
                    return(1);
                }
            }
            
            int j = i;
            while (infix.at(j) != '(' && j > 0) {
                if (islower(infix.at(j))) {
                    count_characters = count_characters + 1;
                }
                j--;
            }
            
            if (count_characters == 0) { // has to be a character between parentheses
                return(1);
            }
            count_characters = 0; // resets
            if (operators.empty()) {
                return(1);
            }
            
            operators.pop(); // pops the '('
            continue;
        }
        else if (infix.at(i) == '&' || infix.at(i) == '|' || infix.at(i) == '!') { // case operator
            if (operators.empty() == false) { // have to make sure operators has something to be accessed
                if (infix.at(i) == '&' && operators.top() == '(') { // problem
                    int count_characters = 0;
                    int j = i;
                    while (infix.at(j) != '(' && j > 0) {
                        if (islower(infix.at(j))) {
                            count_characters = count_characters + 1;
                        }
                        j--;
                    }
                    if (count_characters == 0) {
                        return(1);
                    }
                    count_characters = 0;
                }
                if (infix.at(i) == '|' && operators.top() == '(') {
                    int count_characters = 0;
                    int j = i;
                    while (infix.at(j) != '(' && j > 0) {
                        if (islower(infix.at(j))) {
                            count_characters = count_characters + 1;
                        }
                        j--;
                    }
                    if (count_characters == 0) {
                        return(1);
                    }
                    count_characters = 0;
                }
            }
            if (operators.size() != 0)
            
            while (operators.empty() == false && operators.top() != '(' && presedence(infix.at(i)) <= presedence(operators.top())) {
                postfix = postfix + operators.top();
                operators.pop();
            }
            operators.push(infix.at(i));
            continue;
        }
        else if (infix.at(i) == ' ') { // created so spaces aren't considered invalid
            
        }
        else {
            return(1); // invalid character in the string
        }
    }
    
    
    while (operators.empty() == false) { // last step of first alogorithm
        postfix = postfix + operators.top();;
        operators.pop();
    }


    std::stack<char> operands;
    
    for (int i = 0; i < postfix.size(); i++) {
        if (islower(postfix.at(i))) {
            if (trueValues.contains(postfix.at(i)) == true) {
                operands.push('T');
            }
            else {
                operands.push('F');
            }
            
        }
        else if (postfix.at(i) == '!') { // fix this
            char operand1 = operands.top();
            operands.pop();
            if (operand1 == 'T') {
                operands.push('F');
            }
            else {
                operands.push('T');
            }
        }
        else { // binary operator case
            char operand2 = operands.top();
            operands.pop();
            char operand1 = operands.top();
            operands.pop();
            if (postfix.at(i) == '|') {
                if (operand1 == 'T' && operand2 == 'T') {
                    operands.push('T');
                }
                else if (operand1 == 'T' || operand2 == 'T') {
                    operands.push('T');
                }
                else { // if both are false
                    operands.push('F');
                }
            }
            else if (postfix.at(i) == '&') {
                if (operand1 == 'T' && operand2 == 'T') {
                    operands.push('T');
                }
                else {
                    operands.push('F');
                }
            }
        }
    }
    
    
    int i = 0;
    
    for (i = 0; i < postfix.size(); i++) {
        char c = postfix.at(i);
        if (islower(c)) { // only want to test letters
            if (trueValues.contains(c) == true || falseValues.contains(c) == true) {
                if (trueValues.contains(c) == true && falseValues.contains(c) == true) { // if the value is in both
                    return(3);
                }
            }
            else {
                return(2); // if the value is in neither
            }
        }
    }
    
    
    if (operands.empty() == true || operands.size() > 1) { // bad syntax
        return(1);
    }
    
    if (operands.top() == 'T') {
        result = true;
    }
    else if (operands.top() == 'F'){
        result = false;
    }
    
    return(0);
}

bool isValid(const std::string& infix) {
    
    int openParens = 0;
    int closedParens = 0;
    
    for (int i = 0; i < infix.size(); i++) {
        if (infix.at(i) == '|' || infix.at(i) == '&') {
            
            if (i != infix.size()) {
                
                int j = i + 1;
                while (j <= infix.size()) {
                    if (j == infix.size()) {
                        return(false);
                    }
                    if (infix.at(j) == '|' || infix.at(j) == '&' || infix.at(j) == ')') {
                        return(false);
                    }
                    if (islower(infix.at(j))) {
                        break;
                    }
                    
                    j++;
                }
            }
            else {
                return(false);
            }
        }
        else if (infix.at(i) == '(') {
            openParens = openParens + 1;
        }
        else if (infix.at(i) == ')') {
            closedParens = closedParens + 1;
        }
    }
    
    if (openParens != closedParens) {
        return(false);
    }
    
    return(true);
}

int presedence(const char c) {
    switch(c) {
        case '!':
            return(3);
        case '&':
            return(2);
        case '|':
            return(1);
    }
    
    return(0);
}


