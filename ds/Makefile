
link_list_ARCHIVE=$(PROJ_PATH)/ds/link_list/link_list.o
stack_ARCHIVE=$(PROJ_PATH)/ds/stack/stack.o
queue_ARCHIVE=$(PROJ_PATH)/ds/queue/queue.o
heap_ARCHIVE=$(PROJ_PATH)/ds/heap/heap.o
tree_ARCHIVE=$(PROJ_PATH)/ds/tree/tree.o
graph_ARCHIVE=$(PROJ_PATH)/ds/graph/graph.o

ds_ARCHIVE=$(PROJ_PATH)/ds/bin/ds.a

export

ifeq ($(LINK_LIST), true)
INCLUDES += -I $(PROJ_PATH)/ds/link_list/
sub_ARCHIVE += $(link_list_ARCHIVE)
endif

ifeq ($(STACK), true)
INCLUDES += -I $(PROJ_PATH)/ds/stack/
sub_ARCHIVE += $(stack_ARCHIVE)
endif

ifeq ($(QUEUE), true)
INCLUDES += -I $(PROJ_PATH)/ds/queue/
sub_ARCHIVE += $(queue_ARCHIVE)
endif

ifeq ($(HEAP), true)
INCLUDES += -I $(PROJ_PATH)/ds/heap/
sub_ARCHIVE += $(heap_ARCHIVE)
endif

ifeq ($(TREE), true)
INCLUDES += -I $(PROJ_PATH)/ds/tree/
sub_ARCHIVE += $(tree_ARCHIVE)
endif

ifeq ($(GRAPH), true)
INCLUDES += -I $(PROJ_PATH)/ds/graph/
sub_ARCHIVE += $(graph_ARCHIVE)
endif

all: $(ds_ARCHIVE)

$(ds_ARCHIVE): $(sub_ARCHIVE)
	@echo "building $(ds_ARCHIVE) from $(sub_ARCHIVE)"
	ar rcs $(ds_ARCHIVE) $(sub_ARCHIVE)
#	cp $(sub_ARCHIVE) $(ds_ARCHIVE)

$(link_list_ARCHIVE) :
	make -C link_list/ all

$(stack_ARCHIVE) :
	make -C stack/ all

$(queue_ARCHIVE) :
	make -C queue/ all

$(heap_ARCHIVE) :
	make -C heap/ all

$(tree_ARCHIVE) :
	make -C tree/ all

$(graph_ARCHIVE) :
	make -C graph/ all

clean:
	rm -rf $(ds_ARCHIVE) $(sub_ARCHIVE)
	


