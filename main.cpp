#include <iostream>
#include "include/key_generator.h"


using namespace std;

int main() {
    int bit_length;
    cout << "Enter key size (in bits, e.g., 16, 32, 64, 128): ";
    cin >> bit_length;

    long long prime_candidate = generate_prime(bit_length);
    cout << "Generated Prime: " << prime_candidate << endl;

    long long generator = find_generator(prime_candidate);
    cout << "Generator for Z_" << prime_candidate << "*: " << generator << endl;

    return 0;
}a
