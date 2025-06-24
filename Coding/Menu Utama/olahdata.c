#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "Data_Dokter.csv"

typedef struct {
    int no;
    char nama[50];
    int maksShift;
    int prefShift;
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
            &data[jumlah].no, 
            data[jumlah].nama, 
            &data[jumlah].maksShift, 
            &data[jumlah].prefShift);
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

    fprintf(file, "No;Nama;MaksimalShift;PreferensiShift\n");
    for (int i = 0; i < jumlah; i++) {
        fprintf(file, "%d;%s;%d;%d\n",
                data[i].no, data[i].nama,
                data[i].maksShift, data[i].prefShift);
    }

    fclose(file);
}

// Menampilkan daftar dokter
void tampilkanData() {
    printf("\n=== Daftar Dokter ===\n");
    printf("No\tNama\t\tMaksimalShift\tPreferensiShift\n");
    for (int i = 0; i < jumlah; i++) {
        printf("%d\t%-15s\t%d\t\t%d\n",
               data[i].no,
               data[i].nama,
               data[i].maksShift,
               data[i].prefShift);
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

    printf("Masukkan maksimal shift per minggu [1-21]: ");
    scanf("%d", &data[jumlah].maksShift);

    printf(
        "Masukkan preferensi shift (0–6):\n"
        "Pagi = 0\nSiang = 1\nMalam = 2\n"
        "Pagi Siang = 3\nPagi Malam = 4\nSiang Malam = 5\n"
        "Waktu Bebas = 6\nPilihan: "
    );
    scanf("%d", &data[jumlah].prefShift);

    if (data[jumlah].prefShift < 0 || data[jumlah].prefShift > 6) {
        printf("Input preferensi tidak valid. Dokter tidak ditambahkan.\n");
        return;
    }

    data[jumlah].no = jumlah + 1;
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

    // Update ulang no agar tetap terurut
    for (int i = 0; i < jumlah; i++) {
        data[i].no = i + 1;
    }

    simpanFile();
    printf("Data dokter \"%s\" berhasil dihapus.\n", nama);
}
