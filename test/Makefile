

INCLUDES += -I $(PROJ_PATH)/test/inc/
INCLUDES += -I $(PROJ_PATH)/ds/link_list/
export

CFLAGS += -g -Wall 

test_SRC=src/test.c
test_OBJ=bin/test.o

test_ARCHIVE=$(PROJ_PATH)/test/bin/test.a

OBJS=$(test_OBJ)

$(test_OBJ): $(test_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS)

all: $(OBJS)
	ar rcs $(test_ARCHIVE) $(OBJS)
	rm -f  $(OBJS)


.PHONY: clean

clean:
	rm -f $(test_ARCHIVE) $(OBJS)
