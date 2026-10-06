#ifndef GABUNGAN_H
#define GABUNGAN_H

#include <string>
#include <vector>

using namespace std;

struct Riwayat
{
    int algoritma;

    // posisi x tambahan pada playfair
    vector<int> posisiFiller;

    // posisi spasi sebelum suatu lapisan dienkripsi
    vector<int> posisiSpasi;
};

void tambahRiwayat(
    vector<Riwayat> &riwayat,
    Riwayat data);

vector<int> cariPosisiSpasi(string teks);

string kembalikanSpasi(
    string teks,
    vector<int> posisiSpasi);

string namaAlgoritma(int algoritma);

#endif