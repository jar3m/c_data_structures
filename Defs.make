# #############################################################################
#
# #############################################################################
#  ======== Defs.make=============
#
#All defines to be explained in docs/testing_framework.txt

PROJ_PATH=$(PWD)
MODULE=test
LINK_LIST=true

.show:
	@echo "PROJ_PATH= $(PROJ_PATH)"
	@echo "MODULE= $(MODULE)"
	@echo "link= $(LINK_LIST)"
