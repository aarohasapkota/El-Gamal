# El-Gamal
ElGamal Pub-Key Encryption Written in C++ by Aaroha Sapkota and Jonathan Mazurkiewicz for CIS 4634 003 Appl Cryptography and Security Spring 2025 cohort taught by Mehrdad Nojoumian


## Key Generation
![image](https://github.com/user-attachments/assets/5b0b3f40-b632-4174-b857-1cd8634f7d1a)

### Functions:
      generate_large_prime()
      generate_generator_alpha()
      
      

## Encryption and Decryption
![image](https://github.com/user-attachments/assets/ead2b56e-7e4b-4847-a5f4-caf883f20f08)

### Functions:
#### Enc:
      select_random_integer()
      compute_gamma()
      compute_delta()
      send_ciphertext()
#### Dec:
      compute_gamma_modular_expression()
      compute_gamma_times_delta_modular_expression()


## Example:
![image](https://github.com/user-attachments/assets/e4a21787-9f3f-457a-9934-0c8dd23ade09)

### Libraries Used
Modular Arithmetic: https://github.com/hurchalla/modular_arithmetic 

CryptoPP: https://github.com/weidai11/cryptopp



