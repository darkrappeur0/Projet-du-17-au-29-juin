CFILES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(CFILES))
COMPILER_FLAGS = -lSDL2 -lSDL_image -lSDL2_ttf -lm -g -Wall -Wextra -Wshadow -Werror
LD_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm

all: Wizard

%.o: %.c $(HEADERS)
	gcc $(COMPILER_FLAGS) -c $<

Wizard: $(OBJECTS) $(HEADERS)
	gcc -o Wizard $(OBJECTS) $(LD_FLAGS)

clean:
	-rm *.o Wizard