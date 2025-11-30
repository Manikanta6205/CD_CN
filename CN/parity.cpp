#include <iostream>
using namespace std;

// Function to count number of 1s
int countOnes(string s) {
    int count = 0;
    for(char c : s) {
        if(c == '1') count++;
    }
    return count;
}

int main() {
    string data;
    int choice;

    // -------------- SENDER SIDE -----------------
    cout << "Enter binary string: ";
    cin >> data;

    cout << "Choose Parity Type:\n";
    cout << "1. Even Parity\n";
    cout << "2. Odd Parity\n";
    cin >> choice;

    int ones = countOnes(data);
    char parityBit;

    // EVEN PARITY: total 1s must be even
    if (choice == 1) {
        if (ones % 2 == 0)
            parityBit = '0';    // already even
        else
            parityBit = '1';    // make it even
    }

    // ODD PARITY: total 1s must be odd
    else if (choice == 2) {
        if (ones % 2 == 0)
            parityBit = '1';    // make it odd
        else
            parityBit = '0';    // already odd
    }

    // Append the parity bit
    string transmitted = data + parityBit;

    cout << "\n--- SENDER SIDE ---\n";
    cout << "Original Data:   " << data << endl;
    cout << "Parity Bit:      " << parityBit << endl;
    cout << "Transmitted Data: " << transmitted << endl;

    // ---------------- RECEIVER SIDE ----------------
    string received;
    cout << "\nEnter received binary string: ";
    cin >> received;

    int receivedOnes = countOnes(received);

    bool isCorrect;

    if (choice == 1) {  // Even parity check
        isCorrect = (receivedOnes % 2 == 0);
    } else {            // Odd parity check
        isCorrect = (receivedOnes % 2 == 1);
    }

    cout << "\n--- RECEIVER SIDE ---\n";
    if (isCorrect)
        cout << "Status: No Error (Data is correct)\n";
    else
        cout << "Status: ERROR detected (Data corrupted)\n";

    return 0;
}
