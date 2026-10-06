#include <iostream>
#include "playfair.h"

using namespace std;

string bersihkanTeksPlayfair(string teks)
{
    string hasil = "";

    for (char huruf : teks)
    {
        // mengubah huruf kecil menjadi huruf besar
        if (huruf >= 'a' && huruf <= 'z')
        {
            huruf = huruf - 32;
        }

        // hanya huruf alfabet yang diproses
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

bool sudahAdaPlayfair(string teks, char huruf)
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

void buatMatriksPlayfair(
    string kunci,
    char matriks[5][5])
{
    string isiMatriks = "";
    string alfabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

    kunci = bersihkanTeksPlayfair(kunci);

    // memasukkan huruf kunci tanpa duplikat
    for (char huruf : kunci)
    {
        if (!sudahAdaPlayfair(isiMatriks, huruf))
        {
            isiMatriks += huruf;
        }
    }

    // menambahkan alfabet yang belum digunakan
    for (char huruf : alfabet)
    {
        if (!sudahAdaPlayfair(isiMatriks, huruf))
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

string siapkanPlainteksPlayfairData(
    string plainteks,
    vector<int> &posisiFiller)
{
    string teks = bersihkanTeksPlayfair(plainteks);
    string hasil = "";

    posisiFiller.clear();

    int i = 0;

    while (i < teks.length())
    {
        char huruf1 = teks[i];

        // jika hanya tersisa satu huruf
        if (i + 1 >= teks.length())
        {
            hasil += huruf1;
            hasil += 'X';

            posisiFiller.push_back(
                hasil.length() - 1);

            i++;
        }
        else
        {
            char huruf2 = teks[i + 1];

            // jika dua huruf dalam pasangan sama
            if (huruf1 == huruf2)
            {
                hasil += huruf1;
                hasil += 'X';

                posisiFiller.push_back(
                    hasil.length() - 1);

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

string siapkanPlainteksPlayfair(string plainteks)
{
    vector<int> posisiFiller;

    return siapkanPlainteksPlayfairData(
        plainteks,
        posisiFiller);
}

bool adaPosisiFiller(
    vector<int> posisiFiller,
    int posisi)
{
    for (int isi : posisiFiller)
    {
        if (isi == posisi)
        {
            return true;
        }
    }

    return false;
}

string hapusFillerPlayfair(
    string teks,
    vector<int> posisiFiller)
{
    string hasil = "";

    for (int i = 0; i < teks.length(); i++)
    {
        if (!adaPosisiFiller(posisiFiller, i))
        {
            hasil += teks[i];
        }
    }

    return hasil;
}

bool validasiCipherPlayfair(string cipherteks)
{
    int jumlahHuruf = 0;

    for (char karakter : cipherteks)
    {
        // spasi kelompok boleh diabaikan
        if (karakter == ' ')
        {
            continue;
        }

        if (karakter >= 'a' && karakter <= 'z')
        {
            karakter = karakter - 32;
        }

        // cipher hanya boleh berisi alfabet
        if (karakter < 'A' || karakter > 'Z')
        {
            return false;
        }

        // matriks playfair tidak mempunyai huruf j
        if (karakter == 'J')
        {
            return false;
        }

        jumlahHuruf++;
    }

    if (jumlahHuruf == 0)
    {
        return false;
    }

    // cipher harus terdiri dari pasangan huruf
    if (jumlahHuruf % 2 != 0)
    {
        return false;
    }

    return true;
}

string kelompokkanPlayfair(
    string teks,
    int jumlahHuruf)
{
    string hasil = "";

    if (jumlahHuruf <= 0)
    {
        return teks;
    }

    int hitung = 0;

    for (int i = 0; i < teks.length(); i++)
    {
        hasil += teks[i];
        hitung++;

        if (
            hitung == jumlahHuruf &&
            i != teks.length() - 1)
        {
            hasil += ' ';
            hitung = 0;
        }
    }

    return hasil;
}

void cariPosisiPlayfair(
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

string enkripsiPlayfair(
    string plainteks,
    string kunci)
{
    char matriks[5][5];

    buatMatriksPlayfair(kunci, matriks);

    string teks =
        siapkanPlainteksPlayfair(plainteks);

    string cipherteks = "";

    for (int i = 0; i < teks.length(); i += 2)
    {
        char huruf1 = teks[i];
        char huruf2 = teks[i + 1];

        int baris1, kolom1;
        int baris2, kolom2;

        cariPosisiPlayfair(
            matriks,
            huruf1,
            baris1,
            kolom1);

        cariPosisiPlayfair(
            matriks,
            huruf2,
            baris2,
            kolom2);

        // jika berada pada baris yang sama
        if (baris1 == baris2)
        {
            cipherteks +=
                matriks[baris1][(kolom1 + 1) % 5];

            cipherteks +=
                matriks[baris2][(kolom2 + 1) % 5];
        }

        // jika berada pada kolom yang sama
        else if (kolom1 == kolom2)
        {
            cipherteks +=
                matriks[(baris1 + 1) % 5][kolom1];

            cipherteks +=
                matriks[(baris2 + 1) % 5][kolom2];
        }

        // jika membentuk persegi panjang
        else
        {
            cipherteks +=
                matriks[baris1][kolom2];

            cipherteks +=
                matriks[baris2][kolom1];
        }
    }

    return cipherteks;
}

string dekripsiPlayfair(
    string cipherteks,
    string kunci)
{
    if (!validasiCipherPlayfair(cipherteks))
    {
        return "";
    }

    char matriks[5][5];

    buatMatriksPlayfair(kunci, matriks);

    string teks =
        bersihkanTeksPlayfair(cipherteks);

    string plainteks = "";

    for (int i = 0; i < teks.length(); i += 2)
    {
        char huruf1 = teks[i];
        char huruf2 = teks[i + 1];

        int baris1, kolom1;
        int baris2, kolom2;

        cariPosisiPlayfair(
            matriks,
            huruf1,
            baris1,
            kolom1);

        cariPosisiPlayfair(
            matriks,
            huruf2,
            baris2,
            kolom2);

        // jika berada pada baris yang sama
        if (baris1 == baris2)
        {
            plainteks +=
                matriks[baris1][(kolom1 + 4) % 5];

            plainteks +=
                matriks[baris2][(kolom2 + 4) % 5];
        }

        // jika berada pada kolom yang sama
        else if (kolom1 == kolom2)
        {
            plainteks +=
                matriks[(baris1 + 4) % 5][kolom1];

            plainteks +=
                matriks[(baris2 + 4) % 5][kolom2];
        }

        // jika membentuk persegi panjang
        else
        {
            plainteks +=
                matriks[baris1][kolom2];

            plainteks +=
                matriks[baris2][kolom1];
        }
    }

    return plainteks;
}