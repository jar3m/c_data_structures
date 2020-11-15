link_list_SRC=link_list.c
link_list_OBJ=link_list.o

OBJS=$(link_list_OBJ)


all: $(OBJS)
#	rm -f  $(OBJS)
#	ar rcs $(link_list_ARCHIVE) $(OBJS)

$(link_list_OBJ): $(link_list_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(link_list_ARCHIVE) $(OBJS)
