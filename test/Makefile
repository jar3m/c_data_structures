

INCLUDES += -I $(PROJ_PATH)/test/inc/
INCLUDES += -I $(PROJ_PATH)/ds/link_list/
INCLUDES += -I $(PROJ_PATH)/ds/stack/
INCLUDES += -I $(PROJ_PATH)/ds/queue/
INCLUDES += -I $(PROJ_PATH)/ds/heap/
INCLUDES += -I $(PROJ_PATH)/ds/tree/
INCLUDES += -I $(PROJ_PATH)/ds/graph/
INCLUDES += -I $(PROJ_PATH)/ds/array/
INCLUDES += -I $(PROJ_PATH)/ds/disjoint_set/
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
