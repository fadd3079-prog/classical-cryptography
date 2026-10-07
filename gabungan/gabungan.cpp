#include "gabungan.h"

using namespace std;

bool validasiPlainteksAwal(string teks){
    if (teks.empty()) return false;

    bool adaHuruf = false;

    for (char karakter : teks){
        if (karakter >= 'A' && karakter <= 'Z') adaHuruf = true;
        else if (karakter != ' ') return false;
    }

    return adaHuruf;
}

bool validasiHasilAkhir(string plainteksAwal, string hasilAkhir){
    return plainteksAwal == hasilAkhir;
}

vector<int> cariPosisiSpasi(string teks){
    vector<int> posisiSpasi;
    int panjang = teks.length();

    for (int i = 0; i < panjang; i++){
        if (teks[i] == ' ') posisiSpasi.push_back(i);
    }

    return posisiSpasi;
}

bool adaPosisiSpasi(vector<int> posisiSpasi, int posisi){
    for (int isi : posisiSpasi){
        if (isi == posisi) return true;
    }

    return false;
}

string kembalikanSpasi(string teks, vector<int> posisiSpasi){
    if (posisiSpasi.empty()) return teks;

    string hasil = "";
    int indexTeks = 0;
    int panjangTeks = teks.length();
    int panjangAsli = panjangTeks + posisiSpasi.size();

    for (int i = 0; i < panjangAsli; i++){
        if (adaPosisiSpasi(posisiSpasi, i)) hasil += ' ';
        else if (indexTeks < panjangTeks) hasil += teks[indexTeks++];
    }

    return hasil;
}

void tambahRiwayat(vector<Riwayat> &riwayat, Riwayat data){
    riwayat.push_back(data);
}

string namaAlgoritma(int algoritma){
    if (algoritma == 1) return "Caesar Cipher";
    if (algoritma == 2) return "Playfair Cipher";
    if (algoritma == 3) return "Transposisi Kolom";
    return "Tidak diketahui";
}