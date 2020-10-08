
export CC
export NN_PATH

include $(NN_PATH)/Defs.make


LDLIBS +=  -lm -pg

INCLUDES += -I $(NN_PATH)/neural_network/inc/

CFLAGS += -g -Wall $(NN_SRC_DEFS)

nn_def_SRC=src/nn_def.c
nn_def_OBJ=bin/nn_def.o

nn_algo_SRC=src/nn_algo.c
nn_algo_OBJ=bin/nn_algo.c

nn_ARCHIVE=$(NN_PATH)/neural_network/bin/neural_network.a

$(nn_def_OBJ): $(nn_def_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS) 

$(nn_algo_OBJ): $(nn_algo_SRC)
	$(CC) $(INCLUDES) -c $^ -o $@ $(CFLAGS) 

OBJS += $(nn_def_OBJ) $(nn_algo_OBJ)

all: $(OBJS)
	ar rcs $(nn_ARCHIVE) $(OBJS)

.PHONY: clean

clean:
	rm -f $(nn_ARCHIVE) $(OBJS)
