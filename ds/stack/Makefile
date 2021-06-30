stack_SRC=stack.c
stack_OBJ=stack.o

OBJS=$(stack_OBJ)

all: $(OBJS)

$(stack_OBJ): $(stack_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS) 


.PHONY: clean

clean:
	rm -rf $(stack_ARCHIVE) $(OBJS)
