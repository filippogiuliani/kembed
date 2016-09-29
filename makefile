

include Make.def

TARGET = kernel.img
LINKER = kernel.ld

MODULES = boot asm kernel baselib device

# The intermediate directory for compiled object files.
TARGET_DIR = img/

OBJECTS := $(foreach module,$(MODULES),$(module)/$(BIN_DIR_FROM_MAIN)$(module).o)

BUILD_DIR = $(BUILD)/

all: $(TARGET)

rebuild: distclean all

$(TARGET_DIR) :
	$(HIDE)mkdir $@

$(BUILD_DIR) :
	$(HIDE)mkdir $@

# Rule to make the elf file.
$(BUILD_DIR)output.elf : $(MODULES) $(BUILD_DIR) $(LINKER)
	@echo Creating $(BUILD_DIR)output.elf..
	$(HIDE)$(ARMGNU)-ld $(LFLAGS) $(OBJECTS) -o $(BUILD_DIR)output.elf -T $(LINKER) $(FOUT)
#	$(HIDE)$(ARMGNU)-ld $(LFLAGS) $(OBJECTS) -o $(BUILD_DIR)output.elf $(FOUT)

$(TARGET) : $(BUILD_DIR)output.elf $(TARGET_DIR)
	@echo Creating $(TARGET)..
	$(HIDE)$(ARMGNU)-objcopy $(BUILD_DIR)output.elf -O binary $(TARGET_DIR)$(TARGET) $(FOUT)

$(MODULES) : FORCE
	@echo Compiling $@..
	$(HIDE)cd $@ && $(MAKE) $@.o $(MFLAGS)

$(LINKER) : FORCE
	@echo Generating linker script
	./kernel.py $(BIN_DIR_FROM_MAIN) $(MODULE_ALIGNMENT) $(SECTION_ALIGNMENT) $(MODULES) > kernel.ld

FORCE :

# Rule to clean files.
clean : 
	$(HIDE)rm -rf $(BUILD_DIR) $(FOUT)
	$(HIDE)rm -rf $(TARGET_DIR) $(FOUT)

clean_module :
	$(HIDE)for i in $(MODULES) ; do 			\
		cd $$i && $(MAKE) $(MFLAGS) clean && cd ..;	\
	done

cleanall : clean_module clean
distclean : cleanall
