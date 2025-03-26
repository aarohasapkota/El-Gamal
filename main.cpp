/* 
   Team Members: Aaroha Sapkota and Jonathan Mazurkiewicz
   Assignment: Project 3 - El Gamal Encryption
   Professor: Dr. Nojoumian
   Due Date: 3/25/2025
*/

#include <iostream>
#include <chrono>
#include "elgamal.h"
#include <string>

using namespace std;
using namespace std::chrono;

int main() {
    int bit_length;
    cout << "Enter key size (in bits, e.g., 32, 64, 128): ";
    cin >> bit_length;

    cin.ignore(); // To ignore the newline character left in the buffer

    string message;
    cout << "Enter your string: (max length determined by key size) ";
    cout << "For 32 bit - max 3 chars, 64 bit - max 7 chars, 128 bit - max 15 chars" << endl;
    getline(cin, message);

    auto start = high_resolution_clock::now();
    encryption_decryption(bit_length, message);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Encryption and decryption took " << duration.count() << " milliseconds." << endl;

    return 0;
}