#include "caesar.h"

string enkripsiCaesar(string plainteks, int kunci) {
    string cipherteks = "";

    // memastikan kunci berada di antara 0 sampai 25
    kunci = kunci % 26;

    if (kunci < 0) {
        kunci = kunci + 26;
    }

    for (char huruf : plainteks) {

        // enkripsi huruf besar
        if (huruf >= 'A' && huruf <= 'Z') {
            huruf = 'A' + (huruf - 'A' + kunci) % 26;
        }

        // enkripsi huruf kecil
        else if (huruf >= 'a' && huruf <= 'z') {
            huruf = 'a' + (huruf - 'a' + kunci) % 26;
        }

        cipherteks += huruf;
    }

    return cipherteks;
}


string dekripsiCaesar(string cipherteks, int kunci) {
    string plainteks = "";

    // memastikan kunci berada di antara 0 sampai 25
    kunci = kunci % 26;

    if (kunci < 0) {
        kunci = kunci + 26;
    }

    for (char huruf : cipherteks) {

        // dekripsi huruf besar
        if (huruf >= 'A' && huruf <= 'Z') {
            huruf = 'A' + (huruf - 'A' - kunci + 26) % 26;
        }

        // dekripsi huruf kecil
        else if (huruf >= 'a' && huruf <= 'z') {
            huruf = 'a' + (huruf - 'a' - kunci + 26) % 26;
        }

        plainteks += huruf;
    }

    return plainteks;
}