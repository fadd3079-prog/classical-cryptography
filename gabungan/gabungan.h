#ifndef GABUNGAN_H
#define GABUNGAN_H

#include <string>
#include <vector>

using namespace std;

// metadata untuk memulihkan teks pada setiap lapisan enkripsi
struct Riwayat{
    int algoritma;
    vector<int> posisiSpasi;
    vector<int> posisiFiller;
    vector<int> posisiJ;
};

bool validasiPlainteksAwal(string teks);
bool validasiHasilAkhir(string plainteksAwal, string hasilAkhir);

vector<int> cariPosisiSpasi(string teks);
string kembalikanSpasi(string teks, vector<int> posisiSpasi);

void tambahRiwayat(vector<Riwayat> &riwayat, Riwayat data);
string namaAlgoritma(int algoritma);

#endif