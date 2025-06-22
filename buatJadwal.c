#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct dokter{
    char nama[50];  // nama dokter
    int maxShift;   // Maksimal shift per minggu
    int preferensi; // preferensi hari pertama
    int totalShift; // counter untuk menghitung sudah berapa shift dalam seminggu
    struct dokter *next;
} dokter;

typedef struct hari{
    int tanggal;        // Tanggal hari
    dokter *pagi[5];    // Dokter-dokter pada shift pagi
    dokter *siang[5];   // Dokter-dokter pada shift siang
    dokter *malam[5];   // Dokter-dokter pada shift malam
    struct hari *next;
} hari;

hari *head_hari = NULL;
dokter *head_dokter = NULL;

void bacaFile() { // Fungsi untuk membaca file dan membuat linked list dokter
    char line[100];
    FILE *file = fopen("daftar_dokter.csv", "r");
    while(fgets(line, 100, file)) {
        dokter *new = malloc(sizeof(dokter));
        strcpy(new->nama, strtok(line, ","));
        new->maxShift = atoi(strtok(NULL, ","));
        new->preferensi = atoi(strtok(NULL, ","));
        new->totalShift=0;
        if (head_dokter==NULL) {
            new->next=NULL;
            head_dokter=new;
        }
        else {
            new->next=head_dokter;
            head_dokter=new;
        }
    }
    fclose(file);
}

void buatHari() { // Fungsi untuk membuat linked list hari
    for (int i=1;i<31;i++) {
        hari *new = malloc(sizeof(hari));
        new->tanggal=i;
        memset(new->pagi, 0, sizeof(new->pagi));
        memset(new->siang, 0, sizeof(new->siang));
        memset(new->malam, 0, sizeof(new->malam));
        new->next = NULL;
        if (head_hari==NULL) {
            head_hari=new;
        }
        else {
            hari *current = head_hari;
            while (current->next!=NULL) {
                current=current->next;
            }
            current->next=new;
        }
    }
}

dokter* salinDokter(const dokter *sumber) { // Fungsi untuk menyalin struct dokter
    dokter *target = malloc(sizeof(dokter));
    strcpy(target->nama, sumber->nama);
    target->maxShift = sumber->maxShift;
    target->preferensi = sumber->preferensi;
    target->totalShift = 0;
    target->next = NULL;
    return target;
}

void salinArray(dokter *sumber[], dokter *target[], int counter) { // Fungsi untuk menyalin array of struct dokter
    for (int i = 0; i < counter; i++) {
        target[i] = salinDokter(sumber[i]);
    }
}

void randomIndeks(int counter_dokter, int totalShiftPref, int indeksRandom[5], int maks, int sisa) { // Fungsi untuk menghasilkan random index angka
    for (int i = 0; i < 5; i++) {
        indeksRandom[i] = -1;
    }
    indeksRandom[0] = rand() % counter_dokter;
    if (totalShiftPref >= (1+sisa) && counter_dokter >= 2 && maks >=2) { // Jika bisa mengassign 2 dokter sekaligus 
        do {
            indeksRandom[1] = rand() % counter_dokter;
        } while (indeksRandom[1] == indeksRandom[0]);
    }
    if (totalShiftPref >= (2+sisa) && counter_dokter >= 3 && maks >=3) { // Jika bisa mengassign 3 dokter sekaligus
        do {
            indeksRandom[2] = rand() % counter_dokter;
        } while (indeksRandom[2] == indeksRandom[0] || 
                 indeksRandom[2] == indeksRandom[1]);
    }
    if (totalShiftPref >= (3+sisa) && counter_dokter >= 4 && maks >=4) { // Jika bisa mengassign 4 dokter sekaligus
        do {
            indeksRandom[3] = rand() % counter_dokter;
        } while (indeksRandom[3] == indeksRandom[0] || 
                 indeksRandom[3] == indeksRandom[1] || 
                 indeksRandom[3] == indeksRandom[2]);
    }
    if (totalShiftPref >= (4+sisa) && counter_dokter >= 5 && maks >=5) { // Jika bisa mengassign 5 (maksimal) dokter sekaligus
        do {
            indeksRandom[4] = rand() % counter_dokter;
        } while (indeksRandom[4] == indeksRandom[0] || 
                 indeksRandom[4] == indeksRandom[1] || 
                 indeksRandom[4] == indeksRandom[2] || 
                 indeksRandom[4] == indeksRandom[3]);
    }
}

void distribusiArray (  dokter *kekurangan[], dokter *lebih1[], dokter *lebih2[], 
                        int *sumShiftKekurangan, int *sumShiftLebih1, int *sumShiftLebih2,
                        int *counterKekurangan, int *counterLebih1, int *counterLebih2) { // Fungsi untuk memindahkan dokter dari satu array ke array lainnya
    if (*sumShiftLebih1 >= *sumShiftLebih2) {
        *counterLebih1-=1;
        kekurangan[*counterKekurangan] = lebih1[*counterLebih1];
        *sumShiftKekurangan+=kekurangan[*counterKekurangan]->maxShift;
        *sumShiftLebih1-=kekurangan[*counterKekurangan]->maxShift;
        *counterKekurangan+=1;
    } 
    else {
        *counterLebih2-=1;
        kekurangan[*counterKekurangan] = lebih2[*counterLebih2];
        *sumShiftKekurangan+=kekurangan[*counterKekurangan]->maxShift;
        *sumShiftLebih2-=kekurangan[*counterKekurangan]->maxShift;
        *counterKekurangan+=1;
    }
}

void hitungMaxShift(dokter *pagi[], dokter *siang[], dokter *malam[],
                    int *shiftPagi, int *shiftSiang, int *shiftMalam,
                    int counter_pagi, int counter_siang, int counter_malam) { // Fungsi untuk menghitung maksimal shift per minggu semua dokter tiap preferensi
    *shiftPagi=0; *shiftSiang=0; *shiftMalam=0;
    for(int i=0; i<counter_pagi; i++) {
        *shiftPagi+=pagi[i]->maxShift;
    }
    for(int i=0; i<counter_siang; i++) {
        *shiftSiang+=siang[i]->maxShift;
    }
    for(int i=0; i<counter_malam; i++) {
        *shiftMalam+=malam[i]->maxShift;
    }
}

void assignDokter(int *counter, int *totalShift, dokter *shift[], hari *current_hari, int p, int maks, int sisa) { // Fungsi untuk mengambil dokter secara dari array preferensi, lalu mengassign ke array shift pada ndoe hari
    int indeksRandom[5];
    randomIndeks(*counter, *totalShift, indeksRandom, maks, sisa);
    for (int i=0;i<5;i++) {
        if (indeksRandom[i] != -1) { 
            if (p==0) {
                current_hari->pagi[i]= shift[indeksRandom[i]];
            }
            else if (p==1) {
                current_hari->siang[i]= shift[indeksRandom[i]];
            }
            else if (p==2) {
                current_hari->malam[i]= shift[indeksRandom[i]];
            }
            shift[indeksRandom[i]]->totalShift++;
            *totalShift-=1;
            if (shift[indeksRandom[i]]->totalShift>=shift[indeksRandom[i]]->maxShift) {
                *counter-=1;
                shift[indeksRandom[i]] = shift[*counter];
            }
        }
        else {
            if (p==0) {
                current_hari->pagi[i]=NULL;
            }
            else if (p==1) {
                current_hari->siang[i]=NULL;
            }
            else if (p==2) {
                current_hari->malam[i]=NULL;
            }
        }
    }
}

void buatJadwal() {
    srand(time(NULL));
    // array of struct dokter yang nantinya akan dimasukkan data dokter berdasarkan preferensi
    dokter *pagi[100] = {0};
    dokter *siang[100] = {0};
    dokter *malam[100] = {0};
    // counter untuk menghitung banyak dokter di masing-masing array diatas
    int counter_pagi = 0;
    int counter_siang = 0;
    int counter_malam = 0;
    // counter untuk menghitung maksimal shift per minggu dari semua dokter tiap preferensi
    int shiftPagi, shiftSiang, shiftMalam;

    bacaFile();
    buatHari();

    // Proses mengelompokkan data dokter ke array sesuai preferensi shift
    //========================================================================================================================================================
    // Untuk dokter yang memiliki preferensi satu hari (0,1,2) dahulu, agar nanti bisa dilakukan pemerataan antar shift dengan preferensi yang lebih fleksibel
    dokter *current_dokter = head_dokter;
    while (current_dokter!=NULL) {
        // Jika preferensi pagi
        if (current_dokter->preferensi==0) {
            pagi[counter_pagi]=current_dokter;
            counter_pagi++;
        }
        // Jika preferensi siang
        else if (current_dokter->preferensi==1) {
            siang[counter_siang]=current_dokter;
            counter_siang++;
        }
        // Jika preferensi malam
        else if (current_dokter->preferensi==2) {
            malam[counter_malam]=current_dokter;
            counter_malam++;
        }
        current_dokter=current_dokter->next;
    }

    // Untuk preferensi 3,4,5
    current_dokter = head_dokter;
    while (current_dokter != NULL) {
        // Hitung jumlah maksmial shift per minggu semua dokter untuk masing masing array preferensi shift
        hitungMaxShift(pagi, siang, malam, &shiftPagi, &shiftSiang, &shiftMalam, counter_pagi, counter_siang, counter_malam);
        // Memasukkan data dokter ke array preferensi shift dengan jumlah maksimal shift per minggu terendah
        // Jika preferensi pagi dan siang
        if (current_dokter->preferensi==3) {
            if (shiftPagi<=shiftSiang) {
                pagi[counter_pagi]=current_dokter;
                counter_pagi++;
            }
            else {
                siang[counter_siang]=current_dokter;
                counter_siang++;
            }
        }
        // Jika preferensi pagi dan malam
        else if (current_dokter->preferensi==4) {
            if (shiftPagi<=shiftMalam) {
                pagi[counter_pagi]=current_dokter;
                counter_pagi++;
            }
            else {
                malam[counter_malam]=current_dokter;
                counter_malam++;
            }
        }
        // Jika preferensi siang dan malam
        else if (current_dokter->preferensi==5) {
            if (shiftSiang<=shiftMalam) {
                siang[counter_siang]=current_dokter;
                counter_siang++;
            }
            else {
                malam[counter_malam]=current_dokter;
                counter_malam++;
            }
        }
        current_dokter=current_dokter->next;
    }

    // Untuk yang preferensi 6 (tidak memiliki preferensi)
    // Prosesnya sama dengan proses untuk preferensi 3,4,5
    current_dokter=head_dokter;
    while (current_dokter!=NULL) {
        hitungMaxShift(pagi, siang, malam, &shiftPagi, &shiftSiang, &shiftMalam, counter_pagi, counter_siang, counter_malam);
        if (current_dokter->preferensi>5 || current_dokter->preferensi <0) { // diluar antara 0 sampai 5 dianggap tidak memiliki preferensi
            if ((shiftPagi<shiftSiang || shiftPagi==shiftSiang) && (shiftPagi<shiftMalam || shiftPagi==shiftMalam)) {
                pagi[counter_pagi]=current_dokter;
                counter_pagi++;
            }
            else if (shiftSiang<shiftPagi  && (shiftSiang<shiftMalam || shiftSiang==shiftMalam)) {
                siang[counter_siang]=current_dokter;
                counter_siang++;
            }
            else if (shiftMalam<shiftPagi  && shiftMalam<shiftSiang) {
                malam[counter_malam]=current_dokter;
                counter_malam++;
            }
        }
        current_dokter=current_dokter->next;
    }
    
    hitungMaxShift(pagi, siang, malam, &shiftPagi, &shiftSiang, &shiftMalam, counter_pagi, counter_siang, counter_malam); // Hitung jumlah maksmial shift per minggu semua dokter untuk masing masing array preferensi shift

    // Melakukan pengecekan kembali jumlah maksimal shift per minggu semua dokter untuk masing masing array preferensi shift, apakah cukup untuk setidaknya satu dokter per shift dalam seminggu
    // Jika tidak cukup atau jumlah masksimal shift semua dokter untuk suatu preferensi <7 maka terpaksa memindahkan dokter dari yang bukan preferensinya (melanggar preferensi) jika memungkinkan
    if (shiftPagi<7) {
        while (shiftPagi<7 && (shiftSiang>=13 ||shiftMalam>=13)) {
            distribusiArray (pagi, siang, malam, &shiftPagi, &shiftSiang, &shiftMalam, &counter_pagi, &counter_siang, &counter_malam);
        }
    }
    if (shiftSiang<7) {
        while (shiftSiang<7 && (shiftPagi>=13 ||shiftMalam>=13)) {
            distribusiArray (siang, pagi, malam, &shiftSiang, &shiftPagi, &shiftMalam, &counter_siang, &counter_pagi, &counter_malam);
        }
    }
    if (shiftMalam<7) {
        while (shiftMalam<7 && (shiftSiang>=13 ||shiftPagi>=13)) {
            distribusiArray (malam, siang, pagi, &shiftMalam, &shiftSiang, &shiftPagi, &counter_malam, &counter_siang, &counter_pagi);
        }
    }
    //==============================================================================================================================================
    
    // Default Value agar bisa assign kembali saat reset per minggu ke variabel sementara yang nilainya berubah-ubah selama proses membuat jadwal
    //==========================================================================
    dokter *pagiDef[100];
    dokter *siangDef[100];
    dokter *malamDef[100];
    int counter_pagiDef  = counter_pagi;
    int counter_siangDef = counter_siang;
    int counter_malamDef = counter_malam;
    salinArray(pagi , pagiDef , counter_pagi );
    salinArray(siang, siangDef, counter_siang);
    salinArray(malam, malamDef, counter_malam);
    int shiftPagiDef  = shiftPagi;
    int shiftSiangDef = shiftSiang;
    int shiftMalamDef = shiftMalam;
    //==========================================================================

    // Proses pembuatan jadwal
    //=============================================================================================================================================
    hari *current_hari = head_hari;
    int sisa = 7;
    while(current_hari!=NULL) {
        // Assign shift pagi
        if (counter_pagi>0) {
            int maks = (shiftPagiDef/7)+1; // Maksimal jumlah dokter per shift agar merata setiap hari selama seminggu jika tidak bisa 5 dokter per shift
            if (((maks*7)-shiftPagiDef)>=sisa) maks--;
            assignDokter(&counter_pagi, &shiftPagi, pagi, current_hari, 0, maks, sisa);
        }
        // Assign shift siang
        if (counter_siang>0) {
            int maks = (shiftSiangDef/7)+1;
            if (((maks*7)-shiftSiangDef)>=sisa) maks--;
            assignDokter(&counter_siang, &shiftSiang, siang, current_hari, 1, maks, sisa);
        }
        // Assign shift malam
        if (counter_malam>0) {
            int maks = (shiftMalamDef/7)+1;
            if (((maks*7)-shiftMalamDef)>=sisa) maks--;
            assignDokter(&counter_malam, &shiftMalam, malam, current_hari, 2, maks, sisa);
        }
        sisa-=1;
        // Jika sudah seminggu lakukan reset
        if (current_hari->tanggal==7 || current_hari->tanggal==14 || current_hari->tanggal==21 || current_hari->tanggal==28) {
            counter_pagi = counter_pagiDef;
            counter_siang = counter_siangDef;
            counter_malam = counter_malamDef;
            salinArray(pagiDef, pagi, counter_pagi);
            salinArray(siangDef, siang, counter_siang);
            salinArray(malamDef, malam, counter_malam);
            shiftPagi=shiftPagiDef;
            shiftSiang=shiftSiangDef;
            shiftMalam=shiftMalamDef;
            sisa=7;
        }
        current_hari=current_hari->next;
    }
    //==========================================================================================================================================================
}

int main () {
    buatJadwal();
    // Menampilkan Jadwal
    int pelanggaran=0;
    hari *current_hari = head_hari;
    while (current_hari!=NULL) {
        printf("\n\nTanggal\t: %d", current_hari->tanggal);
        printf("\nPagi\t: ");
        if (current_hari->pagi[0] != NULL) {
            for (int i=0;i<5;i++) {
                if (current_hari->pagi[i] != NULL) {
                    printf("%s\t", current_hari->pagi[i]->nama);
                    if (!(current_hari->pagi[i]->preferensi == 0 || current_hari->pagi[i]->preferensi == 3 || current_hari->pagi[i]->preferensi == 4 || current_hari->pagi[i]->preferensi == 6)) pelanggaran++;
                }
            }
        } 
        else {
            printf("[Belum diassign]");
        }
        printf("\nSiang\t: ");
        if (current_hari->siang[0] != NULL) {
            for (int i=0;i<5;i++) {
                if (current_hari->siang[i] != NULL) {
                    printf("%s\t", current_hari->siang[i]->nama);
                    if (!(current_hari->siang[i]->preferensi == 1 || current_hari->siang[i]->preferensi == 3 || current_hari->siang[i]->preferensi == 5 || current_hari->siang[i]->preferensi == 6)) pelanggaran++;
                }
            }
        } 
        else {
            printf("[Belum diassign]");
        }
        printf("\nMalam\t: ");
        if (current_hari->malam[0] != NULL) {
            for (int i=0;i<5;i++) {
                if (current_hari->malam[i] != NULL) {
                    printf("%s\t", current_hari->malam[i]->nama);
                    if (!(current_hari->malam[i]->preferensi == 2 || current_hari->malam[i]->preferensi == 4 || current_hari->malam[i]->preferensi == 5 || current_hari->malam[i]->preferensi == 6)) pelanggaran++;
                }
            }
        } 
        else {
            printf("[Belum diassign]");
        }
        current_hari=current_hari->next;
    }

    printf("\n\nPelanggaran\t: %d", pelanggaran);
    return 0;
}
