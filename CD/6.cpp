#include <bits/stdc++.h>
using namespace std;

/* ---------------------------------------------------
   STEP 1: TOKENIZATION
   ---------------------------------------------------
   This function splits the input expression (string)
   into separate tokens such as:
   - operands (a, b, c, x1, etc.)
   - operators (+, -, *, /)
   - parentheses ((, ))
--------------------------------------------------- */
vector<string> tokenize(string s) {
    vector<string> tokens;
    string temp = "";

    for (int i = 0; i < s.size(); i++) {
        // If character is alphanumeric or underscore, add to temp
        if (isalnum(s[i]) || s[i] == '_') {
            temp += s[i];
        } else {
            // If temp is non-empty, push it as a token
            if (!temp.empty()) {
                tokens.push_back(temp);
                temp = "";
            }

            // Skip spaces
            if (s[i] == ' ') continue;

            // Push operators or parentheses as individual tokens
            tokens.push_back(string(1, s[i]));
        }
    }

    // Push the last token if any
    if (!temp.empty()) tokens.push_back(temp);
    return tokens;
}

/* ---------------------------------------------------
   STEP 2: OPERATOR PRECEDENCE
   ---------------------------------------------------
   Defines the precedence of operators.
   Higher number = higher precedence.
--------------------------------------------------- */
int prec(string op) {
    if (op == "+" || op == "-") return 1;
    else if (op == "*" || op == "/") return 2;
    return 0;
}

/* ---------------------------------------------------
   STEP 3: INFIX TO POSTFIX CONVERSION
   ---------------------------------------------------
   Converts infix expressions (like a + b * c)
   to postfix (Reverse Polish Notation): a b c * +
   Using the Shunting-Yard algorithm.
--------------------------------------------------- */
vector<string> infix2postfix(vector<string> tokens) {
    vector<string> output;
    stack<string> s;

    for (auto x : tokens) {
        // If token is operand, directly send to output
        if (isalnum(x[0]) || x[0] == '_') {
            output.push_back(x);
        } else if (x == "(") {
            s.push(x);
        } else if (x == ")") {
            while (!s.empty() && s.top() != "(") {
                output.push_back(s.top());
                s.pop();
            }
            s.pop(); // Remove '('
        } else {
            // Operator: pop higher or equal precedence ops
            while (!s.empty() && s.top() != "(" && prec(s.top()) >= prec(x)) {
                output.push_back(s.top());
                s.pop();
            }
            s.push(x);
        }
    }

    // Pop remaining operators
    while (!s.empty()) {
        output.push_back(s.top());
        s.pop();
    }

    return output;
}

/* ---------------------------------------------------
   STEP 4: GENERATE THREE ADDRESS CODE (TAC)
--------------------------------------------------- */
void gen_TAC(vector<string> postfix) {
    vector<tuple<string, string, string, string>> quadruples; // (op, arg1, arg2, result)
    vector<tuple<string, string, string>> triples;            // (op, arg1, arg2)
    stack<string> st;                                         // operand stack
    int temp_count = 1;                                       // for temporary variables

    for (auto x : postfix) {
        if (isalnum(x[0]) || x[0] == '_') {
            // Operand → push to stack
            st.push(x);
        } else {
            // Operator → pop 2 operands
            string b = st.top(); st.pop();
            string a = st.top(); st.pop();

            // Create a temporary variable (t1, t2, ...)
            string tmp = "t" + to_string(temp_count++);

            // Store in quadruple format
            quadruples.push_back({x, a, b, tmp});

            // Convert temp reference for triples
            auto conv = [&](string s) {
                return (s[0] == 't') ? "(" + to_string(stoi(s.substr(1)) - 1) + ")" : s;
            };

            // Store in triple format
            triples.push_back({x, conv(a), conv(b)});

            // Push result (temporary) back to stack
            st.push(tmp);
        }
    }

    // Print Quadruples
    cout << "\nQuadruples:\nIdx\tOp\tArg1\tArg2\tResult\n";
    for (int i = 0; i < quadruples.size(); i++) {
        auto [op, a, b, r] = quadruples[i];
        cout << i << "\t" << op << "\t" << a << "\t" << b << "\t" << r << "\n";
    }

    // Print Triples
    cout << "\nTriples:\nIdx\tOp\tArg1\tArg2\n";
    for (int i = 0; i < triples.size(); i++) {
        auto [op, a, b] = triples[i];
        cout << i << "\t" << op << "\t" << a << "\t" << b << "\n";
    }

    // Print Indirect Triples
    cout << "\nIndirect Triples:\nIdx\tPointer\n";
    for (int i = 0; i < triples.size(); i++) {
        cout << i << "\t(" << i << ")\n";
    }
}

/* ---------------------------------------------------
   STEP 5: MAIN FUNCTION
--------------------------------------------------- */
int main() {
    string expr;
    cout << "Enter expression: ";
    getline(cin, expr);

    // Step 1: Tokenize input
    auto tokens = tokenize(expr);

    // Step 2: Convert infix to postfix
    auto postfix = infix2postfix(tokens);

    // Step 3: Generate TAC
    gen_TAC(postfix);

    return 0;
}
