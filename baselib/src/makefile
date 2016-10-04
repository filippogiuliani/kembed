KEMBED_ROOT:=..
include $(KEMBED_ROOT)/Make.def

SRCS = baselib.c blib_utils.c

DEPS = $(patsubst %,$(DEP_DIR)%,$(patsubst %.c,%.o,$(SRCS)))

IFLAGS += -I../../baselib/include


all : $(DEP_DIR) $(DEPS) $(OBJ_DIR)
	$(HIDE)$(ARMGNU)-ld -r $(DEPS) -o $(OBJ_DIR)baselib.o $(FOUT)

clean :
	$(HIDE)rm -rf $(DEP_DIR)
	$(HIDE)rm -rf $(OBJ_DIR)
