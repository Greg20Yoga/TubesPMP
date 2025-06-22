/* File : Greedytubes.h */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef GREEDYTUBES_H
#define GREEDYTUBES_H

#include "Dokter.h"
#include "Jadwal.h"


void openfileDokter(const char* filename);
/* I.S. Nama file csv data dokter 
   F.S. Menghasilkan Linked List dengan data dokter sesuai dengan file csv yang diinput
   Membaca file CSV yang berisi data dokter, membuat Node dokter baru untuk setiap baris data, dan menambahkannya ke Linked List dokter.
   Jika file pointer bernilai NULL, Fungsi memberikan output (filename): No such file or directory */

void inisialisasiJadwal(int numDays);
/* I.S. Jumlah hari yang akan diinisialisasi
   F.S. Menginisialisasi jadwal untuk jumlah hari numDays dengan membangun struktur jadwal kosong. 
   Menginisialisasi jadwal untuk beberapa hari dengan membuat dan menyambungkan beberapa node jadwal yang kosong. */

int cekDokter(jadwal* hari, dokter* dokter);
/* I.S. hari dan dokter yang ingin diperiksa keberadaanya pada hari tersebut
   F.S. Mengembalikan 1 jika dokter sudah ditugaskan pada hari tersebut
   Memeriksa apakah seorang dokter sudah ditugaskan pada shift */

void jadwalDokter(int preference);
/* I.S. preferensi dokter yang ingin dijadwalkan 
   F.S. Dokter dengn preferensi input ditugaskan pada jadwal
   Menempatkan semua dokter dengan kode preferensi yang diinput yang belum mencapai batas shift maksimalnya ke dalam jadwal*/

void buatJadwal();
/* I.S. Sembarang
   F.S. Jadwal dengan semua dokter yang telah ditugaskan
   Menjalankan fungsi jadwal dokter secara berurutan sesuai dengan prioritas Greedy */
#endif