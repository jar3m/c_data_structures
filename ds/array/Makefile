array_SRC=array.c
array_OBJ=array.o

OBJS=$(array_OBJ)

all: $(OBJS)

$(array_OBJ): $(array_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS) 


.PHONY: clean

clean:
	rm -rf $(array_ARCHIVE) $(OBJS)
