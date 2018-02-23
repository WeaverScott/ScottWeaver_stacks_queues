#include "functions.h"
#include <iostream>
#include <stack>
#include <string>

/**********************************************************************
Homework for 263.
Contains 2 main methods:  balancedSymbols() and iToP().
2 helper method: priority() and comparePriority().

@author Scott Weaver
@version Winter 2018
**********************************************************************/
int priority(char symbol);

bool comparePriority(char top, char compare);

/**********************************************************************
Takes as input a string of arbitrary length. It checks the entire 
file to determine if there is a closing parenthesis, square bracket, 
and curly brace for everycorresponding opening symbol.

@param input
	The inputted string to balance.
@return bool
	True if it is balanced, false if it is not.
**********************************************************************/
bool balancedSymbols(std::string expr) {
	
	//Initializes the stack
	std::stack<char, std::deque<char> > s;
	
	//Iterates through the inputted expression using an iterator 
	for(auto it = expr.begin(); it != expr.end(); it++) {
		
		//Pushes open char onto stack.
		if (*it == '(' || *it == '[' || *it == '{') {
			s.push(*it);
		}
		//Compares close char to the last item on the stack.
		else if (*it == ')' || *it == ']' || *it == '}') {
			
			//switches the iterator through the cases.
			switch (*it) {
			
			//Pops if first item on the stack is '('
			//And last item is ')'.
			case ')':
				if(s.top() != '(')
					return false;
				s.pop();
				break;

			//Pops if first item on the stack is '['
			//And last item is ']'.
			case ']':
				if(s.top() != '[')
					return false;
				s.pop();
				break;

			//Pops if first item on the stack is '{'
			//And last item is '}'.
			case '}':
				if(s.top() != '{')
					return false;
				s.pop();
				break;
			}
		}
	}

	if (s.size() != 0) {
		return false;
	}
	
	return true;
}	
/**********************************************************************
Takes as input a valid infix expression and returns the
corresponding postfix expression.

@param input
	The inFix expression we wish to convert  to postFix.
@return string
	The postFix expression that we converted from inFix
**********************************************************************/
std::string iToP(std::string input) {
	
	std::stack<char, std::deque<char> > pFix;

	std::string output;

	for(int i = 0; i < input.length(); i++) {
		if(input[i] == ' ')
			continue;

		if(input[i] == '*' || input[i] == '/' 
		|| input[i] == '+' || input[i] == '-') {
			
			while(!pFix.empty() && pFix.top() != '(' && comparePriority(pFix.top(), input[i])) {
				output += pFix.top();
				pFix.pop();
			}
			pFix.push(input[i]);
		}

		else if (input[i] == '(') {
			pFix.push(input[i]);
		}

		else if (input[i] == ')') {
			while(!pFix.empty() && pFix.top() != '(') {
				output += pFix.top();
				pFix.pop();
			}

			pFix.pop();
		}

		else {
			output += input[i];
		}
	}

	while (!pFix.empty()) {
		output += pFix.top();
		pFix.pop();
	}

	return output;	
}
	
/**********************************************************************
Helper method that returns the priority of the given operands.

@param symbol
	The operator that we are determing priority on.
@return 
	The priority of the operand.
**********************************************************************/
int priority(char symbol) {
		
	//Exponents have the highest priority.
	if(symbol == '^'){
		return 3;
	}

	//Division and multiplication have second highest priority.
	else if(symbol == '/' || symbol == '*') {
		return 2;
	}

	//Addition and subtraction have the lowest priority.
	else if(symbol == '+' || symbol == '-') {
		return 1;
	}

	//Return 0 for either '(' or ')'.
	return 0;	
}

/**********************************************************************
Helper function to determine the order of operands.

@param top
	Top element in the stack.
@param compare
	Element that we are comparing
@return boolean
	If top has higher priority or not.
**********************************************************************/
bool comparePriority(char top, char compare) {
	
	/** Holds the weight of the top item in the stack */
	int topWeight = priority(top);

	/** Holds the weight of what is being compared */
	int compareWeight = priority(compare);

	//Compares priority of the operands
	if(topWeight == compareWeight) {
		return true;
	}
	else if (topWeight > compareWeight) {
		return true;
	}
	else {
		return false;
	}
}


int main() {

	std::string expression;
	std::cout<<"Enter Infix Expression \n";
	getline(std::cin, expression);
	std::string pFix = iToP(expression);
	std::cout<<"Output = "<<pFix<<"\n";
} 
