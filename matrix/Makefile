

CC = g++ 
CFLAGS = -c -Wall 
LDFLAGS = 
INCLUDE = include 

SRC = main matrix
SOURCES = $(addsuffix .cpp, $(addprefix src/, $(SRC))) 
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


