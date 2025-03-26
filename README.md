# El-Gamal
 - ElGamal Pub-Key Encryption Written in C++ by Aaroha Sapkota and Jonathan Mazurkiewicz
 - Class: CIS 4634 003 Appl Cryptography and Security Spring 2025
 - Instructor: Dr. Mehrdad Nojoumian
 - Takes advantage of safe primes to ease complexity. For 128-bit key size, average computation time ranges from 5-60 seconds 

## Key Generation
![image](https://github.com/user-attachments/assets/5b0b3f40-b632-4174-b857-1cd8634f7d1a)

## Encryption and Decryption
![image](https://github.com/user-attachments/assets/ead2b56e-7e4b-4847-a5f4-caf883f20f08)

### Functions:

- `InfInt convertToASCII(string text);`  
  Converts a text string to an ASCII-encoded `InfInt`.

- `string asciiToText(InfInt number);`  
  Converts an ASCII-encoded `InfInt` back to text.

- `InfInt mod_exp(InfInt base, InfInt exp, InfInt mod);`  
  Performs modular exponentiation `(base^exp) % mod`.

- `InfInt generate_in_range(InfInt min, InfInt max);`  
  Generates a random `InfInt` within a specified range `[min, max]`.

- `InfInt generate_prime(int bit_length);`  
  Generates a prime number of a given bit length.

- `bool Rabin_Miller(InfInt n, int iterations = 5);`  
  Miller-Rabin primality test to check if `n` is prime.

- `InfInt power_of_two(int exponent);`  
  Computes `2^exponent` without using bit shifting.

- `InfInt generate_safe_prime(int bit_length);`  
  Generates a safe prime `p = 2q + 1` of a given bit length.

- `InfInt find_generator_safe_prime(InfInt p);`  
  Finds a generator for a safe prime `p`.

- `void encryption_decryption(int bitsize, string message);`  
  Encrypts and decrypts a message using ElGamal encryption.


## Example:


## Libraries Used
We use `#include <iostream>`, `#include <vector>`, and `#include "infint-master/InfInt.h"` in our C++ program.


## Implementation Instructions

Follow these steps to set up and run the application in the current directory.

### Prerequisites
1. Ensure you have a C++ compiler installed (e.g., `g++`).
2. Verify that all required libraries and dependencies are installed.

### Running the Application
1. Navigate to the current directory:

2. Compile the source files:
    ```bash
    g++ main.cpp elgamal.cpp -Iinclude -o main
    ```
    Note: Compilation wil result in warnings due to redefinition of predefined types. They do not affect results.

3. Run the application:
    ```bash
    ./main.exe
    ```

4. The program expects the following inputs:
      - Plaintext size must be 1 less than the number of hex digits of the key size
      - e.g. when using a 128-bit key size, plaintext must be 15 characters or smaller (or 7 characters when using 64-bit key)



