#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <string>
#include <vector>

using namespace std;

bool validasiTeksPlayfair(string teks);
bool validasiKunciPlayfair(string kunci);
bool validasiCipherPlayfair(string cipherteks);

string bersihkanKunciPlayfair(string kunci);
string siapkanPlainteksPlayfair(string plainteks);
string siapkanPlainteksPlayfairData(string plainteks, vector<int> &posisiFiller, vector<int> &posisiJ);
string hapusFillerPlayfair(string teks, vector<int> posisiFiller);
string kembalikanJPlayfair(string teks, vector<int> posisiJ);
string kelompokkanPlayfair(string teks, int jumlahHuruf);

bool buatMatriksPlayfair(string kunci, char matriks[5][5]);
bool tampilkanMatriksPlayfair(string kunci);
bool cariPosisiPlayfair(char matriks[5][5], char huruf, int &baris, int &kolom);

string enkripsiPlayfair(string plainteks, string kunci);
string enkripsiPlayfairData(string plainteks, string kunci, vector<int> &posisiFiller, vector<int> &posisiJ);
string dekripsiPlayfair(string cipherteks, string kunci);

#endif