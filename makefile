#Position window in a specific location each time
WindowX=-1
WindowY=-1

SOURCE=./src/*


IDIR=./lib/glew/include -I./lib/glew/src  -I./lib/glfw/include -I./lib/glm -I./headers
CC=g++
CFLAGS=-I$(IDIR)

ODIR=objs

LIBS=-lm

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

compile:
	make test -B

test: 
	g++  $(SOURCE) ./lib/glew/src/glew.c -o $@ $^ $(CFLAGS) $(LIBS) -arch i386 -framework QuartzCore -framework IOKit -framework OpenGL -framework Cocoa -L./lib -lglfw3 -L/Library/Frameworks -w
	./test $(WindowX) $(WindowY)

