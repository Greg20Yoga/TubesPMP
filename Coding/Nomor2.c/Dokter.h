#ifndef DOKTER_H
#define DOKTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct dokter {
    int id;
    char nama[50];
    int maxShift;
    int prefShift;
    int totalShift;
    struct dokter *next;
} dokter;
/* Membuat Struktur Data Linked List Dokter */

dokter *head_dokter = NULL;
/* Menginisialisasi head awal Dokter */

dokter* createDokter(int id, const char* nama, int maxshift, int prefShift);
/* I.S. Sembarang
   F.S. Menghasilkan sebuah Node Linked List dokter
   Menghasilkan sebuah Node dokter baru dengan id, nama, maxshift, dan prefShift yang diberikan.
   Jika alokasi gagal, mengembalikan NULL. */

void freeDokter();
/* Dealokasi linked list dokter untuk mencegah kebocoran memori */

#endif