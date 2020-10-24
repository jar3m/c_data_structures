
common_SRC=src/common.c
common_OBJ=bin/common.o

common_ARCHIVE=$(PROJ_PATH)/common/bin/common.a

logger_SRC=src/logger.c
logger_OBJ=bin/logger.o

fault_SRC=src/fault_manager.c
fault_OBJ=bin/fault_manager.o

common_ARCHIVE=$(PROJ_PATH)/common/bin/common.a

OBJS=$(common_OBJ)
OBJS+=$(logger_OBJ)
OBJS+=$(fault_OBJ)

$(common_OBJ): $(common_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS)

$(logger_OBJ): $(logger_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS)

$(fault_OBJ): $(fault_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS)

all: $(OBJS)
	@echo "building common"
	ar rcs $(common_ARCHIVE) $(OBJS)
	rm -f  $(OBJS)


.PHONY: clean

clean:
	rm -f $(common_ARCHIVE) $(OBJS)
