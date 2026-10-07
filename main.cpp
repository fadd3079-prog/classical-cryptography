#include <iostream>
#include <string>
#include <vector>

#include "caesar/caesar.h"
#include "playfair/playfair.h"
#include "transposisi_kolom/transposisi_kolom.h"
#include "gabungan/gabungan.h"

using namespace std;

int inputAngka(string pesan){
    int nilai;

    while (true){
        cout << pesan;

        if (cin >> nilai){
            cin.ignore(10000, '\n');
            return nilai;
        }

        cout << "Input harus berupa angka." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

int pilihProses(){
    while (true){
        cout << endl;
        cout << "1. Enkripsi" << endl;
        cout << "2. Dekripsi" << endl;

        int pilihan = inputAngka("Pilih proses: ");
        if (pilihan == 1 || pilihan == 2) return pilihan;

        cout << "Pilihan tidak tersedia." << endl;
    }
}

int pilihAlgoritma(){
    while (true){
        cout << endl;
        cout << "1. Caesar Cipher" << endl;
        cout << "2. Playfair Cipher" << endl;
        cout << "3. Transposisi Kolom" << endl;

        int pilihan = inputAngka("Pilih algoritma: ");
        if (pilihan >= 1 && pilihan <= 3) return pilihan;

        cout << "Pilihan tidak tersedia." << endl;
    }
}

int pilihKelompok(){
    while (true){
        int kelompok = inputAngka("Kelompokkan berapa huruf (0 = tanpa kelompok): ");

        if (kelompok >= 0) return kelompok;
        cout << "Jumlah kelompok tidak boleh negatif." << endl;
    }
}

int pilihLanjutan(){
    while (true){
        cout << endl;
        cout << "=== Proses Selanjutnya ===" << endl;
        cout << "1. Enkripsi lagi" << endl;
        cout << "2. Dekripsi semua" << endl;
        cout << "3. Selesai" << endl;

        int pilihan = inputAngka("Pilih: ");
        if (pilihan >= 1 && pilihan <= 3) return pilihan;

        cout << "Pilihan tidak tersedia." << endl;
    }
}

bool prosesEnkripsi(string teks, int algoritma, Riwayat &data, string &hasil){
    data.algoritma = algoritma;
    data.posisiSpasi = cariPosisiSpasi(teks);
    data.posisiFiller.clear();
    data.posisiJ.clear();

    int kelompok;

    if (algoritma == 1){
        int kunci = inputAngka("Masukkan kunci Caesar: ");

        hasil = enkripsiCaesar(teks, kunci);
        if (hasil.empty()) return false;

        kelompok = pilihKelompok();
        cout << "Cipherteks: " << kelompokkanCaesar(hasil, kelompok) << endl;
    }

    else if (algoritma == 2){
        string kunci;

        cout << "Masukkan kunci Playfair: ";
        getline(cin, kunci);

        if (!validasiKunciPlayfair(kunci)){
            cout << "Kunci Playfair tidak valid." << endl;
            return false;
        }

        tampilkanMatriksPlayfair(kunci);

        string teksSiap = siapkanPlainteksPlayfair(teks);
        cout << "Teks setelah disiapkan: " << teksSiap << endl;

        hasil = enkripsiPlayfairData(teks, kunci, data.posisiFiller, data.posisiJ);
        if (hasil.empty()) return false;

        kelompok = pilihKelompok();
        cout << "Cipherteks: " << kelompokkanPlayfair(hasil, kelompok) << endl;
    }

    else if (algoritma == 3){
        int kunci = inputAngka("Masukkan jumlah kolom: ");

        if (!validasiKunciTransposisi(teks, kunci)){
            cout << "Kunci Transposisi tidak valid." << endl;
            return false;
        }

        tampilkanMatriksTransposisi(teks, kunci);

        hasil = enkripsiTransposisi(teks, kunci);
        if (hasil.empty()) return false;

        kelompok = pilihKelompok();
        cout << "Cipherteks: " << kelompokkanTransposisi(hasil, kelompok) << endl;
    }

    return true;
}

bool prosesDekripsi(string teks, Riwayat data, string &hasil){
    int algoritma = data.algoritma;

    if (algoritma == 1){
        int kunci = inputAngka("Masukkan kunci Caesar: ");

        hasil = dekripsiCaesar(teks, kunci);
        if (hasil.empty()) return false;
    }

    else if (algoritma == 2){
        string kunci;

        if (!validasiCipherPlayfair(teks)){
            cout << "Cipherteks Playfair tidak valid atau jumlah huruf ganjil." << endl;
            return false;
        }

        cout << "Masukkan kunci Playfair: ";
        getline(cin, kunci);

        if (!validasiKunciPlayfair(kunci)){
            cout << "Kunci Playfair tidak valid." << endl;
            return false;
        }

        tampilkanMatriksPlayfair(kunci);

        hasil = dekripsiPlayfair(teks, kunci);
        if (hasil.empty()) return false;

        // menghapus filler yang memang ditambahkan saat enkripsi
        hasil = hapusFillerPlayfair(hasil, data.posisiFiller);

        // mengembalikan i yang sebelumnya berasal dari j
        hasil = kembalikanJPlayfair(hasil, data.posisiJ);
    }

    else if (algoritma == 3){
        int kunci = inputAngka("Masukkan jumlah kolom: ");

        if (!validasiKunciTransposisi(teks, kunci)){
            cout << "Kunci Transposisi tidak valid." << endl;
            return false;
        }

        hasil = dekripsiTransposisi(teks, kunci);
        if (hasil.empty()) return false;
    }

    // mengembalikan spasi yang hilang pada lapisan ini
    hasil = kembalikanSpasi(hasil, data.posisiSpasi);

    cout << "Hasil dekripsi: " << hasil << endl;
    return true;
}

void dekripsiBerlapis(string &teksAktif, vector<Riwayat> riwayat){
    int jumlahLapisan = riwayat.size();

    cout << endl;
    cout << "=== Dekripsi Berlapis ===" << endl;

    for (int i = jumlahLapisan - 1; i >= 0; i--){
        cout << endl;
        cout << "Lapisan " << i + 1 << ": " << namaAlgoritma(riwayat[i].algoritma) << endl;

        bool berhasil = false;

        while (!berhasil){
            string hasil;
            berhasil = prosesDekripsi(teksAktif, riwayat[i], hasil);

            if (berhasil) teksAktif = hasil;
            else cout << "Dekripsi gagal, coba masukkan data kembali." << endl;
        }
    }
}

int main(){
    string teksAktif;
    string plainteksAwal;
    vector<Riwayat> riwayat;

    cout << "=== Kriptografi Klasik ===" << endl;
    cout << "Masukkan teks: ";
    getline(cin, teksAktif);

    int proses = pilihProses();

    if (proses == 1){
        if (!validasiPlainteksAwal(teksAktif)){
            cout << "Plainteks tidak valid." << endl;
            cout << "Gunakan huruf kapital A-Z dan spasi saja." << endl;
            return 0;
        }

        plainteksAwal = teksAktif;

        while (true){
            int algoritma = pilihAlgoritma();
            Riwayat data;
            string hasil;

            cout << endl;
            cout << "=== " << namaAlgoritma(algoritma) << " ===" << endl;

            bool berhasil = prosesEnkripsi(teksAktif, algoritma, data, hasil);

            if (!berhasil){
                cout << "Enkripsi gagal. Riwayat tidak ditambahkan." << endl;
                continue;
            }

            teksAktif = hasil;
            tambahRiwayat(riwayat, data);

            int pilihan = pilihLanjutan();

            if (pilihan == 1) continue;

            if (pilihan == 2){
                dekripsiBerlapis(teksAktif, riwayat);

                cout << endl;
                cout << "=== Hasil Akhir ===" << endl;
                cout << "Plainteks awal  : " << plainteksAwal << endl;
                cout << "Hasil dekripsi : " << teksAktif << endl;

                if (validasiHasilAkhir(plainteksAwal, teksAktif)){
                    cout << "Validasi       : BERHASIL" << endl;
                    cout << "Hasil dekripsi identik dengan plainteks awal." << endl;
                }
                else{
                    cout << "Validasi       : GAGAL" << endl;
                    cout << "Hasil dekripsi tidak identik dengan plainteks awal." << endl;
                }

                break;
            }

            if (pilihan == 3){
                cout << endl;
                cout << "Cipherteks akhir: " << teksAktif << endl;
                break;
            }
        }
    }

    else{
        int algoritma = pilihAlgoritma();
        Riwayat data;
        string hasil;

        data.algoritma = algoritma;

        cout << endl;
        cout << "=== Dekripsi " << namaAlgoritma(algoritma) << " ===" << endl;

        if (!prosesDekripsi(teksAktif, data, hasil)){
            cout << "Dekripsi gagal." << endl;
            return 0;
        }

        cout << endl;
        cout << "Plainteks hasil dekripsi: " << hasil << endl;
        cout << "Catatan: pemulihan spasi, J, dan filler penuh membutuhkan riwayat dari proses enkripsi." << endl;
    }

    return 0;
}