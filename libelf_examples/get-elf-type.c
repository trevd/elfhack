/*
 * get-elf-type.c
 *
 * Legal Notice
 * Copyright c 2006–2012 Joseph Koshy. All rights reserved.
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 *    Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *    
 *    Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * Disclaimer
 * 
 * THIS DOCUMENTATION IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR AND CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS DOCUMENTATION,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include <err.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <libelf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


extern const char* __progname ;

#define ELF_KIND_STR_MAX 14 

void cleanup_and_die(int fd,Elf* elf,int exit_code,int errnumber)
{
	
	if(fd > 0){
		close(fd);
	} 
	if(elf != NULL){
		elf_end(elf);
	}
	if(errnumber != EXIT_SUCCESS){
		errno = errnumber; 
		err(EXIT_FAILURE, " error ");
	}
	
	exit(exit_code);
}
char* get_elf_kind_string(Elf* elf)
{
	if(elf == NULL){
		return NULL;
	}
	
	Elf_Kind elfkind = elf_kind(elf);
	
	switch(elfkind){
	
		case ELF_K_AR:{
			return "ar(1) archive" ;
			break;
		}
		case ELF_K_ELF:{
			return "elf object" ;
			break;
		}
		case ELF_K_NONE:{
			return "data" ;
			break;
		}
		default:{
			return "unrecongnized" ;
		}
	}
	return "unrecongnized";
}	


int main(int argc, char** argv)
{

	if ( argc != 2 ){
		 errx(EXIT_FAILURE,"usage: %s <filename>",__progname);
	}
	
	// sanity check the input arguments - never trust the caller 
	if ( ( argv[1] == NULL ) || ( strnlen(argv[1],PATH_MAX) >= PATH_MAX )){
		err(EXIT_FAILURE, "<filename>");
	}
	
	int fd = open(argv[1], O_RDONLY, 0);
	if ( fd < 0 ){
		err(EXIT_FAILURE, " open \"%s\" failed ", argv[1]);
	} 
	
	// libelf initialization
	if ( elf_version(EV_CURRENT) == EV_NONE ){
		errx(EXIT_FAILURE, "ELF library initialization failed: %s\n", elf_errmsg(-1));
	}	
	
	// Start the ELF Dance
	Elf *elf = elf_begin(fd, ELF_C_READ, NULL);
	if(elf == NULL){
		errx(EXIT_FAILURE, "elf_begin() failed: %s\n", elf_errmsg(-1));
	}
	
	char* kind = get_elf_kind_string(elf);
	if( (kind == NULL) || (strnlen(kind,ELF_KIND_STR_MAX) >= ELF_KIND_STR_MAX)){
			cleanup_and_die(fd,elf,EXIT_FAILURE,EFAULT);
	}
	fprintf(stdout,"%s: %s\n",argv[1],kind);
	
	cleanup_and_die(fd,elf,EXIT_SUCCESS,EXIT_SUCCESS);	
	
	exit(EXIT_SUCCESS);
	
	
}
