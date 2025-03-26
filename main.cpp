#include <iostream>
#include <chrono>
#include "elgamal.h"

using namespace std;
using namespace std::chrono;

int main() {
    int bit_length;
    cout << "Enter key size (in bits, e.g., 32, 64, 128, 256): ";
    cin >> bit_length;

    cin.ignore(); // To ignore the newline character left in the buffer

    string message;
    cout << "Enter your string: ";
    getline(cin, message); // Use getline to capture the entire string including spaces

    auto start = high_resolution_clock::now();
    encryption_decryption(bit_length, message);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Encryption and decryption took " << duration.count() << " milliseconds." << endl;

    return 0;
}