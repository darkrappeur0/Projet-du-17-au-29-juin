CFILES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(CFILES))
COMPILER_FLAGS = -lSDL2 -lm -lSDL2_image -Wall -Wextra -Wshadow -Werror -g
LD_FLAGS = -lSDL2 -lm -lSDL2_image

all : topitop_jeu

%.o: %.c $(HEADERS)
	gcc $(COMPILER_FLAGS) -c $<

topitop_jeu: $(OBJECTS) $(HEADERS)
	gcc $(OBJECTS) -o topitop_jeu $(LD_FLAGS) $(sdl2-config --cflags) 

clean:
	-rm *.o topitop_jeu