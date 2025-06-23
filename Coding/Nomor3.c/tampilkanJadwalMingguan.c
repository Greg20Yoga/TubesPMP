#include "tampilkanJadwalMingguan.h"

void tampilkanJadwalMingguan(hari *head, int minggu_ke) {
    int start_date = (minggu_ke-1)*7 + 1;
    int end_date = minggu_ke*7;
    
    // Header mingguan
    printf("\n╔════════════════════════════════════════════════════╗");
    printf("\n║                JADWAL MINGGU KE-%-2d                 ║", minggu_ke);
    printf("\n║                  Tanggal %2d - %-2d                   ║", start_date, end_date);
    printf("\n╠════════════════════════════════════════════════════╣");
    
    hari *current = head;
    int hari_ke = 0;
    
    // Tampilkan per hari
    while(current != NULL && current->tanggal <= end_date) {
        if(current->tanggal >= start_date) {
            // Header hari
            printf("\n║                                                    ║");
            printf("\n║  HARI %-2d (Tgl: %-2d)                                 ║", 
                   ++hari_ke, current->tanggal);
            
            printf("\n╠════════════════════════════════════════════════════╣");
            
            // Tampilkan jadwal harian 
            printf("\n║  ");
            printf("┌────────────────────────────────────────────┐");
            printf("    ║");
            
            // Shift Pagi
            printf("\n║  │ %-42s   │    ║", "🕗 Pagi");
            if(current->pagi[0] == NULL) {
                printf("\n║  │ %-42s │    ║", "(Belum ada jadwal)");
            } else {
                for(int i = 0; i < 5 && current->pagi[i] != NULL; i++) {
                    printf("\n║  │ • %-38s   │    ║", current->pagi[i]->nama);
                }
            }
            
            // Shift Siang
            printf("\n║  ├────────────────────────────────────────────┤    ║");
            printf("\n║  │ %-42s   │    ║", "🕛 Siang");
            if(current->siang[0] == NULL) {
                printf("\n║  │ %-42s │    ║", "(Belum ada jadwal)");
            } else {
                for(int i = 0; i < 5 && current->siang[i] != NULL; i++) {
                    printf("\n║  │ • %-38s   │    ║", current->siang[i]->nama);
                }
            }
            
            // Shift Malam
            printf("\n║  ├────────────────────────────────────────────┤    ║");
            printf("\n║  │ %-42s   │    ║", "🕖 Malam");
            if(current->malam[0] == NULL) {
                printf("\n║  │ %-42s │    ║", "(Belum ada jadwal)");
            } else {
                for(int i = 0; i < 5 && current->malam[i] != NULL; i++) {
                    printf("\n║  │ • %-38s   │    ║", current->malam[i]->nama);
                }
            }
            
            printf("\n║  └────────────────────────────────────────────┘");
            printf("    ║");
        }
        current = current->next;
    }
    
    printf("\n║                                                    ║");
    printf("\n╚════════════════════════════════════════════════════╝\n");
}
