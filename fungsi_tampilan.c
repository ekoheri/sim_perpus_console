#include <newt.h>
#include "fungsi_tampilan.h"

// Fungsi untuk menampilkan form entry
void getCenteredPosition(int formWidth, int formHeight, int *startX, int *startY) {
    int termCols, termRows;
    newtGetScreenSize(&termCols, &termRows);
    
    *startX = (termCols - formWidth) / 2;
    *startY = (termRows - formHeight) / 2;
}
