
include ../../Make.def

SRCS =  dev_gpio.c	\
	dev_irq.c	\
	dev_armtimer.c	\
	dev_uart.c

OBJS := $(patsubst %,$(OBJ_DIR)%,$(patsubst %.c,%.o,$(SRCS)))

IFLAGS += -I../../baselib/include \
	-I../../device/include

clean :
	$(HIDE)rm -rf $(OBJ_DIR)
	$(HIDE)rm -rf $(BIN_DIR)

device.o : $(OBJ_DIR) $(OBJS) $(BIN_DIR)
	$(HIDE)$(ARMGNU)-ld -r $(OBJS) -o $(BIN_DIR)$@ $(FOUT)

$(BIN_DIR) : 
	$(HIDE)mkdir $@

$(OBJ_DIR) : 
	$(HIDE)mkdir $@

