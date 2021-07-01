hash_SRC=hash.c
hash_OBJ=hash.o

OBJS=$(hash_OBJ)

all: $(OBJS)

$(hash_OBJ): $(hash_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(hash_ARCHIVE) $(OBJS)
