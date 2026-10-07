#include "caesar.h"

using namespace std;

bool validasiTeksCaesar(string teks)
{
    if (teks.empty())
    {
        return false;
    }

    bool adaHuruf = false;

    for (char karakter : teks)
    {
        if (karakter >= 'A' && karakter <= 'Z')
        {
            adaHuruf = true;
        }
        else if (karakter != ' ')
        {
            return false;
        }
    }

    return adaHuruf;
}

bool validasiKelompokCaesar(int jumlahHuruf)
{
    if (jumlahHuruf < 0)
    {
        return false;
    }

    return true;
}

int normalisasiKunciCaesar(int kunci){
    kunci = kunci % 26;

    if (kunci < 0)
    {
        kunci += 26;
    }

    return kunci;
}

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

    if (jumlahHuruf == 0)
    {
        return teks;
    }

    if (jumlahHuruf < 0)
    {
        return "";
    }

    teks = hapusSpasiCaesar(teks);

    int panjang = teks.length();
    int hitung = 0;

    for (int i = 0; i < panjang; i++)
    {
        hasil += teks[i];
        hitung++;

        if (hitung == jumlahHuruf && i != panjang - 1)
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

    if (!validasiTeksCaesar(plainteks))
    {
        return "";
    }

    plainteks = hapusSpasiCaesar(plainteks);
    kunci = normalisasiKunciCaesar(kunci);

    int panjang = plainteks.length();

    for (int i = 0; i < panjang; i++)
    {
        char huruf = plainteks[i];

        // mengubah huruf menjadi nilai 0 sampai 25
        int nilai = huruf - 'A';

        // rumus enkripsi caesar
        nilai = (nilai + kunci) % 26;

        cipherteks += char('A' + nilai);
    }

    return cipherteks;
}

string dekripsiCaesar(string cipherteks, int kunci)
{
    string plainteks = "";

    if (!validasiTeksCaesar(cipherteks))
    {
        return "";
    }

    // spasi pengelompokan tidak ikut didekripsi
    cipherteks = hapusSpasiCaesar(cipherteks);
    kunci = normalisasiKunciCaesar(kunci);

    int panjang = cipherteks.length();

    for (int i = 0; i < panjang; i++)
    {
        char huruf = cipherteks[i];

        // mengubah huruf menjadi nilai 0 sampai 25
        int nilai = huruf - 'A';

        // rumus dekripsi caesar
        nilai = (nilai - kunci + 26) % 26;
        plainteks += char('A' + nilai);
    }

    return plainteks;
}