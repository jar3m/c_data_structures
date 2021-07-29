disjoint_set_SRC=disjoint_set.c
disjoint_set_OBJ=disjoint_set.o

OBJS=$(disjoint_set_OBJ)

all: $(OBJS)

$(disjoint_set_OBJ): $(disjoint_set_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS) 


.PHONY: clean

clean:
	rm -rf $(disjoint_set_ARCHIVE) $(OBJS)
