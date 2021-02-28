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
SEGFAULT_BACKTRACE=false
#include submodules of Data structures
LINK_LIST=true

.show:
	@echo "PROJ_PATH= $(PROJ_PATH)"
	@echo "LIB_NAME=$(LIB_NAME)"
	@echo "MODULE= $(MODULE)"
	@echo "BUILD_TYPE=$(BUILD_TYPE)"
	@echo "link= $(LINK_LIST)"
