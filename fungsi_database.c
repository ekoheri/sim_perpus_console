#include <stdio.h>
#include <string.h>
#include "fungsi_database.h"

int search_data_buku(const char *kode, char *judul, char *penerbit) {
    FILE *file = fopen(DATABASE_BUKU, "r");
    if (!file) return 0; // File tidak bisa dibuka

    char line[128], kodeFile[16], judulFile[64], penerbitFile[64];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%[^|]|%[^\n]", kodeFile, judulFile, penerbitFile);
        if (strcmp(kode, kodeFile) == 0) {
            strcpy(judul, judulFile);
            strcpy(penerbit, penerbitFile);
            fclose(file);
            return 1; // Data ditemukan
        }
    }

    fclose(file);
    return 0; // Data tidak ditemukan
}

int add_data_buku(const char *kode, const char *judul, const char *penerbit) {
    FILE *file = fopen(DATABASE_BUKU, "a");
    if (file) {
        fprintf(file, "%s|%s|%s\n", kode, judul, penerbit);
        fclose(file);
        return 1;
    } else return 0;
}

int update_data_buku(const char *kode, const char *judul, const char *penerbit) {
    FILE *file = fopen(DATABASE_BUKU, "r");
    FILE *temp = fopen("temp.txt", "w");

    char line[128], kodeFile[16], judulFile[64], penerbitFile[64];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%[^|]|%[^\n]", kodeFile, judulFile, penerbitFile);
        if (strcmp(kode, kodeFile) == 0) {
            fprintf(temp, "%s|%s|%s\n", kode, judul, penerbit);
            found = 1;
        } else {
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);
    if (found) {
        remove(DATABASE_BUKU);
        rename("temp.txt", DATABASE_BUKU);
        return 1;
    } else {
        remove("temp.txt");
        return 0;
    }
}

int delete_data_buku(const char *kode) {
    FILE *file = fopen(DATABASE_BUKU, "r");
    FILE *temp = fopen("temp.txt", "w");

    char line[128], kodeFile[16], judulFile[64], penerbitFile[64];
    int found = 0;

    if (file && temp) {
        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%[^|]|%[^|]|%[^\n]", kodeFile, judulFile, penerbitFile);
            
            if (strcmp(kode, kodeFile) == 0) {
                found = 1;  // Tandai bahwa data ditemukan dan tidak disalin
            } else {
                fprintf(temp, "%s", line);
            }
        }
        fclose(file);
        fclose(temp);

        if (found) {
            remove(DATABASE_BUKU);
            rename("temp.txt", DATABASE_BUKU);
            return 1;
        } else {
            remove("temp.txt");
            return 0;
        }
    } else return 0;
}

int read_data_buku(char data[MAX_LINES][MAX_LENGTH]) {
    int total_lines = 0;
    FILE *file = fopen(DATABASE_BUKU, "r");
    if (!file) {
        perror("Gagal membuka buku.txt");
        return 0;
    }

    while (fgets(data[total_lines], MAX_LENGTH, file) && total_lines < MAX_LINES) {
        data[total_lines][strcspn(data[total_lines], "\n")] = 0; 
        total_lines++;
    }
    fclose(file);
    return total_lines;
}

int search_data_anggota(const char *ID, char *nama, char *alamat) {
    FILE *file = fopen(DATABASE_ANGGOTA, "r");
    if (!file) return 0; // File tidak bisa dibuka

    char line[128], IDFile[16], namaFile[64], alamatFile[64];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%[^|]|%[^\n]", IDFile, namaFile, alamatFile);
        if (strcmp(ID, IDFile) == 0) {
            strcpy(nama, namaFile);
            strcpy(alamat, alamatFile);
            fclose(file);
            return 1; // Data ditemukan
        }
    }

    fclose(file);
    return 0; // Data tidak ditemukan
}

int read_data_anggota(char data[MAX_LINES][MAX_LENGTH]) {
    int total_lines = 0;
    FILE *file = fopen(DATABASE_ANGGOTA, "r");
    if (!file) {
        perror("Gagal membuka anggota.txt");
        return 0;
    }

    while (fgets(data[total_lines], MAX_LENGTH, file) && total_lines < MAX_LINES) {
        data[total_lines][strcspn(data[total_lines], "\n")] = 0; 
        total_lines++;
    }
    fclose(file);
    return total_lines;
}
