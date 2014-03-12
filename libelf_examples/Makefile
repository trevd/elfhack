
#CC = gcc
CC = /usr/bin/clang
#@echo $(CC) $(CXX)
all: get-elf-type print-elf-header
	
get-elf-type: get-elf-type.c
	$(CC) -I/usr/include get-elf-type.c -lelf -o get-elf-type 
	
print-elf-header: print-elf-header.c
	$(CC) -I/usr/include print-elf-header.c -lelf -o print-elf-header
	
.PHONY: clean

clean:
	rm get-elf-type print-elf-header
