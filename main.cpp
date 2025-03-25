#include <iostream>
#include <chrono>
#include "elgamal.h"

using namespace std;
using namespace std::chrono;

int main() {
    cout << "Testing ElGamal Key Generation...\n";

    auto start = high_resolution_clock::now();

    key_gen();  // Calls the function which now manages local variables

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "\nKey generation completed in " << duration.count() << " milliseconds.\n";

    return 0;
}
