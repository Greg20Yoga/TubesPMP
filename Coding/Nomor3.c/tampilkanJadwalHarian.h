#ifndef JADWAL_H
#define JADWAL_H

#include <stdio.h>  

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

void tampilkanJadwalHarian(hari *day);

#endif
