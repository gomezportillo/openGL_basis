CC = gcc
LDLIBS = -lGL -lGLU -lglut
TARGETS= planetarium robots

all: $(TARGETS)

clean:
	rm -f *.o *~ $(TARGETS)
