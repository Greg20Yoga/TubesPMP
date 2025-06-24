#ifndef MENU_TAMPILKAN_JADWAL_H
#define MENU_TAMPILKAN_JADWAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include Dokter.h
#include Jadwal.h

void menu_tampilkan_jadwal();

// Include header untuk fungsi-fungsi yang dipanggil
#include "MenampilkanJadwal_Harian.h"
#include "MenampilkanJadwal_Mingguan.h"
#include "MenampilkanJadwal_Bulanan.h"
#include "tampilkanJumlahPelanggaran.h"

#endif
