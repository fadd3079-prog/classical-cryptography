#include "caesar.h"

std::string enkripsiCaesar(std::string plainteks, int kunci)
{
    std::string cipherteks = "";

    // Memastikan kunci berada pada rentang 0 sampai 25
    kunci = kunci % 26;

    for (char huruf : plainteks)
    {

        // Jika huruf besar A-Z
        if (huruf >= 'A' && huruf <= 'Z')
        {
            char hasil = 'A' + (huruf - 'A' + kunci) % 26;
            cipherteks += hasil;
        }

        // Jika huruf kecil a-z
        else if (huruf >= 'a' && huruf <= 'z')
        {
            char hasil = 'a' + (huruf - 'a' + kunci) % 26;
            cipherteks += hasil;
        }

        // Spasi, angka, dan tanda baca tidak diubah
        else
        {
            cipherteks += huruf;
        }
    }

    return cipherteks;
}

std::string dekripsiCaesar(std::string cipherteks, int kunci)
{
    std::string plainteks = "";

    kunci = kunci % 26;

    for (char huruf : cipherteks)
    {

        // Jika huruf besar A-Z
        if (huruf >= 'A' && huruf <= 'Z')
        {
            char hasil = 'A' + (huruf - 'A' - kunci + 26) % 26;
            plainteks += hasil;
        }

        // Jika huruf kecil a-z
        else if (huruf >= 'a' && huruf <= 'z')
        {
            char hasil = 'a' + (huruf - 'a' - kunci + 26) % 26;
            plainteks += hasil;
        }

        // Spasi, angka, dan tanda baca tidak diubah
        else
        {
            plainteks += huruf;
        }
    }

    return plainteks;
}