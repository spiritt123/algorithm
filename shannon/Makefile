
CC = g++ 
CFLAGS = -c -Wall -std=c++17 
LDFLAGS = 
INCLUDE = include 

SRC = main shannon
SOURCES = $(addsuffix .cpp, $(addprefix src/, $(SRC)))
OBJECTS = $(SOURCES:.cpp=.o) 
EXECUTABLE = out

main: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS) 	
	$(CC) $(OBJECTS) -o $@ -DSFML_STATIC \
		-Iinclude

%.o: %.cpp 	
	$(CC) -c $(CFLAGS) -o $@ $< -I$(INCLUDE) 


clear: 	
	rm -f src/*.o $(EXECUTABLE) 


