#include <iostream>
#include "transposisi_kolom.h"

using namespace std;

bool validasiTeksTransposisi(string teks){
    if (teks.empty()) return false;

    bool adaHuruf = false;

    for (char karakter : teks){
        if (karakter >= 'A' && karakter <= 'Z') adaHuruf = true;
        else if (karakter != ' ') return false;
    }

    return adaHuruf;
}

string hapusSpasiTransposisi(string teks){
    string hasil = "";

    for (char karakter : teks){
        if (karakter != ' ') hasil += karakter;
    }

    return hasil;
}

bool validasiKunciTransposisi(string teks, int kunci){
    if (kunci <= 0) return false;

    // batas jumlah kolom dihitung setelah spasi dibuang
    teks = hapusSpasiTransposisi(teks);
    int panjang = teks.length();

    if (panjang == 0) return false;
    if (kunci > panjang) return false;

    return true;
}

bool validasiKelompokTransposisi(int jumlahHuruf){
    return jumlahHuruf >= 0;
}

string kelompokkanTransposisi(string teks, int jumlahHuruf){
    if (jumlahHuruf == 0) return teks;
    if (jumlahHuruf < 0) return "";

    // spasi kelompok hanya dipakai saat menampilkan ciphertext
    teks = hapusSpasiTransposisi(teks);

    string hasil = "";
    int panjang = teks.length();

    for (int i = 0; i < panjang; i++){
        hasil += teks[i];

        if ((i + 1) % jumlahHuruf == 0 && i != panjang - 1) hasil += ' ';
    }

    return hasil;
}

void tampilkanMatriksTransposisi(string teks, int kunci){
    if (!validasiTeksTransposisi(teks)) return;
    if (!validasiKunciTransposisi(teks, kunci)) return;

    teks = hapusSpasiTransposisi(teks);

    int panjang = teks.length();
    // pembulatan ke atas menyediakan baris terakhir yang belum penuh
    int jumlahBaris = (panjang + kunci - 1) / kunci;

    cout << "Teks tanpa spasi: " << teks << endl;
    cout << "Matriks Transposisi:" << endl;

    for (int kolom = 0; kolom < kunci; kolom++) cout << kolom + 1 << " ";
    cout << endl;

    for (int baris = 0; baris < jumlahBaris; baris++){
        for (int kolom = 0; kolom < kunci; kolom++){
            int posisi = baris * kunci + kolom;

            if (posisi < panjang) cout << teks[posisi] << " ";
            // bagian kosong hanya ditandai saat matriks ditampilkan
            else cout << "- ";
        }

        cout << endl;
    }
}

string enkripsiTransposisi(string plainteks, int kunci){
    if (!validasiTeksTransposisi(plainteks)) return "";
    if (!validasiKunciTransposisi(plainteks, kunci)) return "";

    plainteks = hapusSpasiTransposisi(plainteks);

    string cipherteks = "";
    int panjang = plainteks.length();
    int jumlahBaris = (panjang + kunci - 1) / kunci;

    // membaca matriks dari atas ke bawah per kolom
    for (int kolom = 0; kolom < kunci; kolom++){
        for (int baris = 0; baris < jumlahBaris; baris++){
            int posisi = baris * kunci + kolom;

            if (posisi < panjang) cipherteks += plainteks[posisi];
        }
    }

    return cipherteks;
}

string dekripsiTransposisi(string cipherteks, int kunci){
    if (!validasiTeksTransposisi(cipherteks)) return "";
    if (!validasiKunciTransposisi(cipherteks, kunci)) return "";

    cipherteks = hapusSpasiTransposisi(cipherteks);

    string plainteks = "";
    int panjang = cipherteks.length();
    // sisa huruf dibagi ke kolom paling awal
    int barisPenuh = panjang / kunci;
    int sisa = panjang % kunci;
    int jumlahBaris = barisPenuh;

    if (sisa > 0) jumlahBaris++;

    // membaca kembali ciphertext menurut urutan baris aslinya
    for (int baris = 0; baris < jumlahBaris; baris++){
        for (int kolom = 0; kolom < kunci; kolom++){
            int panjangKolom = barisPenuh;

            if (kolom < sisa) panjangKolom++;

            if (baris < panjangKolom){
                // mencari awal kolom dengan menghitung kolom yang lebih panjang
                int posisiAwal = kolom * barisPenuh;

                if (kolom < sisa) posisiAwal += kolom;
                else posisiAwal += sisa;

                int posisi = posisiAwal + baris;
                plainteks += cipherteks[posisi];
            }
        }
    }

    return plainteks;
}