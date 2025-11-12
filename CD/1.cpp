#include<bits/stdc++.h>
using namespace std;

// Regular expressions for various components
const regex KEYWORD_PATTERN(
    R"(\b(?:auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while|main|namespace|public|private|protected|class|friend|virtual|template|this|new|delete|try|catch|throw|inline|using|export|mutable)\b)"
);
const regex OPERATOR_PATTERN(R"([+\-*/%=<>!&|^~]|<<|>>|::)");
const regex SPECIAL_SYMBOL_PATTERN(R"([{}();,.\[\]])");

// Regular expression to identify data types followed by an identifier
const regex DATA_TYPE_PATTERN(
    R"(\b(?:int|float|double|char|long|short|void|bool|unsigned)\s+([A-Za-z_][A-Za-z0-9_]*)\b)"
);

void remove_comments(string &content) {
    size_t pos;
    // Remove single-line comments (//)
    while ((pos = content.find("//")) != string::npos) {
        size_t end_pos = content.find("\n", pos);
        if (end_pos == string::npos)
            end_pos = content.size();
        content.erase(pos, end_pos - pos);
    }

    // Remove multi-line comments (/* ... */)
    while ((pos = content.find("/*")) != string::npos) {
        size_t end_pos = content.find("*/", pos);
        if (end_pos == string::npos) break;
        content.erase(pos, end_pos - pos + 2);
    }
}

void analyze_cpp_program(const string& file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error: Could not open file: " << file_path << endl;
        return;
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Remove comments
    remove_comments(content);

    // Find keywords
    set<string> keywords;
    auto words_begin = sregex_iterator(content.begin(), content.end(), KEYWORD_PATTERN);
    auto words_end = sregex_iterator();
    for (sregex_iterator i = words_begin; i != words_end; ++i)
        keywords.insert(i->str());

    // Find identifiers only if preceded by a valid data type
    set<string> identifiers;
    words_begin = sregex_iterator(content.begin(), content.end(), DATA_TYPE_PATTERN);
    for (sregex_iterator i = words_begin; i != words_end; ++i)
        identifiers.insert(i->str(1)); // Group 1 contains the identifier

    // Remove keywords from identifiers
    for (const auto& keyword : keywords)
        identifiers.erase(keyword);

    // Find operators
    vector<string> operators;
    words_begin = sregex_iterator(content.begin(), content.end(), OPERATOR_PATTERN);
    for (sregex_iterator i = words_begin; i != words_end; ++i)
        operators.push_back(i->str());

    // Find special symbols
    vector<string> special_symbols;
    words_begin = sregex_iterator(content.begin(), content.end(), SPECIAL_SYMBOL_PATTERN);
    for (sregex_iterator i = words_begin; i != words_end; ++i)
        special_symbols.push_back(i->str());

    // Output the results
    cout << "=== C/C++ Program Lexical Analysis ===\n\n";

    cout << "Keywords found (" << keywords.size() << "):\n";
    for (const auto& k : keywords) cout << k << " ";
    cout << "\n\n";

    cout << "Identifiers found (" << identifiers.size() << "):\n";
    for (const auto& id : identifiers) cout << id << " ";
    cout << "\n\n";

    cout << "Operators found (" << operators.size() << "):\n";
    for (const auto& op : operators) cout << op << " ";
    cout << "\n\n";

    cout << "Special symbols found (" << special_symbols.size() << "):\n";
    for (const auto& sym : special_symbols) cout << sym << " ";
    cout << "\n";
}

int main() {
    string file_path = "sample.c"; // Replace with your target file name
    analyze_cpp_program(file_path);
    return 0;
}
