
link_list_ARCHIVE=$(PROJ_PATH)/ds/link_list/link_list.o
ds_ARCHIVE=$(PROJ_PATH)/ds/bin/ds.a

export

ifeq ($(LINK_LIST), true)
sub_ARCHIVE += $(link_list_ARCHIVE)
endif

all: $(ds_ARCHIVE)
	@echo "building $(ds_ARCHIVE) from $(sub_ARCHIVE)"

$(ds_ARCHIVE): $(sub_ARCHIVE)
	ar rcs $(ds_ARCHIVE) $(sub_ARCHIVE)
#	cp $(sub_ARCHIVE) $(ds_ARCHIVE)

$(link_list_ARCHIVE) :
	make -C link_list/ all

clean:
	rm -rf $(ds_ARCHIVE) $(sub_ARCHIVE)
	


