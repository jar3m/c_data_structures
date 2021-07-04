tree_SRC=tree.c
tree_OBJ=tree.o

OBJS=$(tree_OBJ)

all: $(OBJS)

$(tree_OBJ): $(tree_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS) 


.PHONY: clean

clean:
	rm -rf $(tree_ARCHIVE) $(OBJS)
