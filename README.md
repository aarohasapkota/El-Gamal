# El-Gamal
ElGamal Pub-Key Encryption Written in C++ by Aaroha Sapkota and Jonathan Mazurkiewicz for CIS 4634 003 Appl Cryptography and Security Spring 2025 cohort taught by Mehrdad Nojoumian

## Key Generation
![image](https://github.com/user-attachments/assets/5b0b3f40-b632-4174-b857-1cd8634f7d1a)

## Encryption and Decryption
![image](https://github.com/user-attachments/assets/ead2b56e-7e4b-4847-a5f4-caf883f20f08)

### Functions:




## Example:
![image](https://github.com/user-attachments/assets/e4a21787-9f3f-457a-9934-0c8dd23ade09)

### Libraries Used


# Run Commands for New User

Follow these steps to set up and run the application in the current directory:

## Prerequisites
1. Ensure you have a C++ compiler installed (e.g., `g++`).
2. Verify that all required libraries and dependencies are installed.

## Running the Application
1. Navigate to the current directory:

2. Compile the source files:
    ```bash
    g++ main.cpp elgamal.cpp -Iinclude -o main
    ```

3. Run the application:
    ```bash
    ./main.exe
    ```

4. The program expects the following inputs:
      - Plaintext size must be 1 less than the number of hex digits of the key size
      - e.g. when using a 128-bit key size, plaintext must be 15 characters or smaller (or 7 characters when using 64-bit key)



