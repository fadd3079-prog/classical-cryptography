#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>

#include <string>
#include <vector>
#include <sstream>

#include "../caesar/caesar.h"
#include "../playfair/playfair.h"
#include "../transposisi_kolom/transposisi_kolom.h"
#include "../gabungan/gabungan.h"

using namespace std;

Fl_Multiline_Input *inputTeks;
Fl_Choice *pilihAlgoritma;
Fl_Input *inputKunci;
Fl_Int_Input *inputKelompok;
Fl_Multiline_Output *outputHasil;
Fl_Multiline_Output *outputRiwayat;
Fl_Box *status;

string plainteksAwal = "";
string teksAktif = "";
vector<Riwayat> riwayat;

bool ubahKeAngka(string teks, int &nilai){
    stringstream baca(teks);
    char sisa;

    if (!(baca >> nilai)) return false;
    // menolak input yang masih memiliki karakter setelah angka
    if (baca >> sisa) return false;

    return true;
}

string buatRiwayat(){
    if (riwayat.empty()) return "Belum ada lapisan.";

    string hasil = "";

    for (int i = 0; i < riwayat.size(); i++){
        hasil += to_string(i + 1) + ". ";
        hasil += namaAlgoritma(riwayat[i].algoritma);
        hasil += "\n";
    }

    return hasil;
}

void perbaruiRiwayat(){
    string teks = buatRiwayat();
    outputRiwayat->value(teks.c_str());
}

void tampilkanHasil(string hasil){
    outputHasil->value(hasil.c_str());
    inputTeks->value(teksAktif.c_str());
}

void enkripsiKlik(Fl_Widget *, void *){
    string teks = inputTeks->value();
    string kunci = inputKunci->value();
    int algoritma = pilihAlgoritma->value() + 1;
    int kelompok = 0;

    if (!ubahKeAngka(inputKelompok->value(), kelompok) || kelompok < 0){
        status->label("Kelompok harus berupa angka 0 atau lebih.");
        return;
    }

    // input menjadi plaintext awal hanya pada lapisan pertama
    if (riwayat.empty()){
        if (!validasiPlainteksAwal(teks)){
            status->label("Plainteks hanya boleh A-Z dan spasi.");
            return;
        }

        plainteksAwal = teks;
        teksAktif = teks;
    }
    else{
        teks = teksAktif;
    }

    // metadata lapisan disiapkan sebelum algoritma dijalankan
    Riwayat data;
    data.algoritma = algoritma;
    data.posisiSpasi = cariPosisiSpasi(teks);
    data.posisiFiller.clear();
    data.posisiJ.clear();

    string hasil = "";
    string tampilan = "";

    if (algoritma == 1){
        int kunciAngka;

        if (!ubahKeAngka(kunci, kunciAngka)){
            status->label("Kunci Caesar harus berupa angka.");
            return;
        }

        hasil = enkripsiCaesar(teks, kunciAngka);
        if (hasil.empty()){
            status->label("Enkripsi Caesar gagal.");
            return;
        }

        tampilan = kelompokkanCaesar(hasil, kelompok);
    }

    else if (algoritma == 2){
        if (!validasiKunciPlayfair(kunci)){
            status->label("Kunci Playfair tidak valid.");
            return;
        }

        hasil = enkripsiPlayfairData(teks, kunci, data.posisiFiller, data.posisiJ);

        if (hasil.empty()){
            status->label("Enkripsi Playfair gagal.");
            return;
        }

        tampilan = kelompokkanPlayfair(hasil, kelompok);
    }

    else if (algoritma == 3){
        int jumlahKolom;

        if (!ubahKeAngka(kunci, jumlahKolom)){
            status->label("Kunci Transposisi harus berupa angka.");
            return;
        }

        if (!validasiKunciTransposisi(teks, jumlahKolom)){
            status->label("Jumlah kolom tidak valid.");
            return;
        }

        hasil = enkripsiTransposisi(teks, jumlahKolom);

        if (hasil.empty()){
            status->label("Enkripsi Transposisi gagal.");
            return;
        }

        tampilan = kelompokkanTransposisi(hasil, kelompok);
    }

    // hasil dan metadata disimpan setelah enkripsi berhasil
    teksAktif = hasil;
    tambahRiwayat(riwayat, data);

    tampilkanHasil(tampilan);
    perbaruiRiwayat();

    string pesan = "Enkripsi berhasil. Lapisan: " + to_string(riwayat.size());
    status->copy_label(pesan.c_str());

    inputKunci->value("");
}

