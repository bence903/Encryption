/**
 * @file RSA.hpp
 * @author Ujhelyi Bence (ujhelyibence@gmail.com)
 * @version 0.1
 * @date 2023-05-15
 * 
 */

#ifndef RSA_HPP
#define RSA_HPP

#include "Encryption.hpp"

//! RSA osztály
class RSA : public Encryption {
private:

    //! publicKey változó
    unsigned long long publicKey;

    //! privateKey változó
    unsigned long long privateKey;

    // generateRandomPrime függvény
    unsigned long long generateRandomPrime(unsigned long long min, unsigned long long max) const;

    // isPrime függvény
    bool isPrime(unsigned long long num) const;

    // modularExponentiation függvény
    unsigned long long modularExponentiation(unsigned long long base, unsigned long long exponent, unsigned long long modulus) const;
    
    // modularInverse függvény
    unsigned long long modularInverse(unsigned long long a, unsigned long long m) const;
    
    // gcd függvény
    unsigned long long gcd(unsigned long long a, unsigned long long b) const;
    
    // findSpace függvény
    size_t findSpace(const std::string& str) const;

    // getRandomNumber függvény
    unsigned long long getRandomNumber(unsigned long long min, unsigned long long max) const;
    
    // toLowerCase függvény
    std::string toLowerCase(const std::string& str) const;

public:
    
    // Default konstruktor
    RSA();

    // encrypt függvény
    std::string encrypt(const std::string& eredeti) const override;
    
    // decrypt függvény
    std::string decrypt(const std::string& titkos) const override;
    
    // get_public_key függvény
    std::string get_public_key() const override;
    
    // get_private_key függvény
    std::string get_private_key() const override;
};

#endif
