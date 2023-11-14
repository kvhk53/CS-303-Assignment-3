#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <stack>
#include <stdexcept>

using namespace std;

//Based off lecture notes
bool is_open(char ch);
bool is_close(char ch);
bool is_balanced(const string& expression);

//Used to test acceptable characters and throw error if not
class Syntax_Error : public exception {
private:
	string message;

public:
	Syntax_Error(const char* text) : message(text) {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

//Based off lecture notes. Changes were made to incorporate parentheses.
class Infix_To_Postfix {
private:
	void process_operator(char op);
	bool is_operator(char ch) const { return OPERATORS.find(ch) != string::npos; }
	int precedence(char op) const { return PRECEDENCE[OPERATORS.find(op)]; }
	static const string OPERATORS;
	static const int PRECEDENCE[];
	stack<char> operator_stack;
	string postfix;

public:
	string convert(const string& expression);
};