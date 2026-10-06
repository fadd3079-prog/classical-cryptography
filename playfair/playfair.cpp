#include <iostream>
#include <string>
#include "playfair.h"

using namespace std;

string bersihkanTeks(string teks)
{
    string hasil = "";

    for (char huruf : teks)
    {
        if (huruf >= 'a' && huruf <= 'z')
        {
            huruf = huruf - 32;
        }

        if (huruf >= 'A' && huruf <= 'Z')
        {
            if (huruf == 'J')
            {
                huruf = 'I';
            }

            hasil += huruf;
        }
    }

    return hasil;
}

bool sudahAda(string teks, char huruf)
{
    for (char isi : teks)
    {
        if (isi == huruf)
        {
            return true;
        }
    }

    return false;
}

void buatMatriksPlayfair(string kunci, char matriks[5][5])
{
    string isiMatriks = "";
    string alfabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

    kunci = bersihkanTeks(kunci);

    // masukkan huruf dari kunci tanpa duplikat
    for (char huruf : kunci)
    {
        if (!sudahAda(isiMatriks, huruf))
        {
            isiMatriks += huruf;
        }
    }

    // tambahkan sisa alfabet
    for (char huruf : alfabet)
    {
        if (!sudahAda(isiMatriks, huruf))
        {
            isiMatriks += huruf;
        }
    }

    int index = 0;

    for (int baris = 0; baris < 5; baris++)
    {
        for (int kolom = 0; kolom < 5; kolom++)
        {
            matriks[baris][kolom] = isiMatriks[index];
            index++;
        }
    }
}

void tampilkanMatriksPlayfair(string kunci)
{
    char matriks[5][5];

    buatMatriksPlayfair(kunci, matriks);

    cout << endl;
    cout << "Matriks Playfair:" << endl;

    for (int baris = 0; baris < 5; baris++)
    {
        for (int kolom = 0; kolom < 5; kolom++)
        {
            cout << matriks[baris][kolom] << " ";
        }

        cout << endl;
    }
}

string siapkanPlainteks(string plainteks)
{
    string teks = bersihkanTeks(plainteks);
    string hasil = "";

    int i = 0;

    while (i < teks.length())
    {
        char huruf1 = teks[i];

        // jika tinggal satu huruf, tambahkan x
        if (i + 1 >= teks.length())
        {
            hasil += huruf1;
            hasil += 'X';
            i++;
        }
        else
        {
            char huruf2 = teks[i + 1];

            // jika satu pasangan berisi huruf sama
            if (huruf1 == huruf2)
            {
                hasil += huruf1;
                hasil += 'X';
                i++;
            }
            else
            {
                hasil += huruf1;
                hasil += huruf2;
                i += 2;
            }
        }
    }

    return hasil;
}

void cariPosisi(
    char matriks[5][5],
    char huruf,
    int &baris,
    int &kolom)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (matriks[i][j] == huruf)
            {
                baris = i;
                kolom = j;
                return;
            }
        }
    }
}

string enkripsiPlayfair(string plainteks, string kunci)
{
    char matriks[5][5];

    buatMatriksPlayfair(kunci, matriks);

    string teks = siapkanPlainteks(plainteks);
    string cipherteks = "";

    for (int i = 0; i < teks.length(); i += 2)
    {
        char huruf1 = teks[i];
        char huruf2 = teks[i + 1];

        int baris1, kolom1;
        int baris2, kolom2;

        cariPosisi(matriks, huruf1, baris1, kolom1);
        cariPosisi(matriks, huruf2, baris2, kolom2);

        // jika berada pada baris yang sama
        if (baris1 == baris2)
        {
            cipherteks += matriks[baris1][(kolom1 + 1) % 5];
            cipherteks += matriks[baris2][(kolom2 + 1) % 5];
        }

        // jika berada pada kolom yang sama
        else if (kolom1 == kolom2)
        {
            cipherteks += matriks[(baris1 + 1) % 5][kolom1];
            cipherteks += matriks[(baris2 + 1) % 5][kolom2];
        }

        // jika membentuk persegi panjang
        else
        {
            cipherteks += matriks[baris1][kolom2];
            cipherteks += matriks[baris2][kolom1];
        }
    }

    return cipherteks;
}

string dekripsiPlayfair(string cipherteks, string kunci)
{
    char matriks[5][5];

    buatMatriksPlayfair(kunci, matriks);

    string teks = bersihkanTeks(cipherteks);
    string plainteks = "";

    for (int i = 0; i < teks.length(); i += 2)
    {
        char huruf1 = teks[i];
        char huruf2 = teks[i + 1];

        int baris1, kolom1;
        int baris2, kolom2;

        cariPosisi(matriks, huruf1, baris1, kolom1);
        cariPosisi(matriks, huruf2, baris2, kolom2);

        // jika berada pada baris yang sama
        if (baris1 == baris2)
        {
            plainteks += matriks[baris1][(kolom1 + 4) % 5];
            plainteks += matriks[baris2][(kolom2 + 4) % 5];
        }

        // jika berada pada kolom yang sama
        else if (kolom1 == kolom2)
        {
            plainteks += matriks[(baris1 + 4) % 5][kolom1];
            plainteks += matriks[(baris2 + 4) % 5][kolom2];
        }

        // jika membentuk persegi panjang
        else
        {
            plainteks += matriks[baris1][kolom2];
            plainteks += matriks[baris2][kolom1];
        }
    }

    return plainteks;
}
