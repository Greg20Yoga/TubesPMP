#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Cekulang.h"
#include "Greedytubes.h"
#include "Dokter.h"
#include "Jadwal.h"

void printJadwal() {
    printf("========================================= WEEKLY SCHEDULE =========================================\n");
    for (jadwal* day = head_jadwal; day != NULL; day = day->next) {
        printf("\n------------------------------------------- DAY %d -------------------------------------------\n", day->tanggal);
        char buffer[64];
        // Pagi
        printf("Pagi:\t");
        for (int i = 0; i < 5; i++) {
            if (day->pagi[i]) {
                snprintf(buffer, sizeof(buffer), "%s (ID:%d)", day->pagi[i]->nama, day->pagi[i]->id);
                printf("%-22s\t", buffer);
            } else {
                printf("%-22s\t", "[Empty]");
            }
        }
        printf("\n");
        // Siang
        printf("Siang:\t");
        for (int i = 0; i < 5; i++) {
            if (day->siang[i]) {
                snprintf(buffer, sizeof(buffer), "%s (ID:%d)", day->siang[i]->nama, day->siang[i]->id);
                printf("%-22s\t", buffer);
            } else {
                printf("%-22s\t", "[Empty]");
            }
        }
        printf("\n");
        // Malam
        printf("Malam:\t");
        for (int i = 0; i < 5; i++) {
            if (day->malam[i]) {
                snprintf(buffer, sizeof(buffer), "%s (ID:%d)", day->malam[i]->nama, day->malam[i]->id);
                printf("%-22s\t", buffer);
            } else {
                printf("%-22s\t", "[Empty]");
            }
        }
        printf("\n");
    }
    printf("===================================================================================================\n");
}

int main() {
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
    printJadwal();
    printf("Total pelanggaran preferensi: %d\n", pelanggaran_preferensi);
    freeDokter();
    freeJadwal();
    return 0;
}