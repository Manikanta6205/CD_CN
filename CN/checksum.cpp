#include <iostream>
using namespace std;

// Function to add two binary strings (1's complement addition)
string addBinary(string a, string b) {
    string result = "";
    int carry = 0;

    for (int i = a.size() - 1; i >= 0; i--) {
        int bit1 = a[i] - '0';
        int bit2 = b[i] - '0';

        int sum = bit1 + bit2 + carry;

        result = char((sum % 2) + '0') + result;
        carry = sum / 2;
    }

    // If there is a carry, wrap around (add it to LSB)
    if (carry == 1) {
        // add 00000001
        string one = string(a.size() - 1, '0') + "1";
        return addBinary(result, one);
    }

    return result;
}

// Function to take 1's complement (flip bits)
string onesComplement(string s) {
    for (int i = 0; i < s.size(); i++) {
        s[i] = (s[i] == '0') ? '1' : '0';
    }
    return s;
}

int main() {
    int n;
    cout << "Enter number of 8-bit blocks: ";
    cin >> n;

    string data[100];

    cout << "Enter each 8-bit binary block:\n";
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    // -------------- SENDER SIDE -----------------
    string sum = data[0];

    // Add all blocks
    for (int i = 1; i < n; i++) {
        sum = addBinary(sum, data[i]);
    }

    // Checksum = 1's complement of sum
    string checksum = onesComplement(sum);

    cout << "\n--- SENDER SIDE ---\n";
    cout << "Final Sum:   " << sum << endl;
    cout << "Checksum:    " << checksum << endl;

    // -------------- RECEIVER SIDE -----------------
    cout << "\nEnter received blocks (including checksum):\n";
    string recv[100];
    for (int i = 0; i < n + 1; i++) {
        cin >> recv[i];
    }

    string rsum = recv[0];

    for (int i = 1; i < n + 1; i++) {
        rsum = addBinary(rsum, recv[i]);
    }

    // Final complement
    string finalCheck = onesComplement(rsum);

    cout << "\n--- RECEIVER SIDE ---\n";
    if (finalCheck == string(finalCheck.size(), '0'))
        cout << "Status: No Error (Data is correct)\n";
    else
        cout << "Status: ERROR detected (Data corrupted)\n";

    return 0;
}
