#include <iostream>
#include <string>
#include <vector>

#include "caesar/caesar.h"
#include "playfair/playfair.h"
#include "transposisi_kolom/transposisi_kolom.h"
#include "gabungan/gabungan.h"

using namespace std;

void tampilkanPilihanAlgoritma()
{
    cout << endl;
    cout << "Pilih algoritma:" << endl;
    cout << "1. Caesar Cipher" << endl;
    cout << "2. Playfair Cipher" << endl;
    cout << "3. Transposisi Kolom" << endl;
    cout << "Pilih: ";
}

string prosesEnkripsi(
    string teks,
    int algoritma,
    Riwayat &data)
{
    string hasil = "";
    string tampilan = "";

    int kelompok;

    data.algoritma = algoritma;
    data.posisiFiller.clear();

    // caesar cipher
    if (algoritma == 1)
    {
        int kunci;

        cout << endl;
        cout << "=== Caesar Cipher ===" << endl;

        cout << "Masukkan kunci: ";
        cin >> kunci;

        hasil = enkripsiCaesar(
            teks,
            kunci);

        cout << "Kelompokkan berapa huruf" << endl;
        cout << "(0 = tanpa kelompok): ";
        cin >> kelompok;

        tampilan = kelompokkanCaesar(
            hasil,
            kelompok);
    }

    // playfair cipher
    else if (algoritma == 2)
    {
        string kunci;

        cin.ignore(1000, '\n');

        cout << endl;
        cout << "=== Playfair Cipher ===" << endl;

        cout << "Masukkan kunci: ";
        getline(cin, kunci);

        tampilkanMatriksPlayfair(kunci);

        // menyimpan posisi x yang ditambahkan playfair
        string teksSiap =
            siapkanPlainteksPlayfairData(
                teks,
                data.posisiFiller);

        cout << endl;
        cout << "Teks setelah disiapkan: "
             << teksSiap
             << endl;

        hasil = enkripsiPlayfair(
            teks,
            kunci);

        cout << "Kelompokkan berapa huruf" << endl;
        cout << "(0 = tanpa kelompok): ";
        cin >> kelompok;

        tampilan = kelompokkanPlayfair(
            hasil,
            kelompok);
    }

    // transposisi kolom
    else if (algoritma == 3)
    {
        int kunci;

        cout << endl;
        cout << "=== Transposisi Kolom ===" << endl;

        cout << "Masukkan jumlah kolom: ";
        cin >> kunci;

        if (kunci <= 0)
        {
            cout << "Kunci harus lebih dari 0." << endl;

            return teks;
        }

        tampilkanMatriksTransposisi(
            teks,
            kunci);

        hasil = enkripsiTransposisi(
            teks,
            kunci);

        cout << endl;
        cout << "Kelompokkan berapa huruf" << endl;
        cout << "(0 = tanpa kelompok): ";
        cin >> kelompok;

        tampilan = kelompokkanTransposisi(
            hasil,
            kelompok);
    }

    cout << endl;
    cout << "Cipherteks: "
         << tampilan
         << endl;

    // yang diteruskan bukan hasil pengelompokan
    return hasil;
}

string prosesDekripsi(
    string teks,
    Riwayat data)
{
    string hasil = "";

    int algoritma = data.algoritma;

    // caesar cipher
    if (algoritma == 1)
    {
        int kunci;

        cout << endl;
        cout << "=== Dekripsi Caesar Cipher ==="
             << endl;

        cout << "Masukkan kunci: ";
        cin >> kunci;

        hasil = dekripsiCaesar(
            teks,
            kunci);
    }

    // playfair cipher
    else if (algoritma == 2)
    {
        string kunci;

        cin.ignore(1000, '\n');

        cout << endl;
        cout << "=== Dekripsi Playfair Cipher ==="
             << endl;

        cout << "Masukkan kunci: ";
        getline(cin, kunci);

        // mengecek cipher sebelum diproses
        if (!validasiCipherPlayfair(teks))
        {
            cout << endl;
            cout << "Cipherteks Playfair tidak valid."
                 << endl;

            return teks;
        }

        tampilkanMatriksPlayfair(kunci);

        hasil = dekripsiPlayfair(
            teks,
            kunci);

        cout << endl;
        cout << "Hasil sebelum filler dihapus: "
             << hasil
             << endl;

        // menghapus hanya x yang dibuat oleh playfair
        hasil = hapusFillerPlayfair(
            hasil,
            data.posisiFiller);
    }

    // transposisi kolom
    else if (algoritma == 3)
    {
        int kunci;

        cout << endl;
        cout << "=== Dekripsi Transposisi Kolom ==="
             << endl;

        cout << "Masukkan jumlah kolom: ";
        cin >> kunci;

        if (kunci <= 0)
        {
            cout << "Kunci harus lebih dari 0." << endl;

            return teks;
        }

        hasil = dekripsiTransposisi(
            teks,
            kunci);
    }

    cout << endl;
    cout << "Hasil dekripsi: "
         << hasil
         << endl;

    return hasil;
}

int main()
{
    string teksAktif;

    int proses;

    vector<Riwayat> riwayat;

    cout << "=== Kriptografi Klasik ===" << endl;

    cout << endl;
    cout << "Masukkan teks: ";
    getline(cin, teksAktif);

    cout << endl;
    cout << "Pilih proses:" << endl;
    cout << "1. Enkripsi" << endl;
    cout << "2. Dekripsi" << endl;
    cout << "Pilih: ";
    cin >> proses;

    // enkripsi berlapis
    if (proses == 1)
    {
        bool programBerjalan = true;

        while (programBerjalan)
        {
            int algoritma;

            tampilkanPilihanAlgoritma();
            cin >> algoritma;

            if (algoritma < 1 || algoritma > 3)
            {
                cout << "Pilihan algoritma tidak tersedia."
                     << endl;

                continue;
            }

            Riwayat data;

            teksAktif = prosesEnkripsi(
                teksAktif,
                algoritma,
                data);

            tambahRiwayat(
                riwayat,
                data);

            cout << endl;
            cout << "=== Proses Selanjutnya ==="
                 << endl;

            cout << "1. Enkripsi lagi" << endl;
            cout << "2. Dekripsi" << endl;
            cout << "3. Selesai" << endl;
            cout << "Pilih: ";

            int pilihan;
            cin >> pilihan;

            // enkripsi lapisan berikutnya
            if (pilihan == 1)
            {
                continue;
            }

            // dekripsi semua lapisan
            else if (pilihan == 2)
            {
                cout << endl;
                cout << "=== Dekripsi Berlapis ==="
                     << endl;

                for (
                    int i = riwayat.size() - 1;
                    i >= 0;
                    i--)
                {
                    cout << endl;

                    cout << "Lapisan "
                         << i + 1
                         << ": "
                         << namaAlgoritma(
                                riwayat[i].algoritma)
                         << endl;

                    teksAktif = prosesDekripsi(
                        teksAktif,
                        riwayat[i]);
                }

                cout << endl;
                cout << "=== Hasil Akhir ==="
                     << endl;

                cout << "Plainteks: "
                     << teksAktif
                     << endl;

                programBerjalan = false;
            }

            // selesai tanpa dekripsi
            else if (pilihan == 3)
            {
                cout << endl;

                cout << "Cipherteks akhir: "
                     << teksAktif
                     << endl;

                programBerjalan = false;
            }

            else
            {
                cout << "Pilihan tidak tersedia." << endl;
            }
        }
    }

    // dekripsi satu algoritma
    else if (proses == 2)
    {
        int algoritma;

        tampilkanPilihanAlgoritma();
        cin >> algoritma;

        if (algoritma < 1 || algoritma > 3)
        {
            cout << "Pilihan algoritma tidak tersedia." << endl;

            return 0;
        }

        Riwayat data;

        data.algoritma = algoritma;

        teksAktif = prosesDekripsi(
            teksAktif,
            data);

        cout << endl;
        cout << "Plainteks: " << teksAktif << endl;
    }

    else
    {
        cout << "Pilihan proses tidak tersedia."
             << endl;
    }

    return 0;
}