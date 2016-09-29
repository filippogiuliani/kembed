
include ../../Make.def

SRCS = kernel.c

OBJS := $(patsubst %,$(OBJ_DIR)%,$(patsubst %.c,%.o,$(SRCS)))

IFLAGS += -I../../baselib/include 	\
	-I../../device/include		\
	-I../../kernel/include

clean :
	$(HIDE)rm -rf $(OBJ_DIR)
	$(HIDE)rm -rf $(BIN_DIR)

kernel.o : $(OBJ_DIR) $(OBJS) $(BIN_DIR)
	$(HIDE)$(ARMGNU)-ld -r $(OBJS) -o $(BIN_DIR)$@ $(FOUT)

$(BIN_DIR) : 
	$(HIDE)mkdir $@

$(OBJ_DIR) : 
	$(HIDE)mkdir $@
