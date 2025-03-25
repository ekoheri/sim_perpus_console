#ifndef FUNGSI_DATABASE
#define FUNGSI_DATABASE

#define DATABASE_BUKU "buku.txt"
#define DATABASE_ANGGOTA "anggota.txt"

#define MAX_LINES 100   
#define MAX_LENGTH 256  
#define ROWS_PER_PAGE 5 

int search_data_buku(const char *kode, char *judul, char *penerbit);
int add_data_buku(const char *kode, const char *judul, const char *penerbit);
int update_data_buku(const char *kode, const char *judul, const char *penerbit);
int delete_data_buku(const char *kode);
int read_data_buku(char data[MAX_LINES][MAX_LENGTH]);

int search_data_anggota(const char *ID, char *nama, char *alamat);
int read_data_anggota(char data[MAX_LINES][MAX_LENGTH]);
#endif