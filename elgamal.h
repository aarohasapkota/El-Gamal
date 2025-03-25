#ifndef ELGAMAL_H
#define ELGAMAL_H

#include <string>
#include <vector>
#include "infint-master/InfInt.h" // Assuming InfInt is a custom class or library you're using

using namespace std;

// Function declarations

InfInt convertToASCII(string text);
//Function for converting ascii to text
string asciiToText(InfInt number);

InfInt mod_exp(InfInt base, InfInt exp, InfInt mod);

InfInt random_generator(InfInt a,InfInt b);


InfInt generate_in_range( InfInt min,  InfInt max);
InfInt generate_prime(int bit_length);
bool Rabin_Miller( InfInt n, int iterations = 10);

std::vector<InfInt> get_prime_factors( InfInt n);
InfInt find_generator( InfInt p);

void encryption_decryption(int bitsize,  string message);

#endif // ELGAMAL_H