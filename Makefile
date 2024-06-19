CFILES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c,%.o,$(CFILES))
COMPILER_FLAGS = -lSDL2 -lm -Wall -Wextra -Wshadow -Werror -g
LD_FLAGS = -lSDL2 -lm

all: PaveSerpent Xfenetre

%.o: %.c $(HEADERS)
	gcc $(COMPILER_FLAGS) -c $<

PaveSerpent: PaulTournaireProjetPaveSerpent.o $(HEADERS)
	gcc -o PaveSerpent PaulTournaireProjetPaveSerpent.o $(LD_FLAGS) 

Xfenetre: PaulTournaireProjetXfenetre.o $(HEADERS)
	gcc -o Xfenetre PaulTournaireProjetXfenetre.o $(LD_FLAGS) 

clean:
	-rm *.o PaveSerpent Xfenetre