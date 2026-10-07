#include <iostream>
#include "playfair.h"

using namespace std;

bool validasiTeksPlayfair(string teks){
    if (teks.empty()) return false;

    bool adaHuruf = false;
    for (char karakter : teks){
        if (karakter >= 'A' && karakter <= 'Z') adaHuruf = true;
        else if (karakter != ' ') return false;
    }

    return adaHuruf;
}

bool validasiKunciPlayfair(string kunci){
    if (kunci.empty()) return false;

    // kunci harus menyisakan huruf setelah j dibuang
    bool adaHurufSelainJ = false;

    for (char karakter : kunci){
        if (karakter >= 'a' && karakter <= 'z') karakter -= 32;

        if (karakter >= 'A' && karakter <= 'Z'){
            if (karakter != 'J') adaHurufSelainJ = true;
        }
        else if (karakter != ' ') return false;
    }

    return adaHurufSelainJ;
}

bool validasiCipherPlayfair(string cipherteks){
    if (cipherteks.empty()) return false;

    int jumlahHuruf = 0;

    for (char karakter : cipherteks){
        if (karakter == ' ') continue;
        if (karakter < 'A' || karakter > 'Z' || karakter == 'J') return false;
        jumlahHuruf++;
    }

    // ciphertext diproses dalam pasangan huruf
    return jumlahHuruf > 0 && jumlahHuruf % 2 == 0;
}

string hapusSpasiPlayfair(string teks){
    string hasil = "";
    for (char karakter : teks){
        if (karakter != ' ') hasil += karakter;
    }
    return hasil;
}

string bersihkanKunciPlayfair(string kunci){
    string hasil = "";

    for (char huruf : kunci){
        if (huruf >= 'a' && huruf <= 'z') huruf -= 32;

        // j pada kunci dibuang, bukan diubah menjadi i
        if (huruf >= 'A' && huruf <= 'Z' && huruf != 'J') hasil += huruf;
    }

    return hasil;
}

bool sudahAdaPlayfair(string teks, char huruf){
    for (char isi : teks){
        if (isi == huruf) return true;
    }
    return false;
}

bool buatMatriksPlayfair(string kunci, char matriks[5][5]){
    if (!validasiKunciPlayfair(kunci)) return false;

    string isiMatriks = "";
    string alfabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    kunci = bersihkanKunciPlayfair(kunci);

    // huruf unik dari kunci menempati matriks lebih dulu
    for (char huruf : kunci){
        if (!sudahAdaPlayfair(isiMatriks, huruf)) isiMatriks += huruf;
    }

    // melengkapi matriks dengan huruf yang belum dipakai
    for (char huruf : alfabet){
        if (!sudahAdaPlayfair(isiMatriks, huruf)) isiMatriks += huruf;
    }

    int index = 0;
    for (int baris = 0; baris < 5; baris++){
        for (int kolom = 0; kolom < 5; kolom++) matriks[baris][kolom] = isiMatriks[index++];
    }

    return true;
}

bool tampilkanMatriksPlayfair(string kunci){
    char matriks[5][5];
    if (!buatMatriksPlayfair(kunci, matriks)) return false;

    cout << "Matriks Playfair:" << endl;
    for (int baris = 0; baris < 5; baris++){
        for (int kolom = 0; kolom < 5; kolom++) cout << matriks[baris][kolom] << " ";
        cout << endl;
    }

    return true;
}

string bersihkanPlainteksPlayfair(string teks, vector<int> &posisiJ){
    string hasil = "";
    posisiJ.clear();

    for (char huruf : teks){
        if (huruf == ' ') continue;

        // posisi j dicatat sebelum diganti menjadi i
        if (huruf == 'J'){
            posisiJ.push_back(hasil.length());
            hasil += 'I';
        }
        else hasil += huruf;
    }

    return hasil;
}

char pilihFillerPlayfair(char huruf){
    // q mencegah terbentuknya pasangan x dengan filler x
    if (huruf == 'X') return 'Q';
    return 'X';
}

string siapkanPlainteksPlayfairData(string plainteks, vector<int> &posisiFiller, vector<int> &posisiJ){
    if (!validasiTeksPlayfair(plainteks)) return "";

    string teks = bersihkanPlainteksPlayfair(plainteks, posisiJ);
    string hasil = "";
    posisiFiller.clear();

    int panjang = teks.length();
    int i = 0;

    // membentuk bigram sambil mencatat filler yang ditambahkan
    while (i < panjang){
        char huruf1 = teks[i];

        // satu huruf tersisa dipasangkan dengan filler
        if (i + 1 >= panjang){
            hasil += huruf1;
            hasil += pilihFillerPlayfair(huruf1);
            posisiFiller.push_back(hasil.length() - 1);
            i++;
        }
        else{
            char huruf2 = teks[i + 1];

            // huruf yang sama dipisah dan huruf kedua diproses lagi
            if (huruf1 == huruf2){
                hasil += huruf1;
                hasil += pilihFillerPlayfair(huruf1);
                posisiFiller.push_back(hasil.length() - 1);
                i++;
            }
            else{
                hasil += huruf1;
                hasil += huruf2;
                i += 2;
            }
        }
    }

    return hasil;
}

string siapkanPlainteksPlayfair(string plainteks){
    vector<int> posisiFiller;
    vector<int> posisiJ;
    return siapkanPlainteksPlayfairData(plainteks, posisiFiller, posisiJ);
}

bool adaPosisiPlayfair(vector<int> posisi, int nilai){
    for (int isi : posisi){
        if (isi == nilai) return true;
    }
    return false;
}

string hapusFillerPlayfair(string teks, vector<int> posisiFiller){
    string hasil = "";
    int panjang = teks.length();

    // hanya filler yang tercatat saat enkripsi yang dihapus
    for (int i = 0; i < panjang; i++){
        if (!adaPosisiPlayfair(posisiFiller, i)) hasil += teks[i];
    }

    return hasil;
}

string kembalikanJPlayfair(string teks, vector<int> posisiJ){
    int panjang = teks.length();

    // mengembalikan j pada posisi aslinya setelah filler dihapus
    for (int posisi : posisiJ){
        if (posisi >= 0 && posisi < panjang) teks[posisi] = 'J';
    }

    return teks;
}

string kelompokkanPlayfair(string teks, int jumlahHuruf){
    if (jumlahHuruf == 0) return teks;
    if (jumlahHuruf < 0) return "";

    // pengelompokan hanya mengatur tampilan ciphertext
    teks = hapusSpasiPlayfair(teks);

    string hasil = "";
    int panjang = teks.length();

    for (int i = 0; i < panjang; i++){
        hasil += teks[i];
        if ((i + 1) % jumlahHuruf == 0 && i != panjang - 1) hasil += ' ';
    }

    return hasil;
}

bool cariPosisiPlayfair(char matriks[5][5], char huruf, int &baris, int &kolom){
    baris = -1;
    kolom = -1;

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (matriks[i][j] == huruf){
                baris = i;
                kolom = j;
                return true;
            }
        }
    }

    return false;
}

string enkripsiPlayfairData(string plainteks, string kunci, vector<int> &posisiFiller, vector<int> &posisiJ){
    if (!validasiTeksPlayfair(plainteks) || !validasiKunciPlayfair(kunci)) return "";

    char matriks[5][5];
    if (!buatMatriksPlayfair(kunci, matriks)) return "";

    string teks = siapkanPlainteksPlayfairData(plainteks, posisiFiller, posisiJ);
    string cipherteks = "";
    int panjang = teks.length();

    for (int i = 0; i < panjang; i += 2){
        char huruf1 = teks[i];
        char huruf2 = teks[i + 1];

        int baris1, kolom1, baris2, kolom2;
        if (!cariPosisiPlayfair(matriks, huruf1, baris1, kolom1)) return "";
        if (!cariPosisiPlayfair(matriks, huruf2, baris2, kolom2)) return "";

        // pasangan sebaris digeser satu kolom ke kanan
        if (baris1 == baris2){
            cipherteks += matriks[baris1][(kolom1 + 1) % 5];
            cipherteks += matriks[baris2][(kolom2 + 1) % 5];
        }
        // pasangan sekolom digeser satu baris ke bawah
        else if (kolom1 == kolom2){
            cipherteks += matriks[(baris1 + 1) % 5][kolom1];
            cipherteks += matriks[(baris2 + 1) % 5][kolom2];
        }
        // sudut persegi panjang diperoleh dengan menukar kolom
        else{
            cipherteks += matriks[baris1][kolom2];
            cipherteks += matriks[baris2][kolom1];
        }
    }

    return cipherteks;
}

string enkripsiPlayfair(string plainteks, string kunci){
    vector<int> posisiFiller;
    vector<int> posisiJ;
    return enkripsiPlayfairData(plainteks, kunci, posisiFiller, posisiJ);
}

string dekripsiPlayfair(string cipherteks, string kunci){
    if (!validasiCipherPlayfair(cipherteks) || !validasiKunciPlayfair(kunci)) return "";

    char matriks[5][5];
    if (!buatMatriksPlayfair(kunci, matriks)) return "";

    string teks = hapusSpasiPlayfair(cipherteks);
    string plainteks = "";
    int panjang = teks.length();

    for (int i = 0; i < panjang; i += 2){
        char huruf1 = teks[i];
        char huruf2 = teks[i + 1];

        int baris1, kolom1, baris2, kolom2;
        if (!cariPosisiPlayfair(matriks, huruf1, baris1, kolom1)) return "";
        if (!cariPosisiPlayfair(matriks, huruf2, baris2, kolom2)) return "";

        // tambahan 4 setara dengan geser satu kolom ke kiri
        if (baris1 == baris2){
            plainteks += matriks[baris1][(kolom1 + 4) % 5];
            plainteks += matriks[baris2][(kolom2 + 4) % 5];
        }
        // tambahan 4 setara dengan geser satu baris ke atas
        else if (kolom1 == kolom2){
            plainteks += matriks[(baris1 + 4) % 5][kolom1];
            plainteks += matriks[(baris2 + 4) % 5][kolom2];
        }
        // aturan persegi panjang tetap menukar kolom
        else{
            plainteks += matriks[baris1][kolom2];
            plainteks += matriks[baris2][kolom1];
        }
    }

    return plainteks;
}