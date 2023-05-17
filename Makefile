CFLAGS = -g -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lSDL2_mixer -lm

INC = sdl2-light.h sdl2-ttf-light.h constante.h logique.h graphique.h
SRC = main.c sdl2-light.c sdl2-ttf-light.c logique.c graphique.c
OBJ = $(SRC:%.c=%.o)

SRC2 = tests.c sdl2-light.c logique.c graphique.c
OBJ2 = $(SRC2:%.c=%.o)

PROG = spacecorridor
PROG2 = tests

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

spacecorridor: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

tests: $(OBJ2)
	gcc $(CFLAGS) $(OBJ2) $(LDFLAGS) -o $@

doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG)
	rm -f *~ *.o $(PROG2)
	rm -rf latex html