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
#include <cstdlib>

#include "../caesar/caesar.h"
#include "../playfair/playfair.h"
#include "../transposisi_kolom/transposisi_kolom.h"
#include "../gabungan/gabungan.h"

using namespace std;

Fl_Multiline_Input *inputTeks;
Fl_Choice *pilihProses;
Fl_Choice *pilihAlgoritma;
Fl_Input *inputKunci;
Fl_Int_Input *inputKelompok;
Fl_Multiline_Output *outputHasil;
Fl_Box *status;

vector<Riwayat> riwayat;

string teksAktif = "";
string hasilAktif = "";

int ambilAngka(string teks)
{
    return atoi(teks.c_str());
}

void prosesEnkripsi()
{
    string teks = inputTeks->value();
    string kunci = inputKunci->value();

    int algoritma = pilihAlgoritma->value() + 1;
    int kelompok = ambilAngka(inputKelompok->value());

    string hasil = "";
    string tampilan = "";

    // jika sudah ada lapisan, gunakan hasil sebelumnya
    if (!riwayat.empty())
    {
        teks = teksAktif;
    }

    if (teks.empty())
    {
        status->label("Teks belum diisi.");
        return;
    }

    Riwayat data;

    data.algoritma = algoritma;
    data.posisiFiller.clear();

    // menyimpan posisi spasi sebelum diproses
    data.posisiSpasi = cariPosisiSpasi(teks);

    // caesar cipher
    if (algoritma == 1)
    {
        int kunciAngka = ambilAngka(kunci);

        hasil = enkripsiCaesar(
            teks,
            kunciAngka);

        tampilan = kelompokkanCaesar(
            hasil,
            kelompok);
    }

    // playfair cipher
    else if (algoritma == 2)
    {
        if (kunci.empty())
        {
            status->label("Kunci Playfair belum diisi.");
            return;
        }

        // menyimpan posisi filler playfair
        siapkanPlainteksPlayfairData(
            teks,
            data.posisiFiller);

        hasil = enkripsiPlayfair(
            teks,
            kunci);

        tampilan = kelompokkanPlayfair(
            hasil,
            kelompok);
    }

    // transposisi kolom
    else if (algoritma == 3)
    {
        int jumlahKolom = ambilAngka(kunci);

        if (jumlahKolom <= 0)
        {
            status->label(
                "Jumlah kolom harus lebih dari 0.");

            return;
        }

        hasil = enkripsiTransposisi(
            teks,
            jumlahKolom);

        tampilan = kelompokkanTransposisi(
            hasil,
            kelompok);
    }

    // menyimpan riwayat lapisan
    tambahRiwayat(
        riwayat,
        data);

    // hasil tanpa spasi kelompok
    teksAktif = hasil;
    hasilAktif = hasil;

    outputHasil->value(
        tampilan.c_str());

    string pesan =
        "Enkripsi berhasil. Jumlah lapisan: " + to_string(riwayat.size());

    status->copy_label(
        pesan.c_str());
}

void prosesDekripsi()
{
    string teks = inputTeks->value();
    string kunci = inputKunci->value();

    string hasil = "";

    // jika ada history gunakan cipher aktif
    if (!riwayat.empty())
    {
        teks = teksAktif;
    }

    if (teks.empty())
    {
        status->label("Cipherteks belum diisi.");
        return;
    }

    int algoritma;
    Riwayat data;

    // jika ada history, algoritma diambil dari lapisan terakhir
    if (!riwayat.empty())
    {
        data = riwayat[riwayat.size() - 1];

        algoritma = data.algoritma;

        pilihAlgoritma->value(
            algoritma - 1);
    }

    // dekripsi biasa tanpa history
    else
    {
        algoritma =
            pilihAlgoritma->value() + 1;

        data.algoritma = algoritma;
    }

    // caesar cipher
    if (algoritma == 1)
    {
        int kunciAngka =
            ambilAngka(kunci);

        hasil = dekripsiCaesar(
            teks,
            kunciAngka);
    }

    // playfair cipher
    else if (algoritma == 2)
    {
        if (kunci.empty())
        {
            status->label(
                "Kunci Playfair belum diisi.");

            return;
        }

        if (!validasiCipherPlayfair(teks))
        {
            status->label(
                "Cipher Playfair tidak valid.");

            return;
        }

        hasil = dekripsiPlayfair(
            teks,
            kunci);

        // menghapus x filler jika ada history
        if (!riwayat.empty())
        {
            hasil = hapusFillerPlayfair(
                hasil,
                data.posisiFiller);
        }
    }

    // transposisi kolom
    else if (algoritma == 3)
    {
        int jumlahKolom =
            ambilAngka(kunci);

        if (jumlahKolom <= 0)
        {
            status->label(
                "Jumlah kolom harus lebih dari 0.");

            return;
        }

        hasil = dekripsiTransposisi(
            teks,
            jumlahKolom);
    }

    // mengembalikan spasi lapisan
    if (!riwayat.empty())
    {
        hasil = kembalikanSpasi(
            hasil,
            data.posisiSpasi);
    }

    teksAktif = hasil;
    hasilAktif = hasil;

    outputHasil->value(
        hasil.c_str());

    // menghapus lapisan yang sudah didekripsi
    if (!riwayat.empty())
    {
        riwayat.pop_back();
    }

    string pesan =
        "Dekripsi berhasil. Sisa lapisan: " + to_string(riwayat.size());

    status->copy_label(
        pesan.c_str());
}

void prosesKlik(Fl_Widget *, void *)
{
    int proses = pilihProses->value();

    if (proses == 0)
    {
        prosesEnkripsi();
    }
    else
    {
        prosesDekripsi();
    }
}

void hasilKeInput(Fl_Widget *, void *)
{
    if (hasilAktif.empty())
    {
        status->label("Belum ada hasil.");
        return;
    }

    // memakai hasil asli tanpa spasi kelompok
    inputTeks->value(
        hasilAktif.c_str());

    status->label(
        "Hasil dipindahkan ke input.");
}

void resetKlik(Fl_Widget *, void *)
{
    inputTeks->value("");
    inputKunci->value("");
    inputKelompok->value("0");
    outputHasil->value("");

    pilihProses->value(0);
    pilihAlgoritma->value(0);

    riwayat.clear();

    teksAktif = "";
    hasilAktif = "";

    status->label("");
}

int main()
{
    Fl_Window *window =
        new Fl_Window(
            520,
            540,
            "Kriptografi Klasik");

    Fl_Box *judul =
        new Fl_Box(
            20,
            15,
            480,
            35,
            "Kriptografi Klasik");

    judul->labelsize(20);

    inputTeks =
        new Fl_Multiline_Input(
            120,
            70,
            360,
            100,
            "Teks:");

    pilihProses =
        new Fl_Choice(
            120,
            190,
            200,
            30,
            "Proses:");

    pilihProses->add("Enkripsi");
    pilihProses->add("Dekripsi");
    pilihProses->value(0);

    pilihAlgoritma =
        new Fl_Choice(
            120,
            230,
            200,
            30,
            "Algoritma:");

    pilihAlgoritma->add("Caesar Cipher");
    pilihAlgoritma->add("Playfair Cipher");
    pilihAlgoritma->add("Transposisi Kolom");
    pilihAlgoritma->value(0);

    inputKunci =
        new Fl_Input(
            120,
            270,
            200,
            30,
            "Kunci:");

    inputKelompok =
        new Fl_Int_Input(
            120,
            310,
            100,
            30,
            "Kelompok:");

    inputKelompok->value("0");

    Fl_Button *tombolProses =
        new Fl_Button(
            120,
            360,
            110,
            35,
            "Proses");

    tombolProses->callback(
        prosesKlik);

    Fl_Button *tombolLanjut =
        new Fl_Button(
            240,
            360,
            130,
            35,
            "Hasil - Input");

    tombolLanjut->callback(
        hasilKeInput);

    Fl_Button *tombolReset =
        new Fl_Button(
            380,
            360,
            100,
            35,
            "Reset");

    tombolReset->callback(
        resetKlik);

    outputHasil =
        new Fl_Multiline_Output(
            120,
            415,
            360,
            70,
            "Hasil:");

    status =
        new Fl_Box(
            100,
            495,
            400,
            25,
            "");

    window->end();
    window->show();

    return Fl::run();
}