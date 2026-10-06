#include <iostream>
#include "transposisi_kolom.h"

using namespace std;

string hapusSpasiTransposisi(string teks)
{
    string hasil = "";

    for (char karakter : teks)
    {
        if (karakter != ' ')
        {
            hasil += karakter;
        }
    }

    return hasil;
}

string kelompokkanTransposisi(string teks, int jumlahHuruf)
{
    string hasil = "";

    if (jumlahHuruf <= 0)
    {
        return teks;
    }

    int hitung = 0;

    for (int i = 0; i < teks.length(); i++)
    {
        hasil += teks[i];
        hitung++;

        // memberi spasi setelah mencapai jumlah kelompok
        if (hitung == jumlahHuruf && i != teks.length() - 1)
        {
            hasil += ' ';
            hitung = 0;
        }
    }

    return hasil;
}

void tampilkanMatriksTransposisi(string teks, int kunci)
{
    if (kunci <= 0)
    {
        return;
    }

    teks = hapusSpasiTransposisi(teks);

    int panjang = teks.length();
    int jumlahBaris = (panjang + kunci - 1) / kunci;

    cout << endl;
    cout << "Teks tanpa spasi: " << teks << endl;

    cout << endl;
    cout << "Matriks Transposisi:" << endl;

    // menampilkan nomor kolom
    for (int kolom = 0; kolom < kunci; kolom++)
    {
        cout << kolom + 1 << " ";
    }

    cout << endl;

    // menampilkan isi matriks
    for (int baris = 0; baris < jumlahBaris; baris++)
    {
        for (int kolom = 0; kolom < kunci; kolom++)
        {
            int posisi = baris * kunci + kolom;

            if (posisi < panjang)
            {
                cout << teks[posisi] << " ";
            }
            else
            {
                cout << "- ";
            }
        }

        cout << endl;
    }
}

string enkripsiTransposisi(string plainteks, int kunci)
{
    string cipherteks = "";

    if (kunci <= 0)
    {
        return "";
    }

    // spasi tidak ikut dalam proses transposisi
    plainteks = hapusSpasiTransposisi(plainteks);

    int panjang = plainteks.length();
    int jumlahBaris = (panjang + kunci - 1) / kunci;

    // membaca matriks dari atas ke bawah per kolom
    for (int kolom = 0; kolom < kunci; kolom++)
    {
        for (int baris = 0; baris < jumlahBaris; baris++)
        {
            int posisi = baris * kunci + kolom;

            if (posisi < panjang)
            {
                cipherteks += plainteks[posisi];
            }
        }
    }

    return cipherteks;
}

string dekripsiTransposisi(string cipherteks, int kunci)
{
    string plainteks = "";

    if (kunci <= 0)
    {
        return "";
    }

    // menghapus spasi dari hasil pengelompokan
    cipherteks = hapusSpasiTransposisi(cipherteks);

    int panjang = cipherteks.length();

    int barisPenuh = panjang / kunci;
    int sisa = panjang % kunci;

    int jumlahBaris = barisPenuh;

    if (sisa > 0)
    {
        jumlahBaris++;
    }

    // membaca kembali matriks sesuai posisi awal
    for (int baris = 0; baris < jumlahBaris; baris++)
    {
        for (int kolom = 0; kolom < kunci; kolom++)
        {
            int panjangKolom = barisPenuh;

            if (kolom < sisa)
            {
                panjangKolom++;
            }

            if (baris < panjangKolom)
            {
                int posisiAwal = kolom * barisPenuh;

                if (kolom < sisa)
                {
                    posisiAwal += kolom;
                }
                else
                {
                    posisiAwal += sisa;
                }

                int posisi = posisiAwal + baris;

                plainteks += cipherteks[posisi];
            }
        }
    }

    return plainteks;
}