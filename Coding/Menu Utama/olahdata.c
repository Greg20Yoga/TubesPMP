#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "Data_Dokter.csv"

typedef struct {
    int id;
    char nama[50];
    int maksShift;
    int preferensi;
} Dokter;

Dokter data[MAX];
int jumlah = 0;

// Fungsi untuk membaca file CSV
void bacaFile() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Gagal membuka file.\n");
        return;
    }

    jumlah = 0;
    char baris[100];
    fgets(baris, sizeof(baris), file); // Skip header

    while (fgets(baris, sizeof(baris), file)) {
        sscanf(baris, "%d;%49[^;];%d;%d", 
            &data[jumlah].id, 
            data[jumlah].nama, 
            &data[jumlah].maksShift, 
            &data[jumlah].preferensi);
        jumlah++;
    }

    fclose(file);
}

// Fungsi untuk menyimpan data ke CSV
void simpanFile() {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Gagal menyimpan file.\n");
        return;
    }

    fprintf(file, "ID;Nama;MaksShift;PreferensiShift\n");
    for (int i = 0; i < jumlah; i++) {
        fprintf(file, "%d;%s;%d;%d\n",
                data[i].id, data[i].nama,
                data[i].maksShift, data[i].preferensi);
    }

    fclose(file);
}

// Menampilkan daftar dokter
void tampilkanData() {
    printf("\n=== Daftar Dokter ===\n");
    printf("ID\tNama\t\tMaksShift\tPreferensiShift\n");
    for (int i = 0; i < jumlah; i++) {
        printf("%d\t%-15s\t%d\t\t%d\n",
               data[i].id,
               data[i].nama,
               data[i].maksShift,
               data[i].preferensi);
    }
}

// Menambahkan data dokter
void tambahDokter() {
    if (jumlah >= MAX) {
        printf("Data penuh.\n");
        return;
    }

    printf("Masukkan nama dokter: ");
    scanf(" %[^\n]", data[jumlah].nama);

    printf("Masukkan maksimal shift per minggu: ");
    scanf("%d", &data[jumlah].maksShift);

    printf(
        "Masukkan preferensi shift (0–6):\n"
        "Pagi = 0\nSiang = 1\nMalem = 2\n"
        "Pagi Siang = 3\nPagi Malem = 4\nSiang Malem = 5\n"
        "Waktu Bebas = 6\nPilihan: "
    );
    scanf("%d", &data[jumlah].preferensi);

    if (data[jumlah].preferensi < 0 || data[jumlah].preferensi > 6) {
        printf("Input preferensi tidak valid. Dokter tidak ditambahkan.\n");
        return;
    }

    data[jumlah].id = jumlah + 1;
    jumlah++;

    simpanFile();
    printf("Data berhasil ditambahkan.\n");
}

// Menghapus dokter berdasarkan nama
void hapusDokter() {
    char nama[50];
    printf("Masukkan nama dokter yang ingin dihapus: ");
    scanf(" %[^\n]", nama);

    int index = -1;
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(data[i].nama, nama) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Dokter tidak ditemukan.\n");
        return;
    }

    for (int i = index; i < jumlah - 1; i++) {
        data[i] = data[i + 1];
    }
    jumlah--;

    // Update ulang ID agar tetap terurut
    for (int i = 0; i < jumlah; i++) {
        data[i].id = i + 1;
    }

    simpanFile();
    printf("Data dokter \"%s\" berhasil dihapus.\n", nama);
}

// Fungsi utama
int main() {
    bacaFile();
    int pilihan;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Tampilkan Daftar Dokter\n");
        printf("2. Tambah Dokter\n");
        printf("3. Hapus Dokter\n");
        printf("4. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tampilkanData();
                break;
            case 2:
                tambahDokter();
                break;
            case 3:
                hapusDokter();
                break;
            case 4:
                printf("Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }

    } while (pilihan != 4);

    return 0;
}
