
link_list_ARCHIVE=$(PROJ_PATH)/ds/link_list/link_list.o
stack_ARCHIVE=$(PROJ_PATH)/ds/stack/stack.o
ds_ARCHIVE=$(PROJ_PATH)/ds/bin/ds.a

export

ifeq ($(LINK_LIST), true)
sub_ARCHIVE += $(link_list_ARCHIVE)
endif

ifeq ($(STACK), true)
sub_ARCHIVE += $(stack_ARCHIVE)
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

clean:
	rm -rf $(ds_ARCHIVE) $(sub_ARCHIVE)
	


