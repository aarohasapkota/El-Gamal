#ifndef ELGAMAL_H
#define ELGAMAL_H

#include <iostream>
#include <vector>
#include <ctime>
#include "infint-master/InfInt.h"

using namespace std;

// Function declarations
InfInt mod_exp(InfInt base, InfInt exp, InfInt mod);
InfInt generate_in_range(InfInt min, InfInt max);
bool Rabin_Miller(InfInt n, int iterations = 5);
InfInt generate_prime(int bit_length);
InfInt find_generator(InfInt p);
void key_gen();

#endif // ELGAMAL_H
