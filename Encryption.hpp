/**
 * @file Encryption.hpp
 * @author Ujhelyi Bence (ujhelyibence@gmail.com)
 * @version 0.1
 * @date 2023-05-15
 * 
 */

#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP 

#include <iostream>
#include <string>
#include <stdexcept>

//!  Encryption osztály. 
/*!
  Absztrakt titkosító osztály.
*/
class Encryption {
public:

  //! Destruktor.
    /*!
      Virtuális destruktor.
    */

  virtual ~Encryption() = default;

  //! encrypt függvény.
    /*!
      Titkosító függvény.
    */
  virtual std::string encrypt(const std::string& plaintext) const = 0;

  //! decrypt függvény.
    /*!
      Titkosítás feloldásáért felelős függvény.
    */
  virtual std::string decrypt(const std::string& ciphertext) const = 0;

  //! get_public_key() függvény.
    /*!
      RSA-hoz a nyilvános kulcs lekérdezése.
    */
  virtual std::string get_public_key() const = 0;

  //! get_private_key() függvény .
    /*!
      RSA-hoz a privát kulcs lekérdezése.
    */
  virtual std::string get_private_key() const = 0;
};

#endif