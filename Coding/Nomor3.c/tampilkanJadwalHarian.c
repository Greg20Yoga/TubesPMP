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
