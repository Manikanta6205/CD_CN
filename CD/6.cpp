#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

int prec(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

void infixToPostfix(const string& infix, string& postfix) {
	stack<char> st;
	for (char c : infix) {
		if (isalnum(c)) postfix += c;
		else if (c == '(') st.push(c);
		else if (c == ')') {
			while (!st.empty() && st.top() != '(') {
				postfix += st.top();
				st.pop();
			}
			if (!st.empty()) st.pop();
		} else {
			while (!st.empty() && prec(st.top()) >= prec(c)) {
				postfix += st.top();
				st.pop();
			}
			st.push(c);
		}
	}
	while (!st.empty()) {
		postfix += st.top();
		st.pop();
	}
}

void generateTAC(const string& postfix) {
	stack<string> st;
	int t = 1;
	for (char c : postfix) {
		if (isalnum(c)) {
			st.push(string(1, c));
		} else {
			string op2 = st.top(); st.pop();
			string op1 = st.top(); st.pop();
			string res = "t" + to_string(t++);
			cout << res << " = " << op1 << " " << c << " " << op2 << endl;
			st.push(res);
		}
	}
}

int main() {
	string infix, postfix;
	cout << "Enter expression: ";
	getline(cin, infix);

	infixToPostfix(infix, postfix);
	cout << "\nPostfix: " << postfix << endl;

	cout << "\nThree Address Code:\n";
	generateTAC(postfix);
}
