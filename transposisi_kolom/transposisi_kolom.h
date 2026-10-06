#ifndef TRANSPOSISI_KOLOM_H
#define TRANSPOSISI_KOLOM_H

#include <string>

using namespace std;

string hapusSpasi(string teks);

void tampilkanMatriksTransposisi(string teks, int kunci);

string enkripsiTransposisi(string plainteks, int kunci);
string dekripsiTransposisi(string cipherteks, int kunci);

#endif