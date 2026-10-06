#ifndef GABUNGAN_H
#define GABUNGAN_H

#include <string>
#include <vector>

using namespace std;

struct Riwayat
{
    int algoritma;

    // dipakai jika lapisan menggunakan playfair
    vector<int> posisiFiller;
};

void tambahRiwayat(
    vector<Riwayat> &riwayat,
    Riwayat data);

string namaAlgoritma(int algoritma);

#endif