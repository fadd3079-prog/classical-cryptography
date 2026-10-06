#include "gabungan.h"

using namespace std;

void tambahRiwayat(
    vector<Riwayat> &riwayat,
    Riwayat data)
{
    riwayat.push_back(data);
}

vector<int> cariPosisiSpasi(string teks)
{
    vector<int> posisiSpasi;

    for (int i = 0; i < teks.length(); i++)
    {
        if (teks[i] == ' ')
        {
            posisiSpasi.push_back(i);
        }
    }

    return posisiSpasi;
}

bool adaPosisiSpasi(
    vector<int> posisiSpasi,
    int posisi)
{
    for (int isi : posisiSpasi)
    {
        if (isi == posisi)
        {
            return true;
        }
    }

    return false;
}

string kembalikanSpasi(
    string teks,
    vector<int> posisiSpasi)
{
    string hasil = "";

    int indexTeks = 0;
    int panjangAsli =
        teks.length() + posisiSpasi.size();

    for (int i = 0; i < panjangAsli; i++)
    {
        if (adaPosisiSpasi(posisiSpasi, i))
        {
            hasil += ' ';
        }
        else
        {
            if (indexTeks < teks.length())
            {
                hasil += teks[indexTeks];
                indexTeks++;
            }
        }
    }

    return hasil;
}

string namaAlgoritma(int algoritma)
{
    if (algoritma == 1)
    {
        return "Caesar Cipher";
    }
    else if (algoritma == 2)
    {
        return "Playfair Cipher";
    }
    else if (algoritma == 3)
    {
        return "Transposisi Kolom";
    }

    return "Tidak diketahui";
}