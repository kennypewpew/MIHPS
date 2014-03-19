CC=gcc
MAIN=main_both.c
LIB=mesh_functions.c A_shortest_path.c shortest_path.c
IFLAGS = -I./ -g
SIZE=-DSIZE=
RN=-DRUN=

all:
	$(CC) $(MAIN) $(LIB) $(IFLAGS) -o both $(SIZE)20 $(RN)30
	./both
	$(CC) $(MAIN) $(LIB) $(IFLAGS) -o both $(SIZE)70 $(RN)30
	./both
	$(CC) $(MAIN) $(LIB) $(IFLAGS) -o both $(SIZE)100 $(RN)20
	./both
	$(CC) $(MAIN) $(LIB) $(IFLAGS) -o both $(SIZE)300 $(RN)10
	./both
	$(CC) $(MAIN) $(LIB) $(IFLAGS) -o both $(SIZE)700 $(RN)5
	./both
	$(CC) $(MAIN) $(LIB) $(IFLAGS) -o both $(SIZE)1000 $(RN)5
	./both
	$(CC) $(MAIN) $(LIB) $(IFLAGS) -o both $(SIZE)3000 $(RN)3
	./both
	$(CC) $(MAIN) $(LIB) $(IFLAGS) -o both $(SIZE)7000 $(RN)2
	./both
	$(CC) $(MAIN) $(LIB) $(IFLAGS) -o both $(SIZE)10000 $(RN)1
	./both


clean:
	rm both
	rm *.vtk
