

include Make.def

TARGET = kernel.img
LINKER = kernel.ld

# The intermediate directory for compiled object files.
TARGET_DIR = img/

BUILD_DIR = $(BUILD)/

all: $(BUILD_DIR)output.elf

install: $(TARGET)

rebuild: distclean all

$(TARGET_DIR) :
	$(HIDE)mkdir $@

$(BUILD_DIR) :
	$(HIDE)mkdir $@

# Rule to make the elf file.
$(BUILD_DIR)output.elf : $(MODULES) $(BUILD_DIR) $(LINKER)
	@echo Creating $(BUILD_DIR)output.elf..
	$(HIDE)$(ARMGNU)-ld $(LFLAGS) -o $(BUILD_DIR)output.elf -T $(LINKER) $(FOUT)

$(TARGET) : $(BUILD_DIR)output.elf $(TARGET_DIR)
	@echo Creating $(TARGET)..
	$(HIDE)$(ARMGNU)-objcopy $(BUILD_DIR)output.elf -O binary $(TARGET_DIR)$(TARGET) $(FOUT)

$(MODULES) : FORCE
	@echo Compiling $@..
	$(HIDE)$(MAKE) -C $@ all $(MFLAGS)

$(LINKER) : FORCE
	@echo Generating linker script
	./kernel.py $(MODULE_ALIGNMENT) $(SECTION_ALIGNMENT) $(MODULES) > kernel.ld

FORCE :

# Rule to clean files.
clean :
	$(HIDE)echo "Clean KEmbed images"	
	$(HIDE)rm -rf {debug,release} $(FOUT)
	$(HIDE)rm -rf $(TARGET_DIR) $(FOUT)

clean_module :
	$(HIDE)echo "Clean all the KEmbed submodules"
	$(HIDE)for i in $(MODULES) ; do 	\
		$(MAKE) -C $$i $(MFLAGS) clean;	\
	done

cleanall : clean_module clean

distclean : cleanall
