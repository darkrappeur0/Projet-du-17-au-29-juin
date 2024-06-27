CFILES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(CFILES))
COMPILER_FLAGS = -lSDL2 -lSDL_image -lSDL2_ttf -lm -g -Wall -Wextra -Wshadow -Werror -fsanitize=address,undefined
LD_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm -fsanitize=address,undefined

all: Wizard

%.o: %.c $(HEADERS)
	gcc $(COMPILER_FLAGS) -c $<

Wizard: $(OBJECTS) $(HEADERS)
	gcc -o Wizard $(OBJECTS) $(LD_FLAGS)

clean:
	-rm *.o Wizard