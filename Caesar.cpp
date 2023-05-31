/**
 * @file Caesar.cpp
 * @author Ujhelyi Bence (ujhelyibence@gmail.com)
 * @version 0.1
 * @date 2023-05-15
 * 
 */

#include <iostream>
#include <string>
#include "Caesar.hpp"

//! encrypt függvény
/*!
  \param text Titkosítandó szöveg
  \return Titkosított szöveg
  Titkosítja a beérkező sztringet és visszaadja a titkosított sztringet;
*/
std::string Caesar::encrypt(const std::string& text) const{
    std::string secrettext;
    for (char c : text) {
      secrettext += shift_char(c, shift_);
    }
    return secrettext;
  }

//! decrypt függvény
/*!
  \param secrettext Titkos szöveg
  \return Visszafejtett szöveg

  Visszafejti a titkos szöveget
*/
std::string Caesar::decrypt(const std::string& secrettext) const{
    std::string text;
    for (char c : secrettext) {
      text += shift_char(c, -shift_);
    }
    return text;
}

//! get_public_key függvény
/*!
  A kompatibilitás miatt muszáj inicializálni a függvént, még akkor is ha nem ad vissza semmit
*/
std::string Caesar::get_public_key() const {
    return "";
}

//! get_private_key függvény
/*!
  A kompatibilitás miatt muszáj inicializálni a függvént, még akkor is ha nem ad vissza semmit
*/
std::string Caesar::get_private_key() const {
    return "";
}