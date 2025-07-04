#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Cekulang.h"
#include "Greedytubes.h"

int checkEmpty() {
    for (jadwal* currentHari = head_jadwal; currentHari != NULL; currentHari = currentHari->next) {
        dokter** shifts[] = { currentHari->pagi, currentHari->siang, currentHari->malam };
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
                if (shifts[i][j] == NULL) {
                    return 1; 
                }
            }
        }
    }
    return 0;
}

int cekPelanggaran(dokter* dokter, int tipeShift) {
    int preferensi = dokter->prefShift;
    switch (tipeShift) {
        case 0:
            if (preferensi == 0 || preferensi == 3 || preferensi == 4 || preferensi == 6) {
                return 0;
                break;
            }
        case 1:
            if (preferensi == 1 || preferensi == 3 || preferensi == 5 || preferensi == 6) {
                return 0;
                break;
            }
        case 2:
            if (preferensi == 2 || preferensi == 4 || preferensi == 5 || preferensi == 6) {
                return 0;
                break;
            }
    }
    return 1;
}

int hitungDokterTersedia() {
    int count = 0;
    for (dokter* d = head_dokter; d != NULL; d = d->next) {
        if (d->totalShift < d->maxShift) {
            count++;
        }
    }
    return count;
}

void randomtoEmpty(int* pelanggaran_preferensi) {
    if (!head_dokter) return;

    for (jadwal* currentHari = head_jadwal; currentHari != NULL; currentHari = currentHari->next) {
        dokter** shifts[] = { currentHari->pagi, currentHari->siang, currentHari->malam };
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 5; i++) {
                
                if (shifts[j][i] == NULL) { 
                    int availableCount = 0;
                    for (dokter* d = head_dokter; d != NULL; d = d->next) {
                        if (d->totalShift < d->maxShift && !cekDokter(currentHari, d)) {
                            availableCount++;
                        }
                    }
                    if (availableCount == 0) continue;

                    dokter** availableDocs = malloc(availableCount * sizeof(dokter*));
                    if (!availableDocs) return;
                    
                    int k = 0;
                    for (dokter* d = head_dokter; d != NULL; d = d->next) {
                        if (d->totalShift < d->maxShift && !cekDokter(currentHari, d)) {
                            availableDocs[k++] = d;
                        }
                    }
                    
                    for (int n = availableCount - 1; n > 0; n--) {
                        int r = rand() % (n + 1);
                        dokter* temp = availableDocs[r];
                        availableDocs[r] = availableDocs[n];
                        availableDocs[n] = temp;
                    }

                    if (availableCount > 0) {
                        dokter* candidate = availableDocs[0];
                        shifts[j][i] = candidate;
                        candidate->totalShift++;

                        if (cekPelanggaran(candidate, j)) {
                            pelanggaran_preferensi++;
                        }
                    }
                    
                    free(availableDocs);
                }
            }
        }
    }
}

void simpanJadwalKeCSV(const char* namaFile) {
    FILE *file = fopen(namaFile, "w");
    if (file == NULL) {
        perror("Error: Gagal membuat atau membuka file untuk menyimpan jadwal");
        return;
    }

    fprintf(file, "Tanggal,Shift,Slot,ID_Dokter,Nama_Dokter\n");

    for (jadwal* day = head_jadwal; day != NULL; day = day->next) {
        const char* nama_shift[] = {"Pagi", "Siang", "Malam"};
        dokter** daftar_shift[] = {day->pagi, day->siang, day->malam};

        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 5; i++) {
                dokter* d = daftar_shift[j][i];
                int nomor_slot = i + 1;

                if (d != NULL) {
                    // Jika slot terisi, tulis semua data
                    fprintf(file, "%d,%s,%d,%d,%s\n", day->tanggal, nama_shift[j], nomor_slot, d->id, d->nama);
                } else {
                    // Jika slot kosong, tulis data hari, shift, dan slot, lalu kosongkan data dokter
                    fprintf(file, "%d,%s,%d,,\n", day->tanggal, nama_shift[j], nomor_slot);
                }
            }
        }
    }

    fclose(file);
    printf("\nJadwal telah berhasil disimpan ke file: %s\n", namaFile);
}