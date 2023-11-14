#include "InfixPostfix.h"

const string OPEN = "([{"; //The set of opening parentheses
const string CLOSE = ")]}"; //The set of closing parentheses

//Function to determine whether a char is an opening parentheses
bool is_open(char ch) {
	return OPEN.find(ch) != string::npos;
}

//Function to determine whether a char is a closing parentheses
bool is_close(char ch) {
	return CLOSE.find(ch) != string::npos;
}

/*  Test input string to see that it contains balanced parentheses 
	and each type of parentheses is balanced. ex. '(' is matched with ')' */
bool is_balanced(const string& expression) {
	stack<char> s;
	bool balanced = true;
	string::const_iterator iter = expression.begin();
	while (balanced && (iter != expression.end())) {
		char next_ch = *iter;
		if (is_open(next_ch))
			s.push(next_ch);
		else if (is_close(next_ch)) {
			if (s.empty())
				balanced = false;
			else {
				char top_ch = s.top();
				s.pop();
				balanced = OPEN.find(top_ch) == CLOSE.find(next_ch);
			}
		}
		++iter;
	}
	return balanced && s.empty();
}

//Added parentheses to OPERATORS and set their precedence to -1
const string Infix_To_Postfix::OPERATORS = "+-*/%([{)]}";
const int Infix_To_Postfix::PRECEDENCE[] = {1,1,2,2,2,-1,-1,-1,-1,-1,-1};

/*	Iterate through infix expression, extracts and processes each token
	and returns the equivalent postfix string */
string Infix_To_Postfix::convert(const string& expression) {
	postfix = "";

	while (!operator_stack.empty())	//Reset stack if not empty
		operator_stack.pop();

	//Used an iterator rather than istringstream to extract char
	string::const_iterator iter = expression.begin();  
	while ((iter != expression.end())) {
		char next_token = *iter;
		if (isalnum(next_token)) {	//Add to result string if operand
			postfix += next_token;
			postfix += " ";
		}
		else if (is_operator(next_token)) {		//Process if operator/parentheses 
			process_operator(next_token);
		}
		else {	//throw error if not acceptable char is in string or continues if whitespace
			if (next_token == ' ') {
				++iter;
				continue;
			}
			else
				throw Syntax_Error("Unexpected Character Encountered");
		}
		++iter;
	}

	while (!operator_stack.empty()) {	//Pop any remaining operator and add them to postfix
		char op = operator_stack.top();
		operator_stack.pop();
		postfix += op;
		postfix += " ";
	}
	return postfix;
}

//Function to process operators
void Infix_To_Postfix::process_operator(char op) {
	//Push any operator to stack if it's empty or is an opening parentheses
	if (operator_stack.empty() || (is_open(op))) {
		if (is_close(op))
			throw Syntax_Error("Unmatched close parenthesis");
		operator_stack.push(op);
	}
	/*	If op is a closing parentheses, pop and add remaining operators in stack to postfix 
		until matching opening parentheses is encountered in stack. 
		parentheses are popped and not added to postdix */
	else if (is_close(op)) {
		while (!operator_stack.empty()
			&& (OPEN.find(operator_stack.top()) != CLOSE.find(op))) {
			postfix += operator_stack.top();
			postfix += " ";
			operator_stack.pop();
		}
		operator_stack.pop();
	}
	/*	If stack is not empty, push operator to stack if higher precedence 
		or adds and pops remaining operators to postfix until stack is empty 
		before pushing operator to stack if lower precedence */
	else {
		if (precedence(op) > precedence(operator_stack.top())) {
			operator_stack.push(op);
		}
		else {
			while (!operator_stack.empty() 
				   && (precedence(op) <= precedence(operator_stack.top()))) {
				postfix += operator_stack.top();
				postfix += " ";
				operator_stack.pop();
			}
			operator_stack.push(op);
		}
	}
}