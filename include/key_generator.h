#ifndef KEY_GENERATOR_H
#define KEY_GENERATOR_H

#include <random>
#include <vector>

// Modular exponentiation using repeated squaring
long long mod_exp(long long base, long long exp, long long mod);

// Function to generate a random number within a given range
long long generate_in_range(long long min, long long max);

// Rabin-Miller primality test
bool Rabin_Miller(long long n, int bit_length);

// Function to generate a prime number for key generation
long long generate_prime(int bit_length);

// Function to find a generator (primitive root) for a given prime
long long find_generator(long long p);

// Function to generate ElGamal key pair (public & private keys)
void key_gen(long long &p, long long &g, long long &h, long long &x);

#endif // KEY_GENERATOR_H
