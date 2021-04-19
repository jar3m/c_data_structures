queue_SRC=queue.c
queue_OBJ=queue.o

OBJS=$(queue_OBJ)

all: $(OBJS)

$(queue_OBJ): $(queue_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS) 


.PHONY: clean

clean:
	rm -rf $(queue_ARCHIVE) $(OBJS)
