CFILES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c,%.o,$(CFILES))
COMPILER_FLAGS = -lSDL2 -lm -lSDL2_image -Wall -Wextra -Wshadow -Werror -g
LD_FLAGS = -lSDL2 -lm -lSDL2_image

all: PaveSerpent Xfenetre SpriteAnim

%.o: %.c $(HEADERS)
	gcc $(COMPILER_FLAGS) -c $<

PaveSerpent: PaulTournaireProjetPaveSerpent.o $(HEADERS)
	gcc -o PaveSerpent PaulTournaireProjetPaveSerpent.o $(LD_FLAGS) 

Xfenetre: PaulTournaireProjetXfenetre.o $(HEADERS)
	gcc -o Xfenetre PaulTournaireProjetXfenetre.o $(LD_FLAGS)

SpriteAnim: PaulTournaireProjetSpriteAnim.o $(HEADERS)
	gcc -o SpriteAnim PaulTournaireProjetSpriteAnim.o $(sdl2-config --cflags) $(LD_FLAGS)

clean:
	-rm *.o PaveSerpent Xfenetre SpriteAnim