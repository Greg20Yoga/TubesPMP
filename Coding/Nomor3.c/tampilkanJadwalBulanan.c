#include "tampilkanJadwalBulanan.h"

void tampilkanJadwalMingguan(hari *head) {
    // Header Bulanan
    printf("\n╔════════════════════════════════════════════════════╗");
    printf("\n║                   JADWAL BULANAN                   ║");
    printf("\n╠════════════════════════════════════════════════════╣");
    
    hari *current = head;
    int tanggal = 0;
    
    // Tampilkan per hari
    while(current != NULL && tanggal<=30) {
        // Header hari
        printf("\n║                                                    ║");
        printf("\n║  HARI %-2d (Tgl: %-2d)                                 ║", 
               tanggal++, current->tanggal);
            
        printf("\n╠════════════════════════════════════════════════════╣");
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
    
    current = current->next;
    if (current==NULL) current = head;
    }
    
    printf("\n║                                                    ║");
    printf("\n╚════════════════════════════════════════════════════╝\n");
}
