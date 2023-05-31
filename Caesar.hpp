/**
 * @file Caesar.hpp
 * @author Ujhelyi Bence (ujhelyibence@gmail.com)
 * @version 0.1
 * @date 2023-05-15
 * 
 */

#ifndef CAESAR_HPP
#define CAESAR_HPP

#include <iostream>
#include <string>
#include "Encryption.hpp"

//! Caesar osztály
class Caesar : public Encryption {
private:

  // shift_char függvény
  static char shift_char(char c, int shift) {
    if (!isalpha(c)) return c;
    char base = isupper(c) ? 'A' : 'a';
    return (c - base + shift + 26) % 26 + base;
  }
  // shift változó
  int shift_;
public:

  // Konstruktor
  Caesar(int shift) : shift_(shift) {}

  // encrypt függvény deklarációja
  std::string encrypt(const std::string& text) const override;

   // decrypt függvény deklarációja
  std::string decrypt(const std::string& secrettext) const override;

   // get_public_key függvény deklarációja
  std::string get_public_key() const override;

   // get_private_key függvény deklarációja
  std::string get_private_key() const override;

};

#endif