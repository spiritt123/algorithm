
CC = g++ 
CFLAGS = -c -Wall 
LDFLAGS = 
INCLUDE = include \
            -I../matrix/include \
            -I../slau/include

SRC = main least_squares_method
STATIC_LIBS = ../matrix/matrix.a ../slau/slau.a
SOURCES = $(addsuffix .cpp, $(addprefix src/, $(SRC))) $(STATIC_LIBS)
OBJECTS = $(SOURCES:.cpp=.o) 
EXECUTABLE = out

main: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS) 	
	$(CC) $(OBJECTS) -o $@ -DSFML_STATIC \
		-Iinclude

%.o: %.cpp 	
	g++ -c -o $@ $< -I$(INCLUDE)


clear: 	
	rm -f src/*.o $(EXECUTABLE) 


