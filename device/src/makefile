KEMBED_ROOT:=..
include $(KEMBED_ROOT)/Make.def

SRCS =  dev_gpio.c	\
	dev_irq.c	\
	dev_armtimer.c	\
	dev_mailbox.c	\
	dev_monitor.c	\
	dev_uart.c

DEPS = $(patsubst %,$(DEP_DIR)%,$(patsubst %.c,%.o,$(SRCS)))

IFLAGS += -I../../baselib/include 	\
          -I../../device/include


all : $(DEP_DIR) $(DEPS) $(OBJ_DIR)
	$(HIDE)$(ARMGNU)-ld -r $(DEPS) -o $(OBJ_DIR)device.o $(FOUT)

clean :
	$(HIDE)rm -rf $(DEP_DIR)
	$(HIDE)rm -rf $(OBJ_DIR)

