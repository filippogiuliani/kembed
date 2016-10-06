#
#   kembed makefile
#   
#   This file is part of the toolchain to compile kembed
#
#
#    @file:      $File$
#    @author:    $Author$
#    @date:      $Date$
#    @version:   $Revision$
#
#    $Id$
#
#
#   (C) Copyright 2016 Filippo Giuliani <mail@filippogiuliani.it>
#
#   This file is part of kembed.
#
#   kembed is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   kembed is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with kembed.  If not, see <http://www.gnu.org/licenses/>.


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
