#ifndef TRANSPOSISI_KOLOM_H
#define TRANSPOSISI_KOLOM_H

#include <string>

using namespace std;

bool validasiTeksTransposisi(string teks);
bool validasiKunciTransposisi(string teks, int kunci);
bool validasiKelompokTransposisi(int jumlahHuruf);

string hapusSpasiTransposisi(string teks);
string kelompokkanTransposisi(string teks, int jumlahHuruf);

void tampilkanMatriksTransposisi(string teks, int kunci);

string enkripsiTransposisi(string plainteks, int kunci);
string dekripsiTransposisi(string cipherteks, int kunci);

#endif