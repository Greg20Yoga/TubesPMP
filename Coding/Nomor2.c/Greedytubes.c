#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Greedytubes.h"

void openfileDokter(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror(filename);
        return;
    }
    char line[256];
    dokter *current = NULL;
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file)) {
        int id, maxShift, prefShift;
        char name[50];
        int items_parsed = sscanf(line, "%d,%49[^,],%d,%d", &id, name, &prefShift, &maxShift);

        if (items_parsed == 4) {
            dokter *newDokter = createDokter(id, name, maxShift, prefShift);
            if (newDokter) {
                if (head_dokter == NULL) {
                    head_dokter = newDokter;
                    current = head_dokter;
                } else {
                    current->next = newDokter;
                    current = newDokter;
                }
            }
        }
    }
    fclose(file);
    printf("Successfully loaded %s\n", filename);
}

void inisialisasiJadwal(int numDays) {
    jadwal *tail_hari = NULL;
    for (int i = 1; i <= numDays; i++) {
        jadwal *newHariNode = createJadwal(i);
        if (!newHariNode) {
            return;
        }
        if (head_jadwal == NULL) {
            head_jadwal = newHariNode;
            tail_hari = newHariNode;
        } 
        else {
            tail_hari->next = newHariNode;
            tail_hari = newHariNode;
        }
    }
}

int cekDokter(jadwal* hari, dokter* dokter) {
    for (int i = 0; i < 5; i++) {
        if ((hari->pagi[i] == dokter) || (hari->siang[i] == dokter) || (hari->malam[i] == dokter)) {
            return 1;
        }
    }
    return 0;
}

void jadwalDokter(int preference) {
    for (dokter* currentDokter = head_dokter; currentDokter != NULL; currentDokter = currentDokter->next) {
        if (currentDokter->prefShift != preference) continue;

        for (jadwal* currentHari = head_jadwal; currentHari != NULL; currentHari = currentHari->next) {
            if (currentDokter->totalShift < currentDokter->maxShift && !cekDokter(currentHari, currentDokter)) {
                int assigned = 0;
                for (int i = 0; i < 5 && !assigned; i++) {
                    switch (preference) {
                        case 0: 
                            if (!currentHari->pagi[i])  { 
                                currentHari->pagi[i]  = currentDokter; 
                                assigned = 1; 
                            } 
                            break;
                        case 1: 
                            if (!currentHari->siang[i]) { 
                                currentHari->siang[i] = currentDokter; 
                                assigned = 1; 
                            } 
                            break;
                        case 2: 
                            if (!currentHari->malam[i]) { 
                                currentHari->malam[i] = currentDokter; 
                                assigned = 1; 
                            }   
                            break;
                        case 3:
                            if (!currentHari->pagi[i]) { 
                                currentHari->pagi[i]  = currentDokter; assigned = 1; 
                            }
                            else if (!currentHari->siang[i]){ 
                                currentHari->siang[i] = currentDokter; 
                                assigned = 1; 
                            }
                            break;
                        case 4:
                            if (!currentHari->pagi[i]) { 
                                currentHari->pagi[i]  = 
                                currentDokter; 
                                assigned = 1; 
                            }
                            else if (!currentHari->malam[i]) { 
                                currentHari->malam[i] = currentDokter; 
                                assigned = 1; 
                            }
                            break;
                        case 5:
                            if (!currentHari->siang[i]) { 
                                currentHari->siang[i] = currentDokter; 
                                assigned = 1; 
                            }
                            else if (!currentHari->malam[i]) { 
                                currentHari->malam[i] = currentDokter; 
                                assigned = 1; 
                            }
                            break;
                        case 6:
                            if (!currentHari->pagi[i]) { 
                                currentHari->pagi[i]  = currentDokter; 
                                assigned = 1; 
                            }
                            else if (!currentHari->siang[i]) { 
                                currentHari->siang[i] = currentDokter;
                                assigned = 1; 
                                }
                            else if (!currentHari->malam[i]) { 
                                currentHari->malam[i] = currentDokter; 
                                assigned = 1; 
                            }
                            break;
                    }
                }
                if (assigned) {
                    currentDokter->totalShift++;
                }
            }
        }
    }
}

void buatJadwal() {
    if (!head_jadwal || !head_dokter) {
        return;
    }
    jadwalDokter(0);
    jadwalDokter(1);
    jadwalDokter(2);
    jadwalDokter(3);
    jadwalDokter(4);
    jadwalDokter(5);
    jadwalDokter(6);
}