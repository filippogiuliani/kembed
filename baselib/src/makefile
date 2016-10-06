#
#   baselib module makefile
#   
#   This implement is part of the toolchain to compile the baselib module
#
#
#   $LastChangedDate: 2016-07-22 21:42:37 -0700 (Sat, 22 Jul 2006) $
#   $Revision: 144 $
#   $Author: filippogiuliani $
#   $Id: makefile 148 2006-07-28 21:30:43Z sally $
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

SRCS = baselib.c blib_utils.c

DEPS = $(patsubst %,$(DEP_DIR)%,$(patsubst %.c,%.o,$(SRCS)))

IFLAGS += -I../../baselib/include


all : $(DEP_DIR) $(DEPS) $(OBJ_DIR)
	$(HIDE)$(ARMGNU)-ld -r $(DEPS) -o $(OBJ_DIR)baselib.o $(FOUT)

clean :
	$(HIDE)rm -rf $(DEP_DIR)
	$(HIDE)rm -rf $(OBJ_DIR)
