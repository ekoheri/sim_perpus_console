CC = gcc
CFLAGS = -Wall
LIBS = -lnewt

TARGET = sim_perpus
SRC = sim_perpus.c master_buku.c master_anggota.c trans_pinjam.c fungsi_tampilan.c fungsi_database.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)