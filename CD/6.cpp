#include <iostream>
#include <cstring>
using namespace std;

char stackOp[50];
int top = -1;

void push(char c) { stackOp[++top] = c; }
char pop() { return stackOp[top--]; }
char peek() { return stackOp[top]; }
int isEmpty() { return top == -1; }

int prec(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
	int k = 0;
	for (int i = 0; infix[i] != '\0'; i++) {
		char c = infix[i];
		if (isalnum(c)) postfix[k++] = c;
		else if (c == '(') push(c);
		else if (c == ')') {
			while (!isEmpty() && peek() != '(')
				postfix[k++] = pop();
			pop(); 
		} else {
			while (!isEmpty() && prec(peek()) >= prec(c))
				postfix[k++] = pop();
			push(c);
		}
	}
	while (!isEmpty()) postfix[k++] = pop();
	postfix[k] = '\0';
}

void generateTAC(char postfix[]) {
	char st[50][10];
	int top2 = -1, t = 1;
	for (int i = 0; postfix[i] != '\0'; i++) {
		char c = postfix[i];
		if (isalnum(c)) {
			char temp[2] = {c, '\0'};
			strcpy(st[++top2], temp);
		} else {
			char op2[10], op1[10], res[10];
			strcpy(op2, st[top2--]);
			strcpy(op1, st[top2--]);
			sprintf(res, "t%d", t++);
			cout << res << " = " << op1 << " " << c << " " << op2 << endl;
			strcpy(st[++top2], res);
		}
	}
}

int main() {
	char infix[50], postfix[50];
	cout << "Enter expression: ";
	cin.getline(infix, 50);

	infixToPostfix(infix, postfix);
	cout << "\nPostfix: " << postfix << endl;

	cout << "\nThree Address Code:\n";
	generateTAC(postfix);

	return 0;
}
