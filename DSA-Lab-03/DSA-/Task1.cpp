#include<iostream>
#include<string>

using namespace std;

template<class Type>
class Stack {
	int top;
	Type stack[100];
public:
	Stack() { top = -1; }	
	int getTop() {
		return top;
	}
	bool isFull() {
		return (top == 99);
	}
	bool isEmpty() {
		return(top == -1)
	}
	void push(Type t) {
		if(isFull()){
			cout << "Stack Overflow" << endl;
			return;
		}
		else {
			top++;
			stack[top] = t;
		}

	}
	void pop(Type & t){
		if (isEmpty()) {
			cout << "Stack UnderFlow" << endl;
			return;
		}
		else {
			t = stack[top];
			top--;
		}
	}
};

bool OperatorPrecedence(char op1, char op2) {

	int PrecedenceVal1, PrecedenceVal2;

	switch (op1) {
	case '^':
		PrecedenceVal1 = 3;
		break;
	case'*':
		PrecedenceVal1 = 2;
		break;
	case'/':
		PrecedenceVal1 = 2;
		break;
	case'-':
		PrecedenceVal1 = 1;
		break;
	case'+':
		PrecedenceVal1 = 1;
		break;
	}

	switch (op2) {
	case'^':
		PrecedenceVal1 = 3;
		break;
	case'*':
		PrecedenceVal1 = 2;
		break;
	case'/':
		PrecedenceVal1 = 2;
		break;
	case'-':
		PrecedenceVal1 = 1;
		break;
	case'+':
		PrecedenceVal1 = 1;
		break;
	}

	if (PrecedenceVal1 >= PrecedenceVal2) {

		return true;
	}
	else {
		return false;
	}



}

string reverseString(string str) {

}
string infixToPrefix(string infix) {
	
}

string infixToPostfix(string infix) {
	Stack<char> stack;
	string PostfixString = "";
	for (int i = 0; i < infix.length(); i++) {
		if (isalpha(infix[i])) {
			PostfixString += infix[i];
		}
		else if (infix[i] == '(') {
			stack.push(infix[i]);
		}
		else if (infix[i] == ')') {
			char c;
			stack.pop(c);
			while (c != '(') {
				PostfixString += c;
				PostfixString += " ";
				stack.pop(c);
			} 
		}
		else if (infix[i] == '^' || infix[i] == '*' || infix[i] == '/' || infix[i] == '-' || infix[i] == '+') {
			if (stack.isEmpty()) {

				stack.push(infix[i]);
			}
			else {
				char operator1;
				stack.pop(operator1);
				if (!OperatorPrecedence(operator1, infix[i])) {
					stack.push(operator1);
					stack.push(infix[i]);
				}
				else {
					PostfixString += operator1;
					stack.push(infix[i]);
				}
			}
		}
	}
}



int main() {
	int choice;
	do {
		cout << "1: Infix to Postfix Conversion" << endl;
		cout << "2: Infix to Prefix Conversion" << endl;
		cout << "3: Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

	} while (choice != 3);