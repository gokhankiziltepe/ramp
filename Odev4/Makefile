CC=g++
CFLAGS= -Wall 
LDFLAGS= -lGLEW -lGL -lSOIL -lGLU -lglut -lassimp
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ramp

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@
