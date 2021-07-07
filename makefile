CXX = gcc

SRC = example.c ringbuf.c
OBJ = $(SRC:.c=.o)
EXEC = example.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(OBJ) 

clean:
	rm $(OBJ) $(EXEC)