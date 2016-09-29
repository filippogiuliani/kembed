set endian little
target sim
load debug/output.elf
file debug/output.elf
b main
r