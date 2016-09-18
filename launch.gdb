set endian little
target sim
load build/output.elf
file build/output.elf
b *0x8008
r
del 1
set $pc=0x8000