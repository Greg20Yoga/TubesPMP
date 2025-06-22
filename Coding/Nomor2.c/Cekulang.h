/* File : Cekulang.h */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef CEKULANG_H
#define CEKULANG_H

#include "Dokter.h"
#include "Jadwal.h"

int pelanggaran_preferensi = 0;
/* Menginisialisasi variabel tipe integer pelanggaran preferensi */

int checkEmpty(void);
/* I.S. Sembarang
   F.S. Mengembalikan 1 jika ada slot kosong di jadwal,
   Memeriksa keberadaan slot kosong*/

int cekPelanggaran(dokter* dokter, int tipeShift);
/* I.S. Dokter dan tipe shift dokter
   F.S. Mengembalikan 1 jika menemukan pelanggaran preferensi,
   Memeriksa apakah penempatan dokter merupakan pelanggaran preferensi dokter tersebut */

void randomtoEmpty(int* pelanggaran_preferensi);
/* Mengisi semua slot kosong dengan memilih secara acak dari daftar dokter dengan jumlah shift yang belum memenuhi maxshift */
#endif
