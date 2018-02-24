CC=g++
CFLAGS= -O3 -Wall -c -std=c++11
LIBS += -lgmp -lgmpxx
SOURCES= fraction.cpp fractionUsage.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=fractionUsage

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	-rm -f *.o $(EXECUTABLE) 
