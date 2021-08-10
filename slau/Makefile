
CC = g++ 
CFLAGS = -c -Wall 
LDFLAGS = 
INCLUDE = include 
MATRIX_INCLUDE = ../matrix/include

SRC = main slau
SOURCES = $(addsuffix .cpp, $(addprefix src/, $(SRC))) ../matrix/matrix.a 
OBJECTS = $(SOURCES:.cpp=.o) 
EXECUTABLE = out

main: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS) 	
	$(CC) $(OBJECTS) -o $@ -DSFML_STATIC \
		-Iinclude

%.o: %.cpp 	
	g++ -c -o $@ $< -I$(INCLUDE) -I$(MATRIX_INCLUDE)


clear: 	
	rm -f src/*.o $(EXECUTABLE) 


