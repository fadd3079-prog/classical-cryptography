#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <string>

using namespace std;

void buatMatriksPlayfair(string kunci, char matriks[5][5]);
void tampilkanMatriksPlayfair(string kunci);

string siapkanPlainteks(string plainteks);

string enkripsiPlayfair(string plainteks, string kunci);
string dekripsiPlayfair(string cipherteks, string kunci);

#endif