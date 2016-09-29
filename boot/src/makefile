
include ../../Make.def

SRCS = main.c

OBJS := $(patsubst %,$(OBJ_DIR)%,$(patsubst %.c,%.o,$(SRCS)))

IFLAGS += -I../../baselib/include 	\
	-I../../boot/include

clean :
	$(HIDE)rm -rf $(OBJ_DIR)
	$(HIDE)rm -rf $(BIN_DIR)

boot.o : $(OBJ_DIR) $(OBJS) $(BIN_DIR)
	$(HIDE)$(ARMGNU)-as start.s -o $(OBJ_DIR)start.o
	$(HIDE)$(ARMGNU)-ld -r $(OBJS) $(OBJ_DIR)start.o -o $(BIN_DIR)$@ $(FOUT)

$(BIN_DIR) : 
	$(HIDE)mkdir $@

$(OBJ_DIR) : 
	$(HIDE)mkdir $@
