#include "gabungan.h"
using namespace std;

bool validasiPlainteksAwal(string teks) {   // mengecek plainteks awal hanya berisi huruf kapital dan spasi
    if (teks.empty()) return false;
    bool adaHuruf = false;
    for (char karakter : teks) {
        if (karakter >= 'A' && karakter <= 'Z') adaHuruf = true;
        else if (karakter != ' ') return false; }
    return adaHuruf; }

bool validasiHasilAkhir(string plainteksAwal, string hasilAkhir) {  // memastikan hasil akhir sama persis dengan plainteks awal
    // validasi berhasil hanya jika seluruh karakter sama persis
    return plainteksAwal == hasilAkhir; }

vector<int> cariPosisiSpasi(string teks) {  // menyimpan posisi spasi sebelum teks diproses algoritma
    vector<int> posisiSpasi;
    int panjang = teks.length();
    for (int i = 0; i < panjang; i++){      // menyimpan index spasi sebelum teks masuk ke algoritma
        if (teks[i] == ' ') posisiSpasi.push_back(i); }
    return posisiSpasi; }

bool adaPosisiSpasi(vector<int> posisiSpasi, int posisi) {  // mengecek apakah suatu index merupakan posisi spasi
    for (int isi : posisiSpasi){
        if (isi == posisi) return true; }
    return false; }

string kembalikanSpasi(string teks, vector<int> posisiSpasi) {  // mengembalikan spasi ke posisi awal setelah proses dekripsi
    if (posisiSpasi.empty()) return teks;
    string hasil = "";
    int indexTeks = 0;
    int panjangTeks = teks.length();
    int panjangAsli = panjangTeks + posisiSpasi.size();     // panjang awal mencakup spasi yang sebelumnya dihapus
    for (int i = 0; i < panjangAsli; i++){      // menyisipkan spasi pada index tercatat sambil membaca huruf lain
        if (adaPosisiSpasi(posisiSpasi, i)) hasil += ' ';   // menyisipkan kembali spasi berdasarkan posisi yang tersimpan
        else if (indexTeks < panjangTeks) hasil += teks[indexTeks++]; }
    return hasil; }

void tambahRiwayat(vector<Riwayat> &riwayat, Riwayat data) {    // menambahkan data proses ke riwayat
    riwayat.push_back(data); }

string namaAlgoritma(int algoritma) {   // mengubah nomor pilihan algoritma menjadi nama algoritma
    if (algoritma == 1) return "Caesar Cipher";
    if (algoritma == 2) return "Playfair Cipher";
    if (algoritma == 3) return "Transposisi Kolom";
    return "Tidak diketahui"; }