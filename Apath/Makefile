

CC = g++ 
CFLAGS = -c -Wall 
LDFLAGS = 
INCLUDE = include 

SRC = main
SOURCES = $(addsuffix .cpp, $(addprefix src/, $(SRC))) 
OBJECTS = $(SOURCES:.cpp=.o) 
EXECUTABLE = out

main: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS) 	
	$(CC) $(OBJECTS) -o $@ -DSFML_STATIC \
		-Iinclude -Llib -pthread -lsfml-graphics -lsfml-system -lsfml-window -lsfml-network -lfreetype -lstdc++ 

%.o: %.cpp 	
	g++ -c -o $@ $< -I$(INCLUDE) 

clear: 	
	rm -f src/*.o $(EXECUTABLE) 


