#include<iostream>
#include<string>
#include<cmath>
#include<algorithm> 

using namespace std;

template<class Type>
class Stack {
    int top;
    Type stack[100];
public:
    Stack() { top = -1; }
    bool isFull() { return (top == 99); }
    bool isEmpty() { return (top == -1); }
    void push(Type t) {
        if (!isFull()) {
            stack[++top] = t;
        }
        else {
            cout << "Stack Overflow" << endl;
        }
    }
    void pop(Type& t) {
        if (!isEmpty()) {
            t = stack[top--];
        }
        else {
            cout << "Stack Underflow" << endl;
        }
    }
};


double Multiply(int a, int b) {

    double Product = 0;
    if (b == 1) {
        return a;
    }
    else {
        return Product = a + Multiply(a, b - 1);
    }


}

double Power(double a, double b) {
    double result = 0;

    if (b == 0) {
        return 1;
    }
    else {
        return result = a * Power(a, b - 1);
    }
}

bool OperatorPrecedence(char op1, char op2) {
    int PrecedenceVal1 = 0, PrecedenceVal2 = 0;

    switch (op1) {
    case '^': PrecedenceVal1 = 3; break;
    case '*': PrecedenceVal1 = 2; break;
    case '/': PrecedenceVal1 = 2; break;
    case '-': PrecedenceVal1 = 1; break;
    case '+': PrecedenceVal1 = 1; break;
    }

    switch (op2) {
    case '^': PrecedenceVal2 = 3; break;
    case '*': PrecedenceVal2 = 2; break;
    case '/': PrecedenceVal2 = 2; break;
    case '-': PrecedenceVal2 = 1; break;
    case '+': PrecedenceVal2 = 1; break;
    }

    return (PrecedenceVal1 >= PrecedenceVal2);
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
                stack.pop(c);
            }
        }
        else if (infix[i] == '^' || infix[i] == '*' || infix[i] == '/' || infix[i] == '-' || infix[i] == '+') {
            while (!stack.isEmpty()) {
                char operator1;
                stack.pop(operator1);
                if (!OperatorPrecedence(operator1, infix[i])) {
                    stack.push(operator1);
                    break;
                }
                PostfixString += operator1;
            }
            stack.push(infix[i]);
        }
    }

    while (!stack.isEmpty()) {
        char operator1;
        stack.pop(operator1);
        PostfixString += operator1;
    }

    return PostfixString;
}


string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());


    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }


    string postfix = infixToPostfix(infix);


    reverse(postfix.begin(), postfix.end());

    return postfix;
}


int evaluatePostfix(string postfix, char operands[], int values[], int operandCount) {
    Stack<int> stack;

    for (int i = 0; i < postfix.length(); i++) {
        char current = postfix[i];


        if (isalpha(current)) {

            for (int j = 0; j < operandCount; j++) {
                if (operands[j] == current) {
                    stack.push(values[j]);
                    break;
                }
            }
        }
        else if (isdigit(current)) {
            stack.push(current - '0');
        }
        else if (current == '^' || current == '*' || current == '/' || current == '-' || current == '+') {
            int operand2, operand1;
            stack.pop(operand2);
            stack.pop(operand1);

            switch (current) {
            case '^':
                stack.push(pow(operand1, operand2));
                break;
            case '*':
                stack.push(operand1 * operand2);
                break;
            case '/':
                stack.push(operand1 / operand2);
                break;
            case '-':
                stack.push(operand1 - operand2);
                break;
            case '+':
                stack.push(operand1 + operand2);
                break;
            }
        }
    }


    int result;
    stack.pop(result);
    return result;
}

int main() {
    int choice;
    do {
        cout << "1: Infix to Postfix Conversion" << endl;
        cout << "2: Infix to Prefix Conversion" << endl;
        cout << "3: Multiply 2 numbers" << endl;
        cout << "4: Power of 2 numbers" << endl;
        cout << "5: Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        string infix, postfix, prefix;


        char operands[20];
        int values[20];
        int operandCount = 0;
        int result = 0;
        double answer = 0.0;
        double num = 0.0, exp;

        switch (choice) {
        case 1:
            cout << "Enter infix Expression:  ";
            cin.ignore();
            getline(cin, infix);


            postfix = infixToPostfix(infix);
            cout << "Postfix Expression = " << postfix << endl;



            for (int i = 0; i < postfix.length(); i++) {
                if (isalpha(postfix[i])) {
                    bool found = false;
                    for (int j = 0; j < operandCount; j++) {
                        if (operands[j] == postfix[i]) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        operands[operandCount] = postfix[i];
                        operandCount++;
                    }
                }
            }

            for (int i = 0; i < operandCount; i++) {
                cout << "Enter value for " << operands[i] << ": ";
                cin >> values[i];
            }

            result = evaluatePostfix(postfix, operands, values, operandCount);
            cout << "Result = " << result << endl << endl;
            break;

        case 2:
            cout << "Enter infix Expression:  ";
            cin.ignore();
            getline(cin, infix);


            prefix = infixToPrefix(infix);
            cout << "Prefix Expression = " << prefix << endl << endl;
            break;
        case 3:
            
            cout << "\nEnter the Number: ";
            cin >> num;
            cin.ignore();
            cout << "\nEnter the Number: ";
            cin >> exp;
            cin.ignore();
            answer = Multiply(num, exp);
            cout << "\nResult is: " << answer << endl << endl;
            break;
        case 4:
            
            cout << "\nEnter the Number: ";
            cin >> num;
            cin.ignore();
            cout << "\nEnter the Exponential: ";
            cin >> exp;
            cin.ignore();
            answer = Power(num, exp);
            cout << "\nResult is: " << answer << endl << endl;
            break;
        case 5:
            cout << "Exiting..." << endl << endl;
            exit(1);
        default:
            cout << "INVALID INPUT." << endl << endl;
            exit(1);
        }
    } while (choice != 5);

    return 0;
}
