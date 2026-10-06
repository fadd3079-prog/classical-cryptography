#include "caesar.h"

string hapusSpasiCaesar(string teks)
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

string kelompokkanCaesar(string teks, int jumlahHuruf)
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

string enkripsiCaesar(string plainteks, int kunci)
{
    string cipherteks = "";

    // spasi tidak ikut dalam proses enkripsi
    plainteks = hapusSpasiCaesar(plainteks);

    // menyesuaikan kunci ke rentang alfabet
    kunci = kunci % 26;

    if (kunci < 0)
    {
        kunci += 26;
    }

    for (char huruf : plainteks)
    {
        // proses huruf besar
        if (huruf >= 'A' && huruf <= 'Z')
        {
            huruf = 'A' + (huruf - 'A' + kunci) % 26;
        }

        // proses huruf kecil
        else if (huruf >= 'a' && huruf <= 'z')
        {
            huruf = 'a' + (huruf - 'a' + kunci) % 26;
        }

        cipherteks += huruf;
    }

    return cipherteks;
}

string dekripsiCaesar(string cipherteks, int kunci)
{
    string plainteks = "";

    // menghapus spasi dari hasil pengelompokan
    cipherteks = hapusSpasiCaesar(cipherteks);

    // menyesuaikan kunci ke rentang alfabet
    kunci = kunci % 26;

    if (kunci < 0)
    {
        kunci += 26;
    }

    for (char huruf : cipherteks)
    {
        // proses huruf besar
        if (huruf >= 'A' && huruf <= 'Z')
        {
            huruf = 'A' + (huruf - 'A' - kunci + 26) % 26;
        }

        // proses huruf kecil
        else if (huruf >= 'a' && huruf <= 'z')
        {
            huruf = 'a' + (huruf - 'a' - kunci + 26) % 26;
        }

        plainteks += huruf;
    }

    return plainteks;
}