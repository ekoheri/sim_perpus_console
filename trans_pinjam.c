#include <newt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "fungsi_tampilan.h"
#include "fungsi_database.h"
#include "trans_pinjam.h"

/*
===========================================
FORM ENTRY
===========================================
*/

void get_tanggal_transaksi(char *tanggal_pinjam, char *tanggal_kembali) {
    // Ambil tanggal sistem
    // Format: YYYY-MM-DD
    char tgl_pinjam[11]; 
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(tgl_pinjam, sizeof(tgl_pinjam), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    strcpy(tanggal_pinjam, tgl_pinjam);

    char tgl_kembali[11];
    tm.tm_mday += 7; // Tambah 7 hari
    mktime(&tm); // Pastikan perubahan diterapkan
    snprintf(tgl_kembali, sizeof(tgl_kembali), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    strcpy(tanggal_kembali, tgl_kembali);
}

void entry_trans_pinjam() {
    newtComponent form, 
    labelKodePinjam, inputKodePinjam, 
    labelTglPinjam, inputTglPinjam, 
    labelTglKembali, inputTglKembali, 
    labelKodeBuku, inputKodeBuku, 
    labelJudul, inputJudul,
    labelIDAnggota, inputIDAnggota, 
    labelNama, inputNama;
    newtComponent simpanButton, clearButton, exitButton, msgLabel;
    
    int formWidth = 60, formHeight = 21;
    int startX, startY;
    getCenteredPosition(formWidth, formHeight, &startX, &startY);

    // LOOP PERTAMA: Menjaga agar form bisa dibuka kembali setelah ditutup
    while (1) {
        newtCls();
        newtOpenWindow(startX, startY, formWidth, formHeight, "Form Entry Pinjam");

        labelKodePinjam = newtLabel(2, 1, "Kode Pinjam:");
        inputKodePinjam = newtEntry(15, 1, "", 10, NULL, NEWT_FLAG_RETURNEXIT);
        
        char tanggal_pinjam[11];
        char tanggal_kembali[11];
        get_tanggal_transaksi(tanggal_pinjam, tanggal_kembali);

        labelTglPinjam = newtLabel(2, 3, "Tgl Pinjam:");
        inputTglPinjam = newtEntry(15, 3, tanggal_pinjam, 13, NULL, NEWT_FLAG_DISABLED);

        labelTglKembali = newtLabel(2, 5, "Tgl Kembali:");
        inputTglKembali = newtEntry(15, 5, tanggal_kembali, 13, NULL, NEWT_FLAG_DISABLED);

        labelKodeBuku = newtLabel(2, 7, "Kode Buku:");
        inputKodeBuku = newtEntry(15, 7, "", 10, NULL, NEWT_FLAG_RETURNEXIT);

        labelJudul = newtLabel(2, 9, "Judul Buku:");
        inputJudul = newtEntry(15, 9, "", 40, NULL, NEWT_FLAG_DISABLED);

        labelIDAnggota = newtLabel(2, 11, "ID Anggota:");
        inputIDAnggota = newtEntry(15, 11, "", 10, NULL, NEWT_FLAG_RETURNEXIT);

        labelNama = newtLabel(2, 13, "Nama:");
        inputNama = newtEntry(15, 13, "", 40, NULL, NEWT_FLAG_DISABLED);

        simpanButton = newtButton(2, 17, "Simpan");
        clearButton = newtButton(36, 17, "Clear");
        exitButton = newtButton(47, 17, "Keluar");

        msgLabel = newtLabel(2, 15, " "); // Label untuk pesan

        form = newtForm(NULL, NULL, 0);
        newtFormAddComponents(form, labelKodePinjam, inputKodePinjam, labelTglPinjam, 
        inputTglPinjam, labelTglKembali, inputTglKembali, labelKodeBuku, 
        inputKodeBuku, labelJudul, inputJudul,labelIDAnggota, inputIDAnggota, 
        labelNama, inputNama, msgLabel, simpanButton, clearButton, exitButton, NULL);

        struct newtExitStruct exitStruct;

        // LOOP KEDUA: Menangani input pengguna (Enter, Simpan, Keluar)
        while (1) {
            newtFormRun(form, &exitStruct);

            // Jika Enter ditekan pada inputKode, cari data dan pindah ke inputJudul
            if (exitStruct.u.co == inputKodePinjam) {
                newtFormSetCurrent(form, inputKodeBuku);
                newtRefresh();
                continue; 
            } else if (exitStruct.u.co == inputKodeBuku) {
                const char *kode = newtEntryGetValue(inputKodeBuku);
                char judul[64] = ""; char penerbit[64] = "";
                if (search_data_buku(kode, judul, penerbit)) {
                    newtEntrySet(inputJudul, judul, 1);
                    newtFormSetCurrent(form, inputIDAnggota);
                } else {
                    newtEntrySet(inputJudul, "", 1);
                    newtFormSetCurrent(form, inputKodeBuku);
                }
                newtRefresh();
                continue; 
            } else if (exitStruct.u.co == inputIDAnggota) {
                const char *ID = newtEntryGetValue(inputIDAnggota);
                char nama[64] = ""; char alamat[64] = "";
                if (search_data_anggota(ID, nama, alamat)) {
                    newtEntrySet(inputNama, nama, 1);
                    newtFormSetCurrent(form, simpanButton);
                } else {
                    newtEntrySet(inputNama, "", 1);
                    newtFormSetCurrent(form, inputIDAnggota);
                }
                newtRefresh();
                continue; 
            } else if(exitStruct.u.co == clearButton) {
                newtEntrySet(inputKodePinjam, "", 1);
                char tanggal_pinjam[11];
                char tanggal_kembali[11];
                get_tanggal_transaksi(tanggal_pinjam, tanggal_kembali);
                newtEntrySet(inputTglPinjam, tanggal_pinjam, 1);
                newtEntrySet(inputTglKembali, tanggal_kembali, 1);
                newtEntrySet(inputKodeBuku, "", 1);
                newtEntrySet(inputJudul, "", 1);
                newtEntrySet(inputIDAnggota, "", 1);
                newtEntrySet(inputNama, "", 1);
                newtLabelSetText(msgLabel, "");
                newtFormSetCurrent(form, inputKodePinjam);
            } else if (exitStruct.u.co == exitButton) {
                // **Perbaikan utama: Hentikan semua loop dan keluar dari form**
                newtFormDestroy(form);
                newtPopWindow();
                return; // **Langsung keluar dari fungsi**
            }
        }

        newtPopWindow();
        newtRefresh();
    }
}

void menu_trans_pinjam() {
    // Ukuran form
    int formWidth = 40;
    int formHeight = 12;

    int startX, startY;
    getCenteredPosition(formWidth, formHeight, &startX, &startY);

    // Event handler
    struct newtExitStruct exitStruct;
    while (1) {
        newtCls();
        // Buat jendela menu di tengah layar
        newtOpenWindow(startX, startY, formWidth, formHeight, "Transaksi Peminjaman");

        // Komponen menu
        newtComponent menuLabel = newtLabel(5, 1, "Pilih Menu:");
        newtComponent listbox = newtListbox(5, 2, 4, NEWT_FLAG_HIDDEN | NEWT_FLAG_RETURNEXIT);
        newtComponent exitButton = newtButton(5, 8, "Keluar");

        // Tambahkan item ke listbox
        newtListboxAppendEntry(listbox, "1. Entry Peminjaman", (void *)"entry");
        newtListboxAppendEntry(listbox, "2. Laporan Peminjaman", (void *)"laporan");

        // Form dengan tombol Keluar
        newtComponent form = newtForm(NULL, NULL, 0);
        newtFormAddComponents(form, menuLabel, listbox, exitButton, NULL);

        newtFormRun(form, &exitStruct);

        if (exitStruct.u.co == exitButton) {
            // Jika tombol "Keluar" ditekan, keluar dari loop
            break;
        } else {
            const char *choice = newtListboxGetCurrent(listbox);
             if (strcmp(choice, "entry") == 0) {
                entry_trans_pinjam();  // Panggil form entry
             } 
        }
        newtFormDestroy(form);
        newtPopWindow();  // Hapus jendela menu sebelum menggambar ulang
    }//end while
}