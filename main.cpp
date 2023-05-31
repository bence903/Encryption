/**
 * @file main.cpp
 * @author Ujhelyi Bence (ujhelyibence@gmail.com)
 * @date 2023-05-15
 * 
 */

#include <iostream>
#include <string>
#include "Encryption.hpp"
#include "RSA.hpp"
#include "Caesar.hpp"

//! Main függvény
/*!
    Teszteli a komponenseket
*/

int main() {

    //RSA algoritmus tesztelése
    std::cout <<std::endl<< "=== RSA Algoritmus Teszt ===" << std::endl<<std::endl;
    int n = 0;
    try{
        while (n != 3) {
            if (n == 0) {
                RSA rsa;
                std::string text1 = "weores sandor";
                std::string encryptedMessage = rsa.encrypt(text1);
                std::cout << "Eredeti: " << text1 << std::endl;
                std::cout << "Titkosított: " << encryptedMessage << std::endl;
                std::string titkos = rsa.decrypt(encryptedMessage);
                std::cout << "Visszafejtett: " << titkos << std::endl;
                if (titkos == text1) {
                    std::cout << "SIKERES 1/3" << std::endl;
                } else {
                    std::cout << "SIKERTELEN 1/3" << std::endl;
                }
                std::cout << std::endl;
            } else if (n == 1) {
                RSA rsa2;
                std::string text2 = "CSUPA NAGY BETU";
                std::string encryptedMessage2 = rsa2.encrypt(text2);
                std::cout << "Eredeti: " << text2 << std::endl;
                std::cout << "Titkosított: " << encryptedMessage2 << std::endl;
                std::string titkos2 = rsa2.decrypt(encryptedMessage2);
                std::cout << "Visszafejtett: " << titkos2 << std::endl;
                if (titkos2 == "csupa nagy betu") {
                    std::cout << "SIKERES 2/3" << std::endl;
                } else {
                    std::cout << "SIKERTELEN 2/3" << std::endl;
                }
                std::cout << std::endl;
            } else if (n == 2){
                RSA rsa3;
                std::string text3 = "+!%/=ŕŘ#$řŔŖ";
                std::cout << "Eredeti: " << text3 << std::endl;
                std::string encryptedMessage3 = rsa3.encrypt(text3);
                if(encryptedMessage3 == "Error"){
                    std::cout << "SIKERES 3/3" << std::endl;
                    throw "Bad character";
                }
                else{
                    std::cout << encryptedMessage3 << std::endl;
                    std::cout << "SIKERTELEN 3/3" << std::endl;
                }
                std::cout << std::endl;

            }

            n++;
        }
    }
    catch(std::exception& e){
        std::cerr << "HIBA:  " << e.what() << std::endl;
    }
    catch(...){
        std::cerr << "ISMERETLEN HIBA!" << std::endl;
    }


    std::cout<<std::endl;

    //Caesar algoritmus tesztelése
    std::cout << "=== Caesar Algoritmus Teszt ===" << std::endl;

    std::cout<<std::endl;
    n = 0;
    int count = 0;
    try
        {
            while (n != 3)
            {
                
                    if(n == 0){
                        //ELSŐ TESZT ESET
                        Caesar caesar(1);
                        std::string text1 = "A csokod festi kekre az eget,";
                        std::string encrypted1 = caesar.encrypt(text1);
                        std::cout << "Eredeti: " << text1 << std::endl;
                        std::cout << "Titkosított: " << encrypted1 << std::endl; //MINDEN BETŰ 1-EL EL VAN TOLVA AZ ABC-BEN
                        std::string decrypted1 = caesar.decrypt(encrypted1);
                        std::cout << "Visszafejtett: " << decrypted1 << std::endl;
                        if(decrypted1 == text1){
                            count++;
                        }
                        else{
                            std::cout<<"SIKERTELEN 1/3"<<std::endl;
                        }
                        std::cout<<std::endl;
                        
                    }
                    else if (n == 1)
                    {
                        //MÁSODIK TESZT ESET
                        Caesar caesar(2);
                        std::string text2 = "szemed szinetol zoldulnek a fak.";
                        std::string encrypted2 = caesar.encrypt(text2);
                        std::cout << "Eredeti: " << text2 << std::endl;
                        std::cout << "Titkosított: " << encrypted2 << std::endl; //MINDEN BETŰ 2-VEL EL VAN TOLVA AZ ABC-BEN
                        std::string decrypted2 = caesar.decrypt(encrypted2);
                        std::cout << "Visszafejtett: " << decrypted2 << std::endl;
                        if(decrypted2 == text2){
                            count++;
                        }
                        else{
                            std::cout<<"SIKERTELEN 2/3"<<std::endl;
                        }
                        std::cout<<std::endl;
                    }
                    else if (n == 2)
                    {
                        //HARMADIK TESZT ESET
                        Caesar caesar(0);
                        std::string text3 = "Nelkuled ures az osszes kepkeret";
                        std::string encrypted3 = caesar.encrypt(text3);
                        std::cout << "Eredeti: " << text3 << std::endl;
                        std::cout << "Titkosított: " << text3 << std::endl; //UGYANAZ MINT AZ EREDETI
                        std::string decrypted3 = caesar.decrypt(encrypted3);
                        std::cout << "Visszafejtett: " << decrypted3 << std::endl;
                        if(decrypted3 == text3){
                            count++;
                        }
                        else{
                            std::cout<<"SIKERTELEN 3/3"<<std::endl;
                        }
                        std::cout<<std::endl;
                    }

                    
                    
                    n++;
                
            }
    }
    catch(std::exception& e){
        std::cerr << "HIBA:  " << e.what() << std::endl;
    }
    catch(...){
            std::cerr << "ISMERETLEN HIBA!" << std::endl;
    }
    
    std::cout << "SIKERES: "<<count<<"/3"<<std::endl;


    return 0;
}







