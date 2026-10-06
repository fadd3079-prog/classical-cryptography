#include <iostream>
#include <string>

#include "caesar/caesar.h"
#include "playfair/playfair.h"
#include "transposisi_kolom/transposisi_kolom.h"

using namespace std;

int main()
{
    int algoritma;

    cout << "=== Kriptografi Klasik ===" << endl;
    cout << "1. Caesar Cipher" << endl;
    cout << "2. Playfair Cipher" << endl;
    cout << "3. Transposisi Kolom" << endl;
    cout << "Pilih algoritma: ";
    cin >> algoritma;

    cin.ignore();

    if (algoritma == 1)
    {
        string teks;
        string hasil;
        int kunci;
        int pilihan;

        cout << endl;
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
            cout << "Cipherteks: " << hasil << endl;
        }
        else if (pilihan == 2)
        {
            hasil = dekripsiCaesar(teks, kunci);
            cout << "Plainteks: " << hasil << endl;
        }
        else
        {
            cout << "Pilihan tidak tersedia." << endl;
        }
    }

    else if (algoritma == 2)
    {
        string teks;
        string kunci;
        string hasil;
        int pilihan;

        cout << endl;
        cout << "=== Playfair Cipher ===" << endl;
        cout << "1. Enkripsi" << endl;
        cout << "2. Dekripsi" << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        cin.ignore();

        cout << "Masukkan teks: ";
        getline(cin, teks);

        cout << "Masukkan kunci: ";
        getline(cin, kunci);

        tampilkanMatriksPlayfair(kunci);

        if (pilihan == 1)
        {
            cout << endl;
            cout << "Plainteks setelah disiapkan: " << siapkanPlainteks(teks) << endl;

            hasil = enkripsiPlayfair(teks, kunci);

            cout << "Cipherteks: " << hasil << endl;
        }
        else if (pilihan == 2)
        {
            hasil = dekripsiPlayfair(teks, kunci);

            cout << endl;
            cout << "Plainteks hasil dekripsi: " << hasil << endl;
        }
        else
        {
            cout << "Pilihan tidak tersedia." << endl;
        }
    }

    else if (algoritma == 3)
    {
        string teks;
        string hasil;
        int kunci;
        int pilihan;

        cout << endl;
        cout << "=== Transposisi Kolom ===" << endl;
        cout << "1. Enkripsi" << endl;
        cout << "2. Dekripsi" << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        cin.ignore();

        cout << "Masukkan teks: ";
        getline(cin, teks);

        cout << "Masukkan jumlah kolom: ";
        cin >> kunci;

        if (kunci <= 0)
        {
            cout << "Kunci harus lebih dari 0." << endl;
        }
        else if (pilihan == 1)
        {
            tampilkanMatriksTransposisi(teks, kunci);

            hasil = enkripsiTransposisi(teks, kunci);

            cout << endl;
            cout << "Cipherteks: " << hasil << endl;
        }
        else if (pilihan == 2)
        {
            hasil = dekripsiTransposisi(teks, kunci);

            tampilkanMatriksTransposisi(hasil, kunci);

            cout << endl;
            cout << "Plainteks: " << hasil << endl;
        }
        else
        {
            cout << "Pilihan tidak tersedia." << endl;
        }
    }

    else
    {
        cout << "Pilihan algoritma tidak tersedia." << endl;
    }

    return 0;
}