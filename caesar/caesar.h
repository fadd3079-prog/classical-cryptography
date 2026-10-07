#ifndef CAESAR_H
#define CAESAR_H

#include <string>

using namespace std;

bool validasiTeksCaesar(string teks);
bool validasiKelompokCaesar(int jumlahHuruf);

int normalisasiKunciCaesar(int kunci);

string hapusSpasiCaesar(string teks);
string kelompokkanCaesar(string teks, int jumlahHuruf);

string enkripsiCaesar(string plainteks, int kunci);
string dekripsiCaesar(string cipherteks, int kunci);

#endif