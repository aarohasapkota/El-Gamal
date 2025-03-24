
#include <random>
#include <iostream>
#include <typeinfo>
using namespace std;

 // Modular Exponentiation using Repeated Square and Multiply
 long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;  // Initialize result
    base = base % mod;     // Ensure base is within mod

    while (exp > 0) {
        // If exponent is odd, multiply base with result
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        
        // Square the base and reduce the exponent by half
        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

bool Rabin_Miller(int n){

    // Obvious composite
    if(n % 2 == 0){
        return false;
    }
    // Step 1: Finding n - 1 = 2^k . m
    int temp = n - 1;
    int k, m = 0;

    while( true ){
        if( temp % 2 == 0){
            k+=1;
            temp = temp / 2;
        } else {
            break;
        }
    }
    m = (n-1)/(pow(2,k));


    //Step 2: Generate Random Number a such that 1<a<n-1
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,n-1);
    int a = dist(gen);

    // Step 3: Test for primality
     auto b = mod_exp(a,m,n);
     if(b == -1 ){
        return true;
     }
     if(b == 1){
        return false;
     }

     while( true ){
        b = mod_exp(b,2,n);
        if(b == -1 ){
            return true;
         }
         if(b == 1){
            return false;
         }
     }



    return false;
}

