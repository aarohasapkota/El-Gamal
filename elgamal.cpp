#include "elgamal.h"
using namespace std;

//Function for converting text to ascii while using the InfInt library
InfInt convertToASCII(string text)
{
    string result = "";
    for (int i = 0; i < text.length(); i++)
    {
        char x = text[i];
        result += to_string(int(x));
    }
    InfInt number = result;
    return number;
}

//Converting ascii to text
string asciiToText(InfInt number)
{
    int num = 0;
    string text = "";
    string n = number.toString();
    for (int i = 0; i < n.length(); i++) {
 
        // Append the current digit
        num = num * 10 + (n[i] - '0');
 
        // If num is within the required range
        if (num >= 32 && num <= 122) {
 
            // Convert num to char
            char ch = (char)num;
            text += ch;
 
            // Reset num to 0
            num = 0;
        }
    }
    return text;
}

// Modular exponentiation using repeated squaring
InfInt mod_exp(InfInt base, InfInt exp, InfInt mod) {
    InfInt result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Generate a number in a given range using InfInt
InfInt generate_in_range(InfInt min, InfInt max) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL)); // Seed once
        seeded = true;
    }
    InfInt range = max - min + 1;
    InfInt random_value = InfInt(rand()) % range;
    return min + random_value;
}

// Rabin-Miller primality test. Uses 5 iterations by default, which provides a 98% accuracy. Increase iterations for higher accuracy.
bool Rabin_Miller(InfInt n, int iterations) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    InfInt m = n - 1;
    int k = 0;
    while (m % 2 == 0) {
        m /= 2;
        k++;
    }

    for (int j = 0; j < iterations; j++) {
        InfInt a = generate_in_range(2, n - 2);
        InfInt x = mod_exp(a, m, n);
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

InfInt power_of_two(int exponent) {
    InfInt result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= 2;
    }
    return result;
}
// This function is used to generate a safe prime number (p = 2q + 1) for ElGamal encryption. This speeds up computation for finding a generator later.
InfInt generate_safe_prime(int bit_length) {
    if (bit_length < 16) {
        cerr << "Error: Minimum bit length must be at least 16." << endl;
        exit(1);
    }

    // Min and max ensure that q is roughly half the size of p but also large enough to be secure.
    InfInt min = power_of_two(bit_length - 1);  // 2^(bit_length-1)
    InfInt max = power_of_two(bit_length) - 1;  // 2^bit_length - 1

    while (true) {
        
        // Generate a random prime q
        InfInt q = generate_in_range(min / 2, max / 2);
        if (q % 2 == 0) q += 1;  // Ensure q is odd

        // Check if q is prime
        if (Rabin_Miller(q)) {
            InfInt p = InfInt(2) * q + 1;  // Compute p = 2q + 1
            if (Rabin_Miller(p)) return p;  // Ensure p is also prime
        }
    }
}

// This function finds a generator for a safe prime p. This is done by checking if (g^2 % p != 1) and (g^q % p != 1).
// If both conditions are met, then g is a generator for Z_p*.
InfInt find_generator_safe_prime(InfInt p) {
    InfInt q = (p - 1) / 2;  // Since p = 2q + 1

    cout << "Finding generator for safe prime p=" << p << ", q=" << q << endl;

    for (InfInt g = 2; g < p; g++) {
        
        if (mod_exp(g, 2, p) != 1 && mod_exp(g, q, p) != 1) {
            cout << "Generator found: " << g << endl;
            return g;
        }
    }

    cerr << "Error: No generator found for safe prime p=" << p << endl;
    exit(1);
}
// Driver function to encrypt and decrypt a message using ElGamal encryption.
void encryption_decryption(int bitsize, string message){
    InfInt messageNUM = convertToASCII(message);

    cout << "Generating a " << bitsize << "-bit prime...\n";
    InfInt p = generate_safe_prime(bitsize);

    cout << "Finding a generator for Z_" << p << "*...\n";
    InfInt g = find_generator_safe_prime(p);

    cout << "Selecting a private key...\n";
    InfInt x = generate_in_range(1, p - 2);
    cout << "Private key selected: " << x << endl;

    cout << "Computing alpha (mod a)...\n";
    InfInt h = mod_exp(g, x, p);
    cout << "alpha (mod a) " << h << endl;

    cout << "ElGamal Key Generation Complete!" << endl;
    cout << "Public Key: (p=" << p << ", g=" << g << ", h=" << h << ")" << endl;
    cout << "Private Key: x=" << x << endl;

    cout << "Computing k random between 1 and p-2" << endl;
    InfInt k = generate_in_range(1,p-2);
    cout << "k generated: " << k << endl;

    cout << "Computing gamma.." << endl;
    InfInt gamma = mod_exp(g,k,p);
    cout << "Gamma generated: " << gamma << endl;

    cout << "Computing Delta.." << endl;
    InfInt delta = (messageNUM * mod_exp(h,k,p) % p);
    cout << "Delta Generated: " << delta << endl;

    cout << "Cipher Text Generated!!" << endl;
    cout << endl << "Ciphertext is Gamma: " << gamma << " + Delta: " << delta << endl;

    cout << "Calling Decryption Now...." << endl;

    InfInt dec_message = (delta * mod_exp(gamma, p - 1 - x, p) % p );
    string dec_text = asciiToText(dec_message);
    cout << "Decrypted message is: " << dec_text << endl;
}

