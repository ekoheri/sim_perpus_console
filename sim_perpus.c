// sudo apt-get install libnewt-dev

#include <newt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fungsi_tampilan.h"
#include "master_buku.h"
#include "master_anggota.h"
#include "trans_pinjam.h"

int main() {
    newtInit();  // Inisialisasi Newt

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
        newtOpenWindow(startX, startY, formWidth, formHeight, "Sistem Informasi Perpustakaan");

        // Komponen menu
        newtComponent menuLabel = newtLabel(5, 1, "Pilih Menu:");
        newtComponent listbox = newtListbox(5, 2, 4, NEWT_FLAG_HIDDEN | NEWT_FLAG_RETURNEXIT);
        newtComponent exitButton = newtButton(5, 8, "Keluar");

        // Tambahkan item ke listbox
        newtListboxAppendEntry(listbox, "1. Master Buku", (void *)"master_buku");
        newtListboxAppendEntry(listbox, "2. Master Anggota", (void *)"master_anggota");
        newtListboxAppendEntry(listbox, "3. Transaksi Pinjam", (void *)"trans_pinjam");
        newtListboxAppendEntry(listbox, "4. Transaksi Kembali", (void *)"trans_kembali");

        // Form dengan tombol Keluar
        newtComponent form = newtForm(NULL, NULL, 0);
        newtFormAddComponents(form, menuLabel, listbox, exitButton, NULL);

        newtFormRun(form, &exitStruct);

        if (exitStruct.u.co == exitButton) {
            // Jika tombol "Keluar" ditekan, keluar dari loop
            break;
        } else {
            const char *choice = newtListboxGetCurrent(listbox);
            if (strcmp(choice, "master_buku") == 0) {
                menu_master_buku();  // Panggil form entry
            } else if (strcmp(choice, "master_anggota") == 0) {
                menu_master_anggota();  // Panggil form entry
            }  else if (strcmp(choice, "trans_pinjam") == 0) {
                menu_trans_pinjam();  // Panggil form entry
            }
        }

        newtFormDestroy(form);
        newtPopWindow();  // Hapus jendela menu sebelum menggambar ulang
    }

    // Bersihkan layar dan keluar
    newtFinished();
    return 0;
}

