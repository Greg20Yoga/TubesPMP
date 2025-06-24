/* File : Cekulang.h */

#ifndef CEKULANG_H
#define CEKULANG_H

#include "Dokter.h"
#include "Jadwal.h"

int checkEmpty(void);
/* I.S. Sembarang
   F.S. Mengembalikan 1 jika ada slot kosong di jadwal,
   Memeriksa keberadaan slot kosong*/

int cekPelanggaran(dokter* dokter, int tipeShift);
/* I.S. Dokter dan tipe shift okter
   F.S. Mengembalikan 1 jika menemukan pelanggaran preferensi,
   Memeriksa apakah penempatan dokter merupakan pelanggaran preferensi dokter tersebut */

int hitungDokterTersedia();
/* Mencari dokter dengan jumlah shift belum memenuhi maxshift */

void randomtoEmpty(int* pelanggaran_preferensi);
/* Mengisi semua slot kosong dengan memilih secara acak dari daftar dokter dengan jumlah shift yang belum memenuhi maxshift */

void simpanJadwalKeCSV(const char* namaFile);
/* I.S. Nama file untuk menyimpan jadwal
   F.S. Jadwal disimpan dalam format CSV
   Menyimpan jadwal ke dalam file CSV dengan format yang telah ditentukan */
#endif
