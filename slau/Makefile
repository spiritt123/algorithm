
CC = g++ 
CFLAGS = -c -Wall 
LDFLAGS = 
INCLUDE = include 
INCLUDE_MATRIX = ../matrix/include 

SRC = main slau
STATIC_LIBS = ../matrix/matrix.a
SOURCES = $(addsuffix .cpp, $(addprefix src/, $(SRC))) $(STATIC_LIBS)
OBJECTS = $(SOURCES:.cpp=.o) 
EXECUTABLE = out

main: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS) 	
	$(CC) $(OBJECTS) -o $@ -DSFML_STATIC \
		-Iinclude

%.o: %.cpp 	
	g++ -c -o $@ $< -I$(INCLUDE) -I$(INCLUDE_MATRIX)


clear: 	
	rm -f src/*.o $(EXECUTABLE) 


