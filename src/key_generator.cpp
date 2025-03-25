
#include <random>
#include <iostream>
#include "../include/key_generator.h"
using namespace std;

// Modular exponentiation using repeated squaring
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

long long generate_in_range(long long min, long long max) {
    static random_device rd;   // Use static to avoid reseeding
    static mt19937 gen(rd());  // Mersenne Twister PRNG
    uniform_int_distribution<long long> dist(min, max);
    return dist(gen);
}


long long generate_prime(int bit_length) {
    long long lower_bound = pow(2, bit_length - 1);  // Smallest bit_length-bit number
    long long upper_bound = pow(2, bit_length) - 1;  // Largest bit_length-bit number

    long long candidate;
    do {
        candidate = generate_in_range(lower_bound, upper_bound); // Random number in range
        candidate |= 1;  // Ensure it's odd
    } while (!Rabin_Miller(candidate, bit_length));

    return candidate;
}

// Rabin-Miller primality test
bool Rabin_Miller(long long n, int bit_length) {
    int i = (bit_length / 16) + 1;
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    long long m = n - 1;
    int k = 0;

    // Express n-1 as 2^k * d
    while (m % 2 == 0) {
        m /= 2;
        k++;
    }

    // Perform multiple trials for probabilistic accuracy
    for (int j = 0; j < i; j++) {
        long long a = generate_in_range(2, n - 2);
        long long x = mod_exp(a, m, n);

        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (int i = 0; i < k - 1; i++) {
            x = mod_exp(x, 2, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }

        if (composite) return false;
    }

    return true;
}

// Function to compute prime factors of (p - 1)
vector<long long> get_prime_factors(long long n) {
    vector<long long> factors;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        factors.push_back(n);
    return factors;
}

// Optimized function to find a generator for Z_p*
long long find_generator(long long p) {
    long long phi = p - 1;
    vector<long long> factors = get_prime_factors(phi);

    int max_attempts = max(10, (int)log2(p));  // 👈 Dynamic attempts

    for (int attempt = 0; attempt < max_attempts; attempt++) {
        long long g = generate_in_range(2, p - 1); // Pick a random candidate

        bool is_generator = true;
        for (long long factor : factors) {
            if (mod_exp(g, phi / factor, p) == 1) {
                is_generator = false;
                break;
            }
        }
        if (is_generator)
            return g;  // Found a valid generator
    }

    return -1; // Should never happen unless p is incorrect
}

// Function to generate the ElGamal key pair
void key_gen(long long &p, long long &g, long long &h, long long &x) {
    int bit_length = 64;   // Define key size (can be changed as needed)
    p = generate_prime(bit_length);  // Generate a 64-bit prime
    g = find_generator(p);           // Find a generator for Z_p*
    x = generate_in_range(1, p - 2); // Use existing function to generate private key x
    h = mod_exp(g, x, p);            // Compute public key h = g^x mod p

    cout << "ElGamal Key Generation Complete!" << endl;
    cout << "Public Key: (p=" << p << ", g=" << g << ", h=" << h << ")" << endl;
    cout << "Private Key: x=" << x << endl;
}



