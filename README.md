# Kriptografi Klasik

Enkripsi/dekripsi Caesar Cipher, Playfair Cipher, dan Transposisi Kolom

## Persiapan

ompiler C++ `g++`. Versi GUI pakai FLTK. Di Linux, perintah `fltk-config` harus tersedia. Di Windows, pastikan compiler menemukan header dan library FLTK.

## Jalankan versi CLI

### Linux

```bash
g++ main.cpp caesar/caesar.cpp playfair/playfair.cpp transposisi_kolom/transposisi_kolom.cpp gabungan/gabungan.cpp -o program
./program
```

### Windows

PowerShell:

```text
g++ main.cpp caesar/caesar.cpp playfair/playfair.cpp transposisi_kolom/transposisi_kolom.cpp gabungan/gabungan.cpp -o program.exe
```

PowerShell:

```powershell
.\program.exe
```

Command Prompt:

```bat
program.exe
```

## RUN GUI

### Linux

```bash
g++ $(fltk-config --cxxflags) UI/gui.cpp caesar/caesar.cpp playfair/playfair.cpp transposisi_kolom/transposisi_kolom.cpp gabungan/gabungan.cpp -o gui_program $(fltk-config --ldflags)
./gui_program
```

### Windows

RUN PowerShell/CMD `g++`:

```text
g++ UI/gui.cpp caesar/caesar.cpp playfair/playfair.cpp transposisi_kolom/transposisi_kolom.cpp gabungan/gabungan.cpp -o gui_program.exe -lfltk
```

PowerShell:

```powershell
.\gui_program.exe
```

CMD:

```bat
gui_program.exe
```

