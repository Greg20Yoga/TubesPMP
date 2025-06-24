/* File : Jadwal.h */

#ifndef JADWAL_H
#define JADWAL_H

#include "Dokter.h"

typedef struct jadwal {
    int tanggal;
    dokter *pagi[5];
    dokter *siang[5];
    dokter *malam[5];
    struct jadwal *next;
} jadwal;
/* Membuat Struktur Data Linked List Jadwal */

extern jadwal *head_jadwal;
/* Menginisialisasi head awal jadwal */

jadwal* createJadwal(int tanggal);
/* I.S. Sembarang
   F.S. Menghasilkan sebuah struktur data jadwal baru
   Menghasilkan sebuah Node jadwal baru dengan tanggal yang diberikan.
   Jika alokasi gagal, mengembalikan NULL. */

void freeJadwal();
/* Dealokasi linked list jadwal untuk mencegah kebocoran memori */
#endif