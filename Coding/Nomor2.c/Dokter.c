#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Dokter.h"

dokter *head_dokter = NULL;

dokter* createDokter(int id, const char* nama, int maxshift, int prefShift) {
    dokter *newDokter = malloc(sizeof(dokter));
    if (newDokter == NULL) {
        return NULL;
    }
    newDokter->id = id;
    strncpy(newDokter->nama, nama, sizeof(newDokter->nama) - 1);
    newDokter->nama[sizeof(newDokter->nama) - 1] = '\0';
    newDokter->maxShift = maxshift;
    newDokter->prefShift = prefShift;
    newDokter->totalShift = 0;
    newDokter->next = NULL;
    return newDokter;
}

void freeDokter() {
    dokter *current = head_dokter, *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
