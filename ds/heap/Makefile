heap_SRC=heap.c
heap_OBJ=heap.o

OBJS=$(heap_OBJ)

all: $(OBJS)

$(heap_OBJ): $(heap_SRC)
	$(CC) $(INCLUDES) -c $^ $(CFLAGS) 


.PHONY: clean

clean:
	rm -rf $(heap_ARCHIVE) $(OBJS)
