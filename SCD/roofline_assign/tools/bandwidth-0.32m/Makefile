#============================================================================
# bandwidth 0.28, a benchmark to estimate memory transfer bandwidth.
# Copyright (C) 2005-2012 by Zack T Smith.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
# The author may be reached at veritas@comcast.net.
#============================================================================

#CFLAGS= -O6 -lm
CFLAGS= -g -lm
CC=gcc
SRC=main.c BMP.c
AS=nasm

message:
	@echo ""
	@echo "To compile for x86 Linux:          make bandwidth32"
	@echo "To compile for x86_64 Linux:       make bandwidth64"
	@echo "To compile for x86 Mac OS/X:       make bandwidth-mac32"
	@echo "To compile for x86_64 Mac OS/X:    make bandwidth-mac64"
	@echo "To compile for x86 Win32/Cygwin:   make bandwidth-win32"
	@echo ""

bandwidth64:	main.c routines64.asm BMP.c
	${AS} -f elf64 routines64.asm -o routines64.o
	${CC} -m64 -g routines64.o ${SRC} ${CFLAGS} -o bandwidth64

bandwidth32:	main.c routines32.asm  BMP.c
	${AS} -f elf routines32.asm -o routines32.o
	${CC} -m32 -mtune=pentium routines32.o ${SRC} ${CFLAGS} -o bandwidth32

bandwidth-mac64:	main.c routines64.asm BMP.c
	${AS} -f macho64 routines64.asm -o routines64.o
	${CC} -m64 -g -Wall routines64.o ${SRC} ${CFLAGS} -o bandwidth-mac64

bandwidth-mac32:	main.c routines32.asm BMP.c
	${AS} -f macho32 routines32.asm -o routines32.o
	${CC} -m32 routines32.o ${SRC} ${CFLAGS} -o bandwidth-mac32

bandwidth-win32:	main.c routines32.asm  BMP.c
	${AS} -f win32 routines32.asm -o routines32.o
	${CC} -Wall -O6 -D__WIN32__ -DWINVER=0x0600 routines32.o ${SRC} -o bandwidth-win32

clean:
	rm -f bandwidth bandwidth32 bandwidth64 routines32.o routines64.o bandwidth-win32.exe bandwidth.bmp bandwidth-mac32 bandwidth-mac64

