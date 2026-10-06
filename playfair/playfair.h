#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <string>
#include <vector>

using namespace std;

string bersihkanTeksPlayfair(string teks);

string siapkanPlainteksPlayfair(string plainteks);

string siapkanPlainteksPlayfairData(
    string plainteks,
    vector<int> &posisiFiller);

string hapusFillerPlayfair(
    string teks,
    vector<int> posisiFiller);

string kelompokkanPlayfair(
    string teks,
    int jumlahHuruf);

bool validasiCipherPlayfair(string cipherteks);

void buatMatriksPlayfair(
    string kunci,
    char matriks[5][5]);

void tampilkanMatriksPlayfair(string kunci);

string enkripsiPlayfair(
    string plainteks,
    string kunci);

string dekripsiPlayfair(
    string cipherteks,
    string kunci);

#endif