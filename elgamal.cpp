#include "elgamal.h"
using namespace std;
#include <math.h>



//Function for converting text to ascii
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

//Function to generate random number in a bound.
InfInt random_generator(InfInt a, InfInt b) {
    srand(time(NULL)); // Seed the random generator

    InfInt range = b - a + 1;
    InfInt random_offset = InfInt(rand()) % range; // Get a number in range [0, range-1]
    
    return a + random_offset; // Shift into range [a, b]
}
//Function for converting ascii to text
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

// Function to generate a number in a given range using InfInt
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

// Function to generate a prime number of a given bit length
InfInt generate_prime(int bit_length) {
    InfInt lower_bound = 1;
    for (int i = 1; i < bit_length; i++) {
        lower_bound *= 2;
    }
    InfInt upper_bound = (lower_bound * 2) - 1;
    InfInt candidate;
    int attempts = 0;
    const int MAX_ATTEMPTS = 1000;

    do {
        if (attempts++ >= MAX_ATTEMPTS) {
            cerr << "Error: Too many attempts to find a prime!\n";
            exit(1);
        }
        candidate = generate_in_range(lower_bound, upper_bound);
        candidate += 1; // Ensure it's odd
    } while (!Rabin_Miller(candidate));

    return candidate;
}

// Rabin-Miller primality test
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

// Function to compute prime factors of (p - 1)
vector<InfInt> get_prime_factors(InfInt n) {
    vector<InfInt> factors;
    
    // Handle divisibility by 2 separately
    while (n % 2 == 0) {
        if (factors.empty() || factors.back() != 2)
            factors.push_back(2);
        n /= 2;
    }

    // Check odd numbers only (reduces iterations by half)
    for (InfInt i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            if (factors.empty() || factors.back() != i){
                factors.push_back(i);
            }
            cout << i << " is a prime factor found" << endl;

            n /= i;
        }
    }

    // If n is still greater than 1, it's prime
    
    if (n > 1) {
        cout << n << " is a prime factorfound" <<endl;
        factors.push_back(n);
    }

    return factors;
}

// Function to find a generator for Z_p*
// Function to find a generator for Z_p*
InfInt find_generator(InfInt p) {
    InfInt phi = p - 1;
    vector<InfInt> factors = get_prime_factors(phi);

    cout << "Finding generator for p=" << p << ", phi=" << phi << endl;
    for (InfInt factor : factors) {
        cout << factor << " ";
    }
    cout << endl;

    for (InfInt g = 2; g < p; g++) {
        bool is_generator = true;

        // Check for each prime factor of (p-1)
        for (InfInt factor : factors) {
            InfInt exp = phi / factor;
            if (mod_exp(g, exp, p) == 1) {
                is_generator = false;
                break;
            }
        }

        if (is_generator) {
            cout << "Generator found: " << g << endl;
            return g;
        }
    }

    cerr << "Error: No generator found for p=" << p << endl;
    exit(1);
}





// Function to generate the ElGamal key pair
// void key_gen() {
//     int bit_length;
//     cout << "Enter key size (in bits, e.g., 32, 64, 128, 256): ";
//     cin >> bit_length;
//     cout << "Generating a " << bit_length << "-bit prime...\n";
//     InfInt p = generate_prime(bit_length);
//     cout << "Prime p generated: " << p << endl;

//     cout << "Finding a generator for Z_" << p << "*...\n";
//     InfInt g = find_generator(p);
//     cout << "Generator g found: " << g << endl;

//     cout << "Selecting a private key...\n";
//     InfInt x = generate_in_range(1, p - 2);
//     cout << "Private key x selected: " << x << endl;

//     cout << "Computing Alpha_Mod_A...\n";
//     InfInt h = mod_exp(g, x, p);
//     cout << "Alpha_Mode_A key computed: " << h << endl;

//     cout << "ElGamal Key Generation Complete!" << endl;
//     cout << "Public Key: (p=" << p << ", g=" << g << ", h=" << h << ")" << endl;
//     cout << "Private Key: x=" << x << endl;
// }

void encryption_decryption(int bitsize, string message){
    InfInt messageNUM = convertToASCII(message);

    cout << "Generating a " << bitsize << "-bit prime...\n";
    InfInt p = generate_prime(bitsize);

    cout << "Finding a generator for Z_" << p << "*...\n";
    InfInt g = find_generator(p);
    cout << "Generator g found: " << g << endl;

    cout << "Selecting a private key...\n";
    InfInt x = generate_in_range(1, p - 2);
    cout << "Private key x selected: " << x << endl;

    cout << "Computing Alpha_Mod_A...\n";
    InfInt h = mod_exp(g, x, p);
    cout << "Alpha_Mode_A key computed: " << h << endl;

    cout << "ElGamal Key Generation Complete!" << endl;
    cout << "Public Key: (p=" << p << ", g=" << g << ", h=" << h << ")" << endl;
    cout << "Private Key: x=" << x << endl;

    cout << "Computing k random between 1 and p-2" << endl;
    InfInt k = random_generator(1,p-2);
    cout << "K generated: " << k << endl;

    cout << "Computing gamma.." << endl;
    InfInt gamma = mod_exp(g,k,p);
    cout << "Gamma generated: " << gamma << endl;

    cout << "Computing Delta.." << endl;
    InfInt delta = (messageNUM * mod_exp(h,k,p) % p);
    cout << "Delta Generated: " << delta << endl;

    cout << "Ciper Text Generated!!" << endl;
    cout << endl << "Ciphertext is Gamma: " << gamma << " + Delta: " << delta << endl;

    cout << "Calling Decryption Now...." << endl;

    InfInt dec_message = (delta * mod_exp(gamma, p - 1 - x, p) % p );
    string dec_text = asciiToText(dec_message);
    cout << "Decrypted message is: " << dec_text << endl;



}

