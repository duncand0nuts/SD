CC = gcc
CFLAGS = -O3

OBJS = Connect4.o CPU_player.o IO.o Game.o Board.o
EXEC = Connect4

SOURCEDIR = src/
INCDIR = include/

exec: $(OBJS) Makefile
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

%.c: $(INCDIR)%.h

%.o: $(SOURCEDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	rm -rf $(OBJS) $(EXEC)


