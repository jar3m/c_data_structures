include Defs.make

CC=gcc
TEST_FILE_DIRECTORY="$(PROJ_PATH)/test/src"

LDLIBS= -lm -pg
INCLUDES+=-I $(PROJ_PATH)/ds/inc
INCLUDES+=-I $(PROJ_PATH)/common/inc
INCLUDES+=-I $(PROJ_PATH)/test/inc

common_ARCHIVE=$(PROJ_PATH)/common/bin/common.a
ds_ARCHIVE=$(PROJ_PATH)/ds/bin/ds.a
algo_ARCHIVE=$(PROJ_PATH)/algo/bin/algo.a
test_ARCHIVE=$(PROJ_PATH)/test/bin/test.a

MODULE_ARCHIVES += $(common_ARCHIVE)

ifeq ($(MODULE), ds)
MODULE_ARCHIVES += $(ds_ARCHIVE)
endif

ifeq ($(MODULE), algo)
MODULE_ARCHIVES += $(algo_ARCHIVE)
endif

ifeq ($(MODULE), test)
MODULE_ARCHIVES += $(ds_ARCHIVE)
MODULE_ARCHIVES += $(test_ARCHIVE)
endif

ifeq ($(MODULE), all)
MODULE_ARCHIVES += $(algo_ARCHIVE)
MODULE_ARCHIVES += $(ds_ARCHIVE)
MODULE_ARCHIVES += $(test_ARCHIVE)
endif

export

all: $(MODULE_ARCHIVES)
	@echo "All archives ($(MODULE_ARCHIVES)) created"
	$(CC) $(INCLUDES) $^ -rdynamic -o foo.out $(MODULE_ARCHIVES) $(LDLIBS) $(CFLAGS)

$(common_ARCHIVE) :
	make -C common/ all

$(algo_ARCHIVE) :
	make -C algo/ all

$(ds_ARCHIVE) :
	make -C ds/ all

$(test_ARCHIVE) :
	make -C test/ all

.PHONY: clean help

clean:
	make -C test/ clean
	make -C ds/ clean
	find ${PROJ_PATH} -name "*.[ao]" -exec rm -v {} \;
	find ${PROJ_PATH} -name "*.out" -exec rm -v {} \;



help:
	@echo "Available build options"
	@echo "#> make <OPTIONS>"
	@echo
	@echo "OPTIONS:"
	@echo "all"
	@echo "ds"
	@echo "algo"
	@echo "test"

