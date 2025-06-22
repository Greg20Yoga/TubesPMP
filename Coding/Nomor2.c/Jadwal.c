#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Jadwal.h"

jadwal *head_jadwal = NULL;

jadwal* createJadwal(int tanggal) {
    jadwal *newHari = calloc(1, sizeof(jadwal));
    if (newHari == NULL) {
        return NULL;
    }
    newHari->tanggal = tanggal;
    return newHari;
}

void freeJadwal() {
    jadwal *current = head_jadwal, *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}