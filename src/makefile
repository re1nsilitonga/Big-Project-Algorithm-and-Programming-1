CC = gcc
CFLAGS = -Iheader -Ic
SRC = c/auth.c c/denah.c c/exit.c c/linkedlist.c c/listdin.c c/load.c c/map.c c/lihat.c c/minum.c c/pasien.c c/queue.c c/save.c c/set.c c/stack.c c/user.c c/cariuser.c c/ngobatin.c c/daftarcheckup.c c/diagnosis.c c/pulangdok.c main.c
OBJ = $(SRC:.c=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

# Rule untuk meng-compile .c menjadi .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f c/*.o *.o $(EXEC)
