#include <iostream>
#include <string>

#include "caesar/caesar.h"

using namespace std;

int main()
{
    string teks;
    string hasil;
    int kunci;
    int pilihan;

    cout << "=== Caesar Cipher ===" << endl;
    cout << "1. Enkripsi" << endl;
    cout << "2. Dekripsi" << endl;
    cout << "Pilih: ";
    cin >> pilihan;

    cin.ignore();

    cout << "Masukkan teks: ";
    getline(cin, teks);

    cout << "Masukkan kunci: ";
    cin >> kunci;

    if (pilihan == 1)
    {
        hasil = enkripsiCaesar(teks, kunci);

        cout << endl;
        cout << "Cipherteks: " << hasil << endl;
    }
    else if (pilihan == 2)
    {
        hasil = dekripsiCaesar(teks, kunci);

        cout << endl;
        cout << "Plainteks: " << hasil << endl;
    }
    else
    {
        cout << "Pilihan tidak tersedia." << endl;
    }

    return 0;
}