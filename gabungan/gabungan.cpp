#include "gabungan.h"

using namespace std;

void tambahRiwayat(
    vector<Riwayat> &riwayat,
    Riwayat data)
{
    riwayat.push_back(data);
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