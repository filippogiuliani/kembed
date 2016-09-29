
include ../../Make.def

SRCS = 

OBJS := $(patsubst %,$(OBJ_DIR)%,$(patsubst %.c,%.o,$(SRCS)))

IFLAGS += -I../../baselib/include 	\
	-I../../boot/include

clean :
	$(HIDE)rm -rf $(OBJ_DIR)
	$(HIDE)rm -rf $(BIN_DIR)

asm.o : $(OBJ_DIR) $(OBJS) $(BIN_DIR)
	$(HIDE)$(ARMGNU)-as instruction.s -o $(OBJ_DIR)instruction.o
	$(HIDE)$(ARMGNU)-ld -r $(OBJS) $(OBJ_DIR)instruction.o -o $(BIN_DIR)$@ $(FOUT)

$(BIN_DIR) : 
	$(HIDE)mkdir $@

$(OBJ_DIR) : 
	$(HIDE)mkdir $@
