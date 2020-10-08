
common_SRC=src/common.c
common_OBJ=bin/common.o

common_ARCHIVE=$(PROJ_PATH)/common/bin/common.a

OBJS=$(common_OBJ)

$(common_OBJ): $(common_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS)

all: $(OBJS)
	@echo "building common"
	ar rcs $(common_ARCHIVE) $(OBJS)


.PHONY: clean

clean:
	rm -f $(common_ARCHIVE) $(OBJS)
