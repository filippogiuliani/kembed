KEMBED_ROOT:=..
include $(KEMBED_ROOT)/Make.def

SRCS = 

DEPS = $(patsubst %,$(DEP_DIR)%,$(patsubst %.c,%.o,$(SRCS)))

IFLAGS += -I../../baselib/include 	\
          -I../../boot/include


all : $(DEP_DIR) $(DEPS) $(OBJ_DIR) $(DEP_DIR)instruction.o
	$(HIDE)$(ARMGNU)-ld -r $(DEPS) $(DEP_DIR)instruction.o -o $(OBJ_DIR)asm.o $(FOUT)

$(DEP_DIR)instruction.o : instruction.s
		      $(HIDE)$(ARMGNU)-as instruction.s -o $(DEP_DIR)instruction.o

clean :
	$(HIDE)rm -rf $(DEP_DIR)
	$(HIDE)rm -rf $(OBJ_DIR)
