#include "Queue.h"
#include "InfixPostfix.h"

int main() {
	Infix_To_Postfix in2post;

	cout << "Infix to Postfix Conversion\n\n";
	cout << "Enter expressions to be converted, or press Return when done\n";
	string expression;
	while (getline(cin, expression) && (expression != "")) {
		if (is_balanced(expression)) {
			try {
				string result = in2post.convert(expression);
				cout << "\n== " << result << endl;
			}
			catch (Syntax_Error& ex) {
				cout << "\nSyntax Error: " << ex.what() << endl;
			}
		}
		else
			cout << "Invalid: " << expression << " is not balanced.\n";

		cout << "\nEnter another expression: ";
	}

	/*	Only created example queues for int and double 
		but can be used with string and char if those Queues were created */
	Queue<int> intQ;
	Queue<double> doubleQ;

	cout << "\nInteger Queue:\n";
	intQ.enQueue(1);
	intQ.enQueue(2);
	intQ.enQueue(3);
	intQ.printQueue();

	cout << "\nTotal: " << intQ.queueTotal() << endl;
	int frontInt = intQ.queueFront();
	cout << "Front of Queue: " << frontInt << endl;
	
	int deletedInt = intQ.deQueue();
	cout << "\nRemoved: " << deletedInt << endl;
	intQ.printQueue();
	cout << "\nNew Total: " << intQ.queueTotal() << endl;

	cout << "\nDouble Queue:\n";
	doubleQ.enQueue(1.5);
	doubleQ.enQueue(3.3);
	doubleQ.enQueue(7.9);
	doubleQ.printQueue();

	cout << "\nTotal: " << doubleQ.queueTotal() << endl << endl;
	doubleQ.enQueue(4.1);
	doubleQ.printQueue();
	cout << "\nNew Total: " << doubleQ.queueTotal() << endl;
}