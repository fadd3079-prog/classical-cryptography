#include <iostream>
#include "transposisi_kolom.h"

using namespace std;

string hapusSpasi(string teks)
{
    string hasil = "";

    for (char karakter : teks)
    {
        if (karakter != ' ')
        {
            hasil += karakter;
        }
    }

    return hasil;
}

void tampilkanMatriksTransposisi(string teks, int kunci)
{
    if (kunci <= 0)
    {
        return;
    }

    teks = hapusSpasi(teks);

    int panjang = teks.length();
    int jumlahBaris = (panjang + kunci - 1) / kunci;

    cout << endl;
    cout << "Teks tanpa spasi: " << teks << endl;
    cout << endl;
    cout << "Matriks Transposisi:" << endl;

    for (int kolom = 0; kolom < kunci; kolom++)
    {
        cout << kolom + 1 << " ";
    }

    cout << endl;

    for (int baris = 0; baris < jumlahBaris; baris++)
    {
        for (int kolom = 0; kolom < kunci; kolom++)
        {
            int posisi = baris * kunci + kolom;

            if (posisi < panjang)
            {
                cout << teks[posisi] << " ";
            }
            else
            {
                cout << "- ";
            }
        }

        cout << endl;
    }
}

string enkripsiTransposisi(string plainteks, int kunci)
{
    string cipherteks = "";

    if (kunci <= 0)
    {
        return "";
    }

    plainteks = hapusSpasi(plainteks);

    int panjang = plainteks.length();
    int jumlahBaris = (panjang + kunci - 1) / kunci;

    // membaca teks per kolom dari atas ke bawah
    for (int kolom = 0; kolom < kunci; kolom++)
    {
        for (int baris = 0; baris < jumlahBaris; baris++)
        {
            int posisi = baris * kunci + kolom;

            if (posisi < panjang)
            {
                cipherteks += plainteks[posisi];
            }
        }
    }

    return cipherteks;
}

string dekripsiTransposisi(string cipherteks, int kunci)
{
    string plainteks = "";

    if (kunci <= 0)
    {
        return "";
    }

    cipherteks = hapusSpasi(cipherteks);

    int panjang = cipherteks.length();
    int barisPenuh = panjang / kunci;
    int sisa = panjang % kunci;

    int jumlahBaris = barisPenuh;

    if (sisa > 0)
    {
        jumlahBaris++;
    }

    // mengembalikan karakter ke posisi awal
    for (int baris = 0; baris < jumlahBaris; baris++)
    {
        for (int kolom = 0; kolom < kunci; kolom++)
        {
            int panjangKolom = barisPenuh;

            if (kolom < sisa)
            {
                panjangKolom++;
            }

            if (baris < panjangKolom)
            {
                int tambahan = kolom;

                if (kolom > sisa)
                {
                    tambahan = sisa;
                }

                int posisi = kolom * barisPenuh + tambahan + baris;

                plainteks += cipherteks[posisi];
            }
        }
    }

    return plainteks;
}