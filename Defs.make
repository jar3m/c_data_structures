# #############################################################################
#
# #############################################################################
#  ======== Defs.make=============
#
#All defines to be explained in docs/testing_framework.txt

PROJ_PATH=$(PWD)
LIB_NAME=c_everyting.so

#which Modules to build
MODULE=test

#build type
BUILD_TYPE=executable
#BUILD_TYPE=library

#flags
SEGFAULT_BACKTRACE=true
#include submodules of Data structures
LINK_LIST=true
STACK=true
QUEUE=true
HEAP=true
TREE=true

#data struct define
DS_FLAGS = -DLINK_LIST=$(LINK_LIST) -DSTACK=$(STACK) \
	   -DQUEUE=$(QUEUE) -DHEAP=$(HEAP) -DTREE=$(TREE)

.show:
	@echo "PROJ_PATH= $(PROJ_PATH)"
	@echo "LIB_NAME=$(LIB_NAME)"
	@echo "MODULE= $(MODULE)"
	@echo "BUILD_TYPE=$(BUILD_TYPE)"
	@echo "LINK_LIST= $(LINK_LIST)"
	@echo "STACKS= $(STACK)"
	@echo "QUEUES= $(QUEUE)"
	@echo "HEAPS= $(HEAP)"
	@echo "TREES= $(TREE)"
