/**
 * @file RSA.cpp
 * @author Ujhelyi Bence
 * @date 2023-05-28
 * 
 */

#include "RSA.hpp"
#include <iostream>
#include <cstring>
#include <string>
#include <random>
#include <sstream>
#include <cstdlib>
#include <ctime>

//! RSA_ALPHABET_SIZE
/*!
    Az rsa-hoz használt abc nagysága.
*/
const unsigned long long RSA_ALPHABET_SIZE = 26;

//! gcd függvény
/*!
    \param a unsigned long long
    \param b unsigned long long
    \return Visszaadja a legnagyobb közös osztót
    A gcd (greatest common divisor) függvény a két bemeneti szám legnagyobb közös osztóját számítja ki. 
    A gcd(a, b) függvény visszatér a b szám és a szám legnagyobb közös osztójával.
*/
unsigned long long RSA::gcd(unsigned long long a, unsigned long long b) const {
  while (b != 0) {
    unsigned long long temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

//! Érték nélküli konstruktor
/*!
    1. Létrehoz két véletlenszerű prímszámot, p-t és q-t. A generateRandomPrime() függvényt használja ezek generálására. 
    A p a [10000, 20000] tartományban generált prímszám lesz, míg a q a [20000, 30000] tartományban generált prímszám lesz.

    2. Kiszámítja a pí (totiense) értékét, amely a (p - 1) * (q - 1) eredménye lesz.

    3. Beállítja a nyilvános kulcsot (publicKey) a 65537 értékre, amely egy gyakran használt nyilvános relatív prím.

    4. Iteratív módon növeli az e értékét egészen addig, amíg nem talál olyan értéket, amely relatív prím pí-vel. 
    Ehhez a gcd(e, phi) függvényt használja, amely az e és pí legnagyobb közös osztóját adja vissza. 
    Amint talál egy ilyen értéket, a ciklus megszakad.

    5. Kiszámítja a privát kulcsot (privateKey) a publicKey moduláris inverzével pí modulo szerint. 
    Ehhez a modularInverse() függvényt használja.

    Ez a konstruktor tehát egy új RSA objektumot hoz létre és inicializálja a nyilvános és privát kulcsokat a fenti lépések szerint.
*/
RSA::RSA() {
    unsigned long long p = generateRandomPrime(10000, 20000);
    unsigned long long q = generateRandomPrime(20000, 30000);
    unsigned long long phi = (p - 1) * (q - 1);

    unsigned long long e = 65537;  // Commonly used public exponent
    while (e < phi) {
        if (gcd(e, phi) == 1)
            break;
        e++;
    }

    publicKey = e;
    privateKey = modularInverse(publicKey, phi);
}

//! modularInverse függvény
/*!
    \param a keresett inverz modulo m
    \param m modulus
    \return a inverze modulo m
    Az algoritmus a bővített Euklideszi algoritmust (extended Euclidean algorithm) alkalmazza, 
    hogy megtalálja a inverzét modulo m. Az alábbiakat végzi el:

    1. Létrehoz két helyi változót: m0 és y. m0 az eredeti m értéket tárolja, míg y kezdetben 0.

    2. Ellenőrzi, hogy m értéke 1-e. Ha igen, akkor visszatér 0-val, mivel az inverz nem létezik.

    3. Elindul egy while ciklus, amíg a értéke nagyobb mint 1.

    4. A ciklusban először kiszámolja az aktuális q értéket, ami az a osztva m-mel.

    5. Egy ideiglenes változóban (t) eltárolja a m értékét.

    6. Az m változót az a modulo m-re állítja.

    7. Az a változót pedig az előzőleg eltárolt t értékére állítja.

    8. Ezután (t)-ben eltárolja az y értékét.

    9. Az y változót az x - q * y értékkel frissíti.

    10. Az x változót pedig az előzőleg eltárolt t értékére állítja.

    11. Amikor a ciklus befejeződik, az x változóban lesz az a inverze modulo m.

    12. Ellenőrzi, hogy az x értéke negatív-e. Ha igen, hozzáadja m0-hoz, hogy pozitív modulo értéket kapjon.

    13. Visszatér az x értékével, ami az a inverze modulo m.
*/
unsigned long long RSA::modularInverse(unsigned long long a, unsigned long long m) const {
    long long m0 = m;
    long long y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        long long q = a / m;
        long long t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

//! generateRandomPrime függvény
/*!
    \param min alsó határ
    \param max felső határ
    \return Random prímszám
    Ez a függvény generál egy véletlenszerű prímszámot a megadott alsó (min) és felső (max) határok között.


    1. Először beállítja a random generátor kezdőértékét az srand() függvény segítségével. 
    A kezdőértéknek itt az aktuális időpontot (time(nullptr)) használja.

    2. Generál egy véletlenszerű számot a getRandomNumber() függvény segítségével a megadott min és max határok között.

    3. Amíg a generált szám nem prím (isPrime() függvény visszatérési értéke hamis), addig újra generál egy véletlenszerű számot.

    4. Ha megtalálta a prímszámot, visszatér ezzel az értékkel.
*/
unsigned long long RSA::generateRandomPrime(unsigned long long min, unsigned long long max) const {
    srand(time(nullptr));

    unsigned long long num = getRandomNumber(min, max);
    while (!isPrime(num))
        num = getRandomNumber(min, max);

    return num;
}

//! getRandomNumber függvény
/*!
    \param min alsó határ
    \param max felső határ
    \return random szám
    Létrehoz egyy random számot a megadott tartományon
*/
unsigned long long RSA::getRandomNumber(unsigned long long min, unsigned long long max) const {
    unsigned long long range = max - min + 1;
    unsigned long long num = (rand() % range) + min;
    return num;
}

//! isPrime függvény
/*!
    \param num szám
    \return ha prím akkor igaz, ha nem akkor hamis
    Megvizsgálja, hogy a kapott szám prím-e
*/
bool RSA::isPrime(unsigned long long num) const {
    if (num <= 1)
      return false;

    if (num <= 3)
      return true;

    if (num % 2 == 0 || num % 3 == 0)
      return false;

    for (unsigned long long i = 5; i * i <= num; i += 6) {
      if (num % i == 0 || num % (i + 2) == 0)
        return false;
    }

    return true;
}

//! modularExponentiation függvény
/*!

   \param base alap
   \param exponent kitevő
   \param modulus modulus
   \return moduláris hatványozás eredménye

    Ez a függvény végzi a moduláris hatványozást, vagyis a 'base' alapú 'exponent' kitevőt veszi modulo 'modulus'.


    1. Először inicializál egy 'result' változót 1 értékkel, ami az eredményt fogja tárolni.

    2. Amíg az 'exponent' nagyobb mint 0, addig folytatódik a ciklus.

    3. A ciklusban ellenőrzi, hogy az exponent páros vagy páratlan-e (exponent % 2 == 1). Ha páratlan, 
    akkor az result értékét megszorozza a base-zel és az eredményt veszi modulo modulus. 
    Ez azért van, mert a páratlan kitevők esetén az alapnak az eredménnyel kell szorozódnia.

    4. A 'base' értékét négyzetre emeli, majd veszi modulo 'modulus'. Ez a lépés a következő hatványra való előkészítést szolgálja.

    5. Az 'exponent' értékét osztja 2-vel (azaz az aktuális kitevőt osztja kettővel), 
    mivel a következő iterációban a következő hatványt kell számolni.

    6. Amikor az 'exponent' értéke eléri a 0-t, a ciklus befejeződik.

    7. Visszaadja az result értékét, ami a moduláris hatványozás eredménye.
*/
unsigned long long RSA::modularExponentiation(unsigned long long base, unsigned long long exponent, unsigned long long modulus) const {
    unsigned long long result = 1;

    while (exponent > 0) {
      if (exponent % 2 == 1)
        result = (result * base) % modulus;

      base = (base * base) % modulus;
      exponent /= 2;
    }

    return result;
}


//! encrypt függvény
/*!
    \param eredeti A titkosítandó sztring
    \return Titkosított sztring
    Titkosítja a paraméterként kapott stringet
    
    
    1. Először ellenőrzi az eredeti üzenet minden karakterét, hogy azok betűk vagy szóközök-e. 
    Ha talál olyan karaktert, ami nem betű és nem szóköz, akkor kiírja a "Nem szabályos karakter" üzenetet, 
    és "Error" értéket ad vissza.

    2. Létrehoz két üres stringet: titkos és eredeti2. Az eredeti2 a toLowerCase() függvény segítségével átalakítja az eredeti üzenetet 
    kisbetűssé.

    3. Iterál az eredeti stringen a karakterek szerint.

    4. Az aktuális karaktert (aktualis) leellenőrzi, hogy egy szóköz-e. Ha igen, akkor a c értékét a RSA_ALPHABET_SIZE-ra állítja,
    ami különleges értékkel jelöli a szóközt. Ha nem szóköz, akkor kiszámolja a karakter titkosított értékét az RSA algoritmus segítségével. 
    Ehhez a modularExponentiation() metódust használja a karaktert átkonvertálva az 'a' értéktől kezdve számmá, 
    majd a publicKey kitevővel emeli hatványra a RSA_ALPHABET_SIZE modulon belül.

    5. A c értékét átkonvertálja sztringgé (cStr), melyben minden számjegyet külön karakterként tárol.

    6. Hozzáadja a cStr-t és egy szóközt a titkos stringhez, így az aktuális karakter titkosított értékét hozzáadja a titkos üzenethez.

    7. Amikor végzett az összes karakterrel, visszaadja a titkos stringet, ami tartalmazza a titkosított üzenetet.
*/
std::string RSA::encrypt(const std::string& eredeti) const {
    for (size_t i = 0; i < eredeti.size(); ++i) {
        char f = eredeti[i];
        if (!std::isalpha(f) && f != ' ') {
            std::cout<<"Nem szabályos karakter"<<std::endl;
            return "Error";
        }
    }
    std::string titkos;
    std::string eredeti2 = toLowerCase(eredeti);
    for (size_t i = 0; i < eredeti.size(); ++i) {
        unsigned long long c;
        char aktualis = eredeti2[i];
        if (aktualis == ' ') {
            c = RSA_ALPHABET_SIZE; // Preserve spaces as a special value
        } else {
            c = (modularExponentiation(aktualis - 'a', publicKey, RSA_ALPHABET_SIZE) % RSA_ALPHABET_SIZE) + 'a';
        }
        
        std::string cStr;
        while (c != 0) {
            cStr.insert(cStr.begin(), '0' + (c % 10));
            c /= 10;
        }
        
        titkos += cStr + " ";
    }

    return titkos;
}

//! decrypt függvény
/*!
    \param titkos A visszafejtendő sztring
    \return Eredeti üzenet

    Visszafejti a titkosított sztringet.

    1. Létrehoz egy üres stringet, decryptedText, amelybe majd beilleszti a visszafejtett karaktereket.

    2. Létrehoz egy üres stringet, token, amelybe az aktuális titkosított karaktert tárolja.

    3. Az endPos változóba elmenti az első szóköz pozícióját a 'titkos' stringben, vagy std::string::npos-t(végtelen értéket), 
    ha nem talál szóközt.

    4. Amíg van újabb szóköz a 'titkos' stringben (vagyis van újabb token), a következő lépéseket végzi el:
        -A token értékét beállítja a 'titkos' stringben található részletre (startPos és endPos között).
        -A token-t átkonvertálja unsigned long long típussá a std::strtoull() függvény segítségével, 
        amely az értékét 10-es számrendszerben olvassa ki a stringből.
        -Az m értékét inicializálja.
        -Ha az c értéke megegyezik a RSA_ALPHABET_SIZE-szal, akkor az m értékét visszaállítja szóközként 
        (visszaállítja a korábban speciális értékként kezelt szóközt), Különben kiszámolja az m értékét az RSA algoritmus segítségével. 
        Ehhez a modularExponentiation() metódust használja a c karaktert átkonvertálva az 'a' értéktől kezdve számmá, 
        majd a privateKey kitevővel emeli hatványra a RSA_ALPHABET_SIZE modulon belül.
        -Az m karaktert hozzáadja a decryptedText stringhez, miután explicit konvertálja char típusra.
        -Beállítja az startPos értékét az aktuális szóköz pozíciójának + 1 értékre.
        -Újra meghatározza az endPos értékét a következő szóköz pozíciójára a 'titkos' stringben, 
        ha van még token. Ehhez az endPos értékét úgy módosítja, hogy az endPos-t az aktuális 
        részleten belül adjon hozzá a startPos értékhez.

    5. Visszaadja a decryptedText stringet, amely tartalmazza
*/
std::string RSA::decrypt(const std::string& titkos) const {
    std::string decryptedText;

    std::string token;
    size_t startPos = 0;
    size_t endPos = findSpace(titkos);

    while (endPos != std::string::npos) {
        token = titkos.substr(startPos, endPos - startPos);

        unsigned long long c = std::strtoull(token.c_str(), nullptr, 10);
        unsigned long long m;

        if (c == RSA_ALPHABET_SIZE) {
            m = ' '; // Restore preserved spaces
        } else {
            m = (modularExponentiation(c - 'a', privateKey, RSA_ALPHABET_SIZE) % RSA_ALPHABET_SIZE) + 'a';
        }

        decryptedText += static_cast<char>(m);

        startPos = endPos + 1;
        endPos = findSpace(titkos.substr(startPos));
        if (endPos != std::string::npos) {
            endPos += startPos;
        }
    }

    return decryptedText;
}





//! get_public_key függvény
/*!
    \return A nyílt kulcs
    A függvény visszaadja a nyílt kulcsot
*/
std::string RSA::get_public_key() const {
  return std::to_string(publicKey);
}

//! get_private_key függvény
/*!
    \return A titkos kulcs
    A függvény visszaadja a titkos kulcsot
*/
std::string RSA::get_private_key() const {
  return std::to_string(privateKey);
}

//! findSpace függvény
/*!
    \param str sztring
    \return A szóköz pozíciója
    Megkeresi a szóközök pozícióját, ha nem talál, akkor std::string::npos-t ad vissza
*/
size_t RSA::findSpace(const std::string& str) const{
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') {
            return i;
        }
    }
    return std::string::npos;
}

//! toLowerCase függvény
/*!
    \param str eredeti sztring
    \return kis betűs sztring
    A függvény kisbetűssé alakítja a beérkező sztringeket
*/
std::string RSA::toLowerCase(const std::string& str) const{
    std::string lowerCaseStr = str;
    for (char& c : lowerCaseStr) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
    return lowerCaseStr;
}