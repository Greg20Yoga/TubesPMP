#ifndef OLAHDATA_H
#define OLAHDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "Data_Dokter.csv"

#include "dokter.h"
#include "jadwal.h"

extern Dokter data[MAX];
extern int jumlah;

void bacaFile();
void simpanFile();
void tampilkanData();
void tambahDokter();
void hapusDokter();

#endif
