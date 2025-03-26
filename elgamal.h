#ifndef ELGAMAL_H
#define ELGAMAL_H

#include <iostream>
#include <vector>
#include <string>
#include "infint-master/InfInt.h"

using namespace std;

// Function prototypes

// Converts a text string to an ASCII-encoded InfInt
InfInt convertToASCII(string text);

// Converts an ASCII-encoded InfInt back to text
string asciiToText(InfInt number);

// Modular exponentiation: (base^exp) % mod
InfInt mod_exp(InfInt base, InfInt exp, InfInt mod);

// Generates a random InfInt within a specified range [a, b]
InfInt generate_in_range(InfInt min, InfInt max);

// Generates a prime number of a given bit length
InfInt generate_prime(int bit_length);

// Miller-Rabin primality test
bool Rabin_Miller(InfInt n, int iterations = 5);

// Computes power of two without bit shifting
InfInt power_of_two(int exponent);

// Generates a safe prime (p = 2q + 1) of a given bit length
InfInt generate_safe_prime(int bit_length);

// Optimized function to find a generator for a safe prime p
InfInt find_generator_safe_prime(InfInt p);

// Encrypts and decrypts a message using ElGamal encryption
void encryption_decryption(int bitsize, string message);

#endif // ELGAMAL_H
