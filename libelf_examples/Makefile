
#CC = gcc
CC = /usr/bin/clang
#@echo $(CC) $(CXX)
all: get-elf-type
	
get-elf-type: get-elf-type.c
	$(CC) -I/usr/include get-elf-type.c -lelf -o get-elf-type 
	
.PHONY: clean

clean:
	rm get-elf-type
