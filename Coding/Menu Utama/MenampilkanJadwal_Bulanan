#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "MenampilkanJadwal_Bulanan.h"
// jadwal bulanan
void tampilkanJadwal_Bulanan(jadwal* head) {
    const char* namaHari[7] = {
        "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"
    };

    printf("\n╔════════════════════════════════════════════════════╗");
    printf("\n║             📅 JADWAL DOKTER BULANAN (30 HARI)     ║");
    printf("\n╚════════════════════════════════════════════════════╝\n");

    jadwal* current = head;
    int hariKe = 1;
    int hariIndex = 0;

    while (hariKe <= 30) {
        printf("\n═══════════════════════════════════════════════════════");
        printf("\n📆 HARI KE-%d | %s | TANGGAL %d", hariKe, namaHari[hariIndex % 7], current->tanggal);
        printf("\n═══════════════════════════════════════════════════════");

        // SHIFT PAGI
        printf("\n🕗 SHIFT PAGI\n");
        for (int i = 0; i < 5; i++) {
            if (current->pagi[i]) {
                printf("• %s (ID:%d)\n", current->pagi[i]->nama, current->pagi[i]->id);
            } else {
                printf("• [Kosong]\n");
            }
        }

        // SHIFT SIANG
        printf("\n🕛 SHIFT SIANG\n");
        for (int i = 0; i < 5; i++) {
            if (current->siang[i]) {
                printf("• %s (ID:%d)\n", current->siang[i]->nama, current->siang[i]->id);
            } else {
                printf("• [Kosong]\n");
            }
        }

        // SHIFT MALAM
        printf("\n🌙 SHIFT MALAM\n");
        for (int i = 0; i < 5; i++) {
            if (current->malam[i]) {
                printf("• %s (ID:%d)\n", current->malam[i]->nama, current->malam[i]->id);
            } else {
                printf("• [Kosong]\n");
            }
        }

        hariKe++;
        hariIndex++;
        current = current->next;

        // Jika sudah 7 hari atau terakhir, pause
        if ((hariKe - 1) % 7 == 0 || hariKe > 30) {
            printf("\nTekan ENTER untuk lanjut...");
            getchar(); // untuk buffer dari scanf
            getchar(); // tunggu enter
        }
    }
}
