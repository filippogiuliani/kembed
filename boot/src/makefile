#
#   boot module makefile
#   
#   This implement is part of the toolchain to compile the kernel module
#
#
#    File:       <FILE>
#    Author:     <AUTHORNAME>
#    Mail:       <AUTHORMAIL>
#    Date:       <COMMITTERDATEISO8601>
#    Ident:      <COMMITHASH>
#    Branch:     <BRANCH>
#
#    <CHANGELOG:--reverse --grep "^tags.*relevant":-1:%an : %ai : %s>
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
