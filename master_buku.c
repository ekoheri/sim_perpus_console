#include <newt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fungsi_tampilan.h"
#include "fungsi_database.h"
#include "master_buku.h"

/*
===========================================
FORM ENTRY
===========================================
*/
void entry_master_buku() {
    newtComponent form, labelKode, inputKode, labelJudul, inputJudul, labelPenerbit, inputPenerbit;
    newtComponent simpanButton, hapusButton, clearButton, exitButton, msgLabel;
    
    int formWidth = 60, formHeight = 14;
    int data_lama = 0;
    int startX, startY;
    getCenteredPosition(formWidth, formHeight, &startX, &startY);

    // LOOP PERTAMA: Menjaga agar form bisa dibuka kembali setelah ditutup
    while (1) {
        newtCls();
        newtOpenWindow(startX, startY, formWidth, formHeight, "Form Entry Data");

        labelKode = newtLabel(2, 1, "Kode:");
        inputKode = newtEntry(11, 1, "", 10, NULL, NEWT_FLAG_RETURNEXIT);

        labelJudul = newtLabel(2, 3, "judul:");
        inputJudul = newtEntry(11, 3, "", 40, NULL, 0);

        labelPenerbit = newtLabel(2, 5, "penerbit:");
        inputPenerbit = newtEntry(11, 5, "", 30, NULL, 0);

        simpanButton = newtButton(2, 9, "Simpan");
        hapusButton = newtButton(14, 9, "Hapus");

        clearButton = newtButton(36, 9, "Clear");
        exitButton = newtButton(47, 9, "Keluar");
         // **Nonaktifkan tombol hapus jika data tidak ada**
        newtComponentTakesFocus(hapusButton, 0);

        msgLabel = newtLabel(2, 7, " "); // Label untuk pesan

        form = newtForm(NULL, NULL, 0);
        newtFormAddComponents(form, labelKode, inputKode, labelJudul, inputJudul,
                              labelPenerbit, inputPenerbit, msgLabel, simpanButton, 
                              hapusButton, clearButton, exitButton, NULL);

        struct newtExitStruct exitStruct;

        // LOOP KEDUA: Menangani input pengguna (Enter, Simpan, Keluar)
        while (1) {
            newtFormRun(form, &exitStruct);

            // Jika Enter ditekan pada inputKode, cari data dan pindah ke inputJudul
            if (exitStruct.u.co == inputKode) {
                const char *kode = newtEntryGetValue(inputKode);
                char judul[64] = "", penerbit[64] = "";

                if (search_data_buku(kode, judul, penerbit)) {
                    newtEntrySet(inputJudul, judul, 1);
                    newtEntrySet(inputPenerbit, penerbit, 1);
                    newtLabelSetText(msgLabel, "Data ditemukan.");
                    // **Aktifkan tombol hapus jika data ditemukan**
                    newtComponentTakesFocus(hapusButton, 1);
                    data_lama = 1;
                } else {
                    newtEntrySet(inputJudul, "", 1);
                    newtEntrySet(inputPenerbit, "", 1);
                    newtLabelSetText(msgLabel, "");
                    // **Nonaktifkan tombol hapus jika data tidak ada**
                    newtComponentTakesFocus(hapusButton, 0);
                    data_lama = 0;
                }

                newtRefresh();
                
                // **Pindahkan fokus ke inputJudul**
                newtFormSetCurrent(form, inputJudul);
                continue; 
            } 
            else if (exitStruct.u.co == simpanButton) {
                const char *kode = newtEntryGetValue(inputKode);
                const char *judul = newtEntryGetValue(inputJudul);
                const char *penerbit = newtEntryGetValue(inputPenerbit);

                if(data_lama == 0) {
                    if(add_data_buku(kode, judul, penerbit) == 1)
                        newtLabelSetText(msgLabel, "Simpan data sukses!");
                    else
                        newtLabelSetText(msgLabel, "Gagal menyimpan data!");
                } else {
                    if(update_data_buku(kode, judul, penerbit) == 1) 
                        newtLabelSetText(msgLabel, "Data berhasil diubah!");
                    else
                        newtLabelSetText(msgLabel, "Data tidak ditemukan!");
                }
                
                // Kosongkan input setelah update
                newtEntrySet(inputKode, "", 1);
                newtEntrySet(inputJudul, "", 1);
                newtEntrySet(inputPenerbit, "", 1);
                newtLabelSetText(msgLabel, "");
                // **Nonaktifkan tombol hapus jika data tidak ada**
                newtComponentTakesFocus(hapusButton, 0);
                newtFormSetCurrent(form, inputKode);
                data_lama = 0;
            } else if(exitStruct.u.co == hapusButton) {
                const char *kode = newtEntryGetValue(inputKode);
    
                if(delete_data_buku(kode) == 1)
                    newtLabelSetText(msgLabel, "Data berhasil dihapus!");
                else
                    newtLabelSetText(msgLabel, "GAGAL menghapus data!");

                // Kosongkan input setelah penghapusan
                newtEntrySet(inputKode, "", 1);
                newtEntrySet(inputJudul, "", 1);
                newtEntrySet(inputPenerbit, "", 1);
                newtLabelSetText(msgLabel, "");
                // **Nonaktifkan tombol hapus jika data tidak ada**
                newtComponentTakesFocus(hapusButton, 0);
                newtFormSetCurrent(form, inputKode);
                data_lama = 0;
            }
            else if(exitStruct.u.co == clearButton) {
                newtEntrySet(inputKode, "", 1);
                newtEntrySet(inputJudul, "", 1);
                newtEntrySet(inputPenerbit, "", 1);
                newtLabelSetText(msgLabel, "");
                // **Nonaktifkan tombol hapus jika data tidak ada**
                newtComponentTakesFocus(hapusButton, 0);
                newtFormSetCurrent(form, inputKode);
                data_lama = 0;
            }
            else if (exitStruct.u.co == exitButton) {
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
/*
==============================================
FUNGSI LAPORAN BUKU
==============================================
*/

void display_page_buku(
    newtComponent textArea, 
    char data[MAX_LINES][MAX_LENGTH], 
    int page, 
    int total_lines) {

    char content[MAX_LINES * MAX_LENGTH] = "";
    strcat(content, "╔══════╦════════════════════════╦════════════════════╗\n");
    strcat(content, "║ Kode ║ Judul                  ║ Penerbit           ║\n");
    strcat(content, "╠══════╬════════════════════════╬════════════════════╣\n");

    int start = page * ROWS_PER_PAGE;
    int end = start + ROWS_PER_PAGE;
    if (end > total_lines) end = total_lines;

    for (int i = start; i < end; i++) {
        char kode[10], judul[22], penerbit[20];
        sscanf(data[i], "%[^|]|%[^|]|%[^|]", kode, judul, penerbit);


        char row[MAX_LENGTH];
        snprintf(row, sizeof(row), "║ %-4s ║ %-22s ║ %-18s ║\n", kode, judul, penerbit);
        strcat(content, row);
    }

    strcat(content, "╚══════╩════════════════════════╩════════════════════╝\n");

    newtTextboxSetText(textArea, content);
}

void laporan_master_buku() {
    newtComponent form, textArea, backButton, nextButton, prevButton;
    char data[MAX_LINES][MAX_LENGTH];
    int total_lines = read_data_buku(data);
    int current_page = 0;

    int formWidth = 60; 
    int formHeight = 20;
    int startX, startY;
    getCenteredPosition(formWidth, formHeight, &startX, &startY);

    while (1) {
        // Bersihkan layar sebelum menampilkan form
        newtCls();

        newtOpenWindow(startX, startY, formWidth, formHeight, "Laporan Buku");

        textArea = newtTextbox(2, 1, 55, 12, NEWT_FLAG_WRAP);
        backButton = newtButton(25, 16, "Kembali");
        nextButton = newtButton(40, 16, "Next");
        prevButton = newtButton(10, 16, "Prev");

        form = newtForm(NULL, NULL, 0);
        newtFormAddComponents(form, textArea, backButton, NULL);

        if (current_page > 0) {
            newtFormAddComponent(form, prevButton);
        }
        if ((current_page + 1) * ROWS_PER_PAGE < total_lines) {
            newtFormAddComponent(form, nextButton);
        }

        display_page_buku(textArea, data, current_page, total_lines);

        struct newtExitStruct es;
        newtFormRun(form, &es);

        if (es.u.co == nextButton) {
            current_page++;
        } else if (es.u.co == prevButton) {
            current_page--;
        } else {
            break; 
        }

        newtFormDestroy(form);
        newtPopWindow();
    }

    newtFormDestroy(form);
    newtPopWindow();
}

void menu_master_buku() {
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
        newtOpenWindow(startX, startY, formWidth, formHeight, "Master Data Buku");

        // Komponen menu
        newtComponent menuLabel = newtLabel(5, 1, "Pilih Menu:");
        newtComponent listbox = newtListbox(5, 2, 4, NEWT_FLAG_HIDDEN | NEWT_FLAG_RETURNEXIT);
        newtComponent exitButton = newtButton(5, 8, "Keluar");

        // Tambahkan item ke listbox
        newtListboxAppendEntry(listbox, "1. Entry Buku", (void *)"entry");
        newtListboxAppendEntry(listbox, "2. Laporan Buku", (void *)"laporan");

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
                entry_master_buku();  // Panggil form entry
             } else if (strcmp(choice, "laporan") == 0) {
                laporan_master_buku();
             }
        }
        newtFormDestroy(form);
        newtPopWindow();  // Hapus jendela menu sebelum menggambar ulang
    }//end while
}