
link_list_ARCHIVE=$(PROJ_PATH)/ds/link_list/link_list.o
stack_ARCHIVE=$(PROJ_PATH)/ds/stack/stack.o
queue_ARCHIVE=$(PROJ_PATH)/ds/queue/queue.o
hash_ARCHIVE=$(PROJ_PATH)/ds/hash/hash.o
ds_ARCHIVE=$(PROJ_PATH)/ds/bin/ds.a

export

ifeq ($(LINK_LIST), true)
INCLUDES += -I $(PROJ_PATH)/ds/link_list/
sub_ARCHIVE += $(link_list_ARCHIVE)
endif

ifeq ($(STACK), true)
INCLUDES += -I $(PROJ_PATH)/ds/stacks/
sub_ARCHIVE += $(stack_ARCHIVE)
endif

ifeq ($(QUEUE), true)
INCLUDES += -I $(PROJ_PATH)/ds/queue/
sub_ARCHIVE += $(queue_ARCHIVE)
endif

ifeq ($(HASH), true)
INCLUDES += -I $(PROJ_PATH)/ds/hash/
sub_ARCHIVE += $(hash_ARCHIVE)
endif

all: $(ds_ARCHIVE)
	@echo "building $(ds_ARCHIVE) from $(sub_ARCHIVE)"

$(ds_ARCHIVE): $(sub_ARCHIVE)
	ar rcs $(ds_ARCHIVE) $(sub_ARCHIVE)
#	cp $(sub_ARCHIVE) $(ds_ARCHIVE)

$(link_list_ARCHIVE) :
	make -C link_list/ all

$(stack_ARCHIVE) :
	make -C stack/ all

$(queue_ARCHIVE) :
	make -C queue/ all

$(hash_ARCHIVE) :
	make -C hash/ all

clean:
	rm -rf $(ds_ARCHIVE) $(sub_ARCHIVE)
	