void dekripsiKlik(Fl_Widget *, void *){
    if (riwayat.empty()){
        status->label("Tidak ada lapisan yang dapat didekripsi.");
        return;
    }

    string kunci = inputKunci->value();
    // lapisan terakhir dibuka lebih dulu seperti stack
    Riwayat data = riwayat.back();
    string hasil = "";

    int algoritma = data.algoritma;

    pilihAlgoritma->value(algoritma - 1);

    if (algoritma == 1){
        int kunciAngka;

        if (!ubahKeAngka(kunci, kunciAngka)){
            status->label("Masukkan kunci Caesar yang benar.");
            return;
        }

        hasil = dekripsiCaesar(teksAktif, kunciAngka);

        if (hasil.empty()){
            status->label("Dekripsi Caesar gagal.");
            return;
        }
    }

    else if (algoritma == 2){
        if (!validasiCipherPlayfair(teksAktif)){
            status->label("Cipher Playfair tidak valid.");
            return;
        }

        if (!validasiKunciPlayfair(kunci)){
            status->label("Masukkan kunci Playfair yang benar.");
            return;
        }

        hasil = dekripsiPlayfair(teksAktif, kunci);

        if (hasil.empty()){
            status->label("Dekripsi Playfair gagal.");
            return;
        }

        // pemulihan memakai metadata dari lapisan playfair ini
        hasil = hapusFillerPlayfair(hasil, data.posisiFiller);
        hasil = kembalikanJPlayfair(hasil, data.posisiJ);
    }

    else if (algoritma == 3){
        int jumlahKolom;

        if (!ubahKeAngka(kunci, jumlahKolom)){
            status->label("Masukkan jumlah kolom yang benar.");
            return;
        }

        if (!validasiKunciTransposisi(teksAktif, jumlahKolom)){
            status->label("Kunci Transposisi tidak valid.");
            return;
        }

        hasil = dekripsiTransposisi(teksAktif, jumlahKolom);

        if (hasil.empty()){
            status->label("Dekripsi Transposisi gagal.");
            return;
        }
    }

    // spasi lapisan ini dipulihkan sebelum teks aktif diperbarui
    hasil = kembalikanSpasi(hasil, data.posisiSpasi);

    teksAktif = hasil;
    // metadata lapisan dihapus setelah dekripsi berhasil
    riwayat.pop_back();

    tampilkanHasil(hasil);
    perbaruiRiwayat();

    inputKunci->value("");

    // validasi akhir dilakukan setelah seluruh lapisan dibuka
    if (riwayat.empty()){
        if (validasiHasilAkhir(plainteksAwal, teksAktif)){
            status->label("Validasi BERHASIL - identik dengan plainteks awal.");
        }
        else{
            status->label("Validasi GAGAL - hasil tidak identik.");
        }
    }
    else{
        string pesan = "Dekripsi berhasil. Sisa lapisan: " + to_string(riwayat.size());
        status->copy_label(pesan.c_str());
    }
}

void resetKlik(Fl_Widget *, void *){
    plainteksAwal = "";
    teksAktif = "";
    riwayat.clear();

    inputTeks->value("");
    inputKunci->value("");
    inputKelompok->value("0");
    outputHasil->value("");
    outputRiwayat->value("Belum ada lapisan.");

    pilihAlgoritma->value(0);
    status->label("");
}

int main(){
    Fl_Window *window = new Fl_Window(650, 650, "Kriptografi Klasik");

    Fl_Box *judul = new Fl_Box(20, 15, 610, 35, "Kriptografi Klasik");
    judul->labelsize(20);

    inputTeks = new Fl_Multiline_Input(130, 70, 480, 90, "Teks Aktif:");

    pilihAlgoritma = new Fl_Choice(130, 180, 220, 30, "Algoritma:");
    pilihAlgoritma->add("Caesar Cipher");
    pilihAlgoritma->add("Playfair Cipher");
    pilihAlgoritma->add("Transposisi Kolom");
    pilihAlgoritma->value(0);

    inputKunci = new Fl_Input(130, 225, 220, 30, "Kunci:");

    inputKelompok = new Fl_Int_Input(130, 270, 100, 30, "Kelompok:");
    inputKelompok->value("0");

    Fl_Button *tombolEnkripsi = new Fl_Button(130, 320, 140, 35, "Enkripsi Lapisan");
    Fl_Button *tombolDekripsi = new Fl_Button(280, 320, 140, 35, "Dekripsi Lapisan");
    Fl_Button *tombolReset = new Fl_Button(430, 320, 100, 35, "Reset");

    tombolEnkripsi->callback(enkripsiKlik);
    tombolDekripsi->callback(dekripsiKlik);
    tombolReset->callback(resetKlik);

    outputHasil = new Fl_Multiline_Output(130, 380, 480, 80, "Hasil:");

    outputRiwayat = new Fl_Multiline_Output(130, 480, 480, 90, "Riwayat:");
    outputRiwayat->value("Belum ada lapisan.");

    status = new Fl_Box(80, 590, 540, 35, "");
    status->labelsize(13);

    window->end();
    window->show();

    return Fl::run();
}