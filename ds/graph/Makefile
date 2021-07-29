graph_SRC=graph.c
graph_OBJ=graph.o

OBJS=$(graph_OBJ)

all: $(OBJS)

$(graph_OBJ): $(graph_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS) 


.PHONY: clean

clean:
	rm -rf $(graph_ARCHIVE) $(OBJS)
