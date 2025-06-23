#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// jadwal harian
void tampilkanJadwal_Harian(hari* head) {
    int nomorHari;
    printf("\n╔════════════════════════════════════════════════════╗");
    printf("\n║               📅 TAMPILKAN JADWAL HARIAN           ║");
    printf("\n╚════════════════════════════════════════════════════╝");
    printf("\nMasukkan nomor hari (1 - 30): ");
    scanf("%d", &nomorHari);

    if (nomorHari < 1) {
        printf("❌ Error: Nomor hari tidak valid.\n");
        return;
    }

    // Hitung indeks dalam 7 hari (0 sampai 6)
    int indeks = (nomorHari - 1) % 7;

    // Akses node ke-indeks dari linked list
    hari* current = head;
    for (int i = 0; i < indeks; i++) {
        if (current->next != NULL)
            current = current->next;
    }

    // Header
    printf("\n╔════════════════════════════════════════════════════╗");
    printf("\n║             🗓️  JADWAL UNTUK HARI KE-%-3d          ║", nomorHari);
    printf("\n╚════════════════════════════════════════════════════╝");

    char buffer[64];

    // Shift Pagi
    printf("\n\n🔹 SHIFT PAGI\n");
    printf("────────────────────────────────────────────────────\n");
    for (int i = 0; i < 5; i++) {
        if (current->pagi[i]) {
            snprintf(buffer, sizeof(buffer), "• %s (ID:%d)", current->pagi[i]->nama, current->pagi[i]->id);
            printf("%-50s\n", buffer);
        } else {
            printf("• [Kosong]\n");
        }
    }

    // Shift Siang
    printf("\n🔸 SHIFT SIANG\n");
    printf("────────────────────────────────────────────────────\n");
    for (int i = 0; i < 5; i++) {
        if (current->siang[i]) {
            snprintf(buffer, sizeof(buffer), "• %s (ID:%d)", current->siang[i]->nama, current->siang[i]->id);
            printf("%-50s\n", buffer);
        } else {
            printf("• [Kosong]\n");
        }
    }

    // Shift Malam
    printf("\n🌙 SHIFT MALAM\n");
    printf("────────────────────────────────────────────────────\n");
    for (int i = 0; i < 5; i++) {
        if (current->malam[i]) {
            snprintf(buffer, sizeof(buffer), "• %s (ID:%d)", current->malam[i]->nama, current->malam[i]->id);
            printf("%-50s\n", buffer);
        } else {
            printf("• [Kosong]\n");
        }
    }

    printf("────────────────────────────────────────────────────\n");
}






/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void tampilkanJadwalHarian(hari *day) {

    printf("\n╔══════════════════════════════════════════╗");
    printf("\n║       JADWAL HARIAN - TANGGAL %-2d         ║", day->tanggal);
    printf("\n╠══════════════════════════════════════════╣");
    
    // Shift Pagi
    printf("\n║ %-40s   ║", "🕗  SHIFT PAGI");
    printf("\n╠──────────────────────────────────────────╣");
    if(day->pagi[0] == NULL) {
        printf("\n║ %-40s ║", "  (Belum ada jadwal)");
    } else {
        for(int i = 0; i < 5 && day->pagi[i] != NULL; i++) {
            printf("\n║  • %-36s  ║", day->pagi[i]->nama);
        }
    }
    
    // Shift Siang
    printf("\n╠══════════════════════════════════════════╣");
    printf("\n║ %-40s   ║", "🕛  SHIFT SIANG");
    printf("\n╠──────────────────────────────────────────╣");
    if(day->siang[0] == NULL) {
        printf("\n║ %-40s ║", "  (Belum ada jadwal)");
    } else {
        for(int i = 0; i < 5 && day->siang[i] != NULL; i++) {
            printf("\n║  • %-36s  ║", day->siang[i]->nama);
        }
    }
    
    // Shift Malam
    printf("\n╠══════════════════════════════════════════╣");
    printf("\n║ %-40s   ║", "🕖  SHIFT MALAM");
    printf("\n╠──────────────────────────────────────────╣");
    if(day->malam[0] == NULL) {
        printf("\n║ %-40s ║", "  (Belum ada jadwal)");
    } else {
        for(int i = 0; i < 5 && day->malam[i] != NULL; i++) {
            printf("\n║  • %-36s  ║", day->malam[i]->nama);
        }
    }
    
    printf("\n╚══════════════════════════════════════════╝\n");
}

hari* buatDataDummy() {
    // Buat node hari
    hari *day = (hari*)calloc(1, sizeof(hari));
    day->tanggal = 1;
    
    // Inisialisasi semua pointer ke NULL
    for(int i = 0; i < 5; i++) {
        day->pagi[i] = NULL;
        day->siang[i] = NULL;
        day->malam[i] = NULL;
    }
    
    // Buat dan isi data dokter (hanya yang diperlukan)
    dokter* buatDokter(const char* nama, int preferensi) {
        dokter *dr = (dokter*)calloc(1, sizeof(dokter));
        strncpy(dr->nama, nama, 49);
        dr->nama[49] = '\0';
        dr->preferensi = preferensi;
        dr->maxShift = 5;
        return dr;
    }
    
    // Isi shift pagi
    day->pagi[0] = buatDokter("Dr. Ahmad", 0);
    day->pagi[1] = buatDokter("Dr. Dian", 3);
    
    // Isi shift siang
    day->siang[0] = buatDokter("Dr. Budi", 1);
    day->siang[1] = buatDokter("Dr. Dian", 3);  // Reuse Dr. Dian
    
    // Isi shift malam
    day->malam[0] = buatDokter("Dr. Citra", 2);
    day->malam[1] = buatDokter("Dr. Eka", 4);
    
    return day;
}

void bersihkanMemori(hari *day) {
    if(!day) return;
    
    // Kumpulkan semua dokter unik untuk di-free
    dokter *doctors[10];
    int count = 0;
    
    // Koleksi dokter dari semua shift
    for(int i = 0; i < 5 && day->pagi[i]; i++) {
        doctors[count++] = day->pagi[i];
    }
    for(int i = 0; i < 5 && day->siang[i]; i++) {
        // Cek duplikat sebelum menambahkan
        int is_duplicate = 0;
        for(int j = 0; j < count; j++) {
            if(day->siang[i] == doctors[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if(!is_duplicate) doctors[count++] = day->siang[i];
    }
    for(int i = 0; i < 5 && day->malam[i]; i++) {
        int is_duplicate = 0;
        for(int j = 0; j < count; j++) {
            if(day->malam[i] == doctors[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if(!is_duplicate) doctors[count++] = day->malam[i];
    }
    
    // Free semua dokter unik
    for(int i = 0; i < count; i++) {
        free(doctors[i]);
    }
    
    // Free node hari
    free(day);
}

int main() {
    // Buat data dummy
    hari *jadwalDummy = buatDataDummy();
    
    // Tampilkan jadwal
    tampilkanJadwalHarian(jadwalDummy);
    
    // Bersihkan memori
    bersihkanMemori(jadwalDummy);
    
    // Pastikan pointer di-nullkan setelah di-free
    jadwalDummy = NULL;
    
    return 0;
}

*/





/*
void tampilkanJadwalHarian(hari *day) {

    printf("\n╔══════════════════════════════════════════╗");
    printf("\n║       JADWAL HARIAN - TANGGAL %-2d         ║", day->tanggal);
    printf("\n╠══════════════════════════════════════════╣");
    
    // Shift Pagi
    printf("\n║ %-40s   ║", "🕗  SHIFT PAGI");
    printf("\n╠──────────────────────────────────────────╣");
    if(day->pagi[0] == NULL) {
        printf("\n║ %-40s ║", "  (Belum ada jadwal)");
    } else {
        for(int i = 0; i < 5 && day->pagi[i] != NULL; i++) {
            printf("\n║  • %-36s  ║", day->pagi[i]->nama);
        }
    }
    
    // Shift Siang
    printf("\n╠══════════════════════════════════════════╣");
    printf("\n║ %-40s   ║", "🕛  SHIFT SIANG");
    printf("\n╠──────────────────────────────────────────╣");
    if(day->siang[0] == NULL) {
        printf("\n║ %-40s ║", "  (Belum ada jadwal)");
    } else {
        for(int i = 0; i < 5 && day->siang[i] != NULL; i++) {
            printf("\n║  • %-36s  ║", day->siang[i]->nama);
        }
    }
    
    // Shift Malam
    printf("\n╠══════════════════════════════════════════╣");
    printf("\n║ %-40s   ║", "🕖  SHIFT MALAM");
    printf("\n╠──────────────────────────────────────────╣");
    if(day->malam[0] == NULL) {
        printf("\n║ %-40s ║", "  (Belum ada jadwal)");
    } else {
        for(int i = 0; i < 5 && day->malam[i] != NULL; i++) {
            printf("\n║  • %-36s  ║", day->malam[i]->nama);
        }
    }
    
    printf("\n╚══════════════════════════════════════════╝\n");
}
*/
