KEMBED_ROOT:=..
include $(KEMBED_ROOT)/Make.def

SRCS = kernel.c

DEPS = $(patsubst %,$(DEP_DIR)%,$(patsubst %.c,%.o,$(SRCS)))

IFLAGS += -I../../baselib/include 	\
          -I../../device/include	\
	  -I../../kernel/include


all : $(DEP_DIR) $(DEPS) $(OBJ_DIR)
	$(HIDE)$(ARMGNU)-ld -r $(DEPS) -o $(OBJ_DIR)kernel.o $(FOUT)

clean :
	$(HIDE)rm -rf $(DEP_DIR)
	$(HIDE)rm -rf $(OBJ_DIR)
