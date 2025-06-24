#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mainProgram.h"
#include "Cekulang.h"
#include "Greedytubes.h"
#include "Dokter.h"
#include "Jadwal.h"

int main2() {
    int pelanggaran_preferensi = 0;
    srand(time(NULL));
    const char* csv_filename = "data_dokter.csv";
    openfileDokter(csv_filename);
    if (head_dokter == NULL) {
        printf("Tidak dapat memperoleh data dokter.\n");
        return 1;
    }
    inisialisasiJadwal(7);
    buatJadwal();
    if (checkEmpty()) {
        if (hitungDokterTersedia() == 0) {
            printf("\nError: Kurang dokter untuk mengisi semua jadwal.\n");
        } else {
            randomtoEmpty(&pelanggaran_preferensi);
        }
    }  
    printf("Total pelanggaran preferensi: %d\n", pelanggaran_preferensi);
    simpanJadwalKeCSV("JadwalDokter.csv");
    freeDokter();
    freeJadwal();
    return 0;
}