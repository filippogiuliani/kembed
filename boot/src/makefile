KEMBED_ROOT:=..
include $(KEMBED_ROOT)/Make.def

SRCS = main.c

DEPS = $(patsubst %,$(DEP_DIR)%,$(patsubst %.c,%.o,$(SRCS)))

IFLAGS += -I../../baselib/include 	\
          -I../../boot/include


all : $(DEP_DIR) $(DEPS) $(OBJ_DIR) $(DEP_DIR)start.o
	$(HIDE)$(ARMGNU)-ld -r $(DEPS) $(DEP_DIR)start.o -o $(OBJ_DIR)boot.o $(FOUT)

$(DEP_DIR)start.o : start.s
		      $(HIDE)$(ARMGNU)-as start.s -o $(DEP_DIR)start.o

clean :
	$(HIDE)rm -rf $(DEP_DIR)
	$(HIDE)rm -rf $(OBJ_DIR)
