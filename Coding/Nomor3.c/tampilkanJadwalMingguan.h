#ifndef TAMPILKANJADWALMINGGUAN_H
#define TAMPILKANJADWALMINGGUAN_H

#include <stdio.h>  // Untuk printf()

// Deklarasi struktur (sama seperti sebelumnya)
typedef struct dokter {
    char nama[50];
    int maxShift;
    int preferensi;
    int totalShift;
    struct dokter *next;
} dokter;

typedef struct hari {
    int tanggal;
    dokter *pagi[5];
    dokter *siang[5];
    dokter *malam[5];
    struct hari *next;
} hari;

// Deklarasi fungsi
void tampilkanJadwalMingguan(hari *head, int minggu_ke);

#endif
