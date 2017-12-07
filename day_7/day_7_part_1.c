
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 256
#define TOTAL_PROGRAMS 1500

const char filename[] = "ex_input_day_7.txt";
//const char filename[] = "day_7_input.txt";

char string[SIZE];
char *string_pointer = string;

int end_of_line = 0;

typedef struct program_t{
	char name[10];
	char below[10];
	int weight;
}program_t;

program_t *programs;
int program_count = 0;
program_t *bottom_program;

void reset(){

	int i;
	for(i = 0; i < SIZE; i++){
		string[i] = 0;
	}
	string_pointer = string;
	end_of_line = 0;

}

int do_strings_match(char *str1, char *str2){
	
	while((*str1 != '\0')){
		if(*(str1++) != *(str2++)){
			return 0;
		}
	}
	
	return 1;
}

void find_bottom_program(){
	
	int i,j; 
	for(i = 0; i<program_count; i++){
		if(*((programs + i)->below) == 0){
			bottom_program = programs + i;
		}
	}
	
}

int main (int argc, char *argv[]){

	FILE *file;
	file = fopen(filename, "r");
	int i;	
	reset();	
		
	int line = 0;
	programs = malloc(TOTAL_PROGRAMS * sizeof(program_t));
		
	/* while not end of file */
	while(!feof(file)){
		
		/* Get new line */
		fgets(string, SIZE, file);
		line++;
		
		char n[10], m[10];
		int w;
		int success;
		
		success = sscanf(string_pointer, "%s (%i) -> %s,", n, &w, m);
		
		if(success == 2){
			// no programs above
			end_of_line = 1;
		} else if (success == 3){
			// programs above, need to parse more
			
		}
		
		// find if any existing programs match name
		// if yes this means they are above another program
		program_t *current_program = NULL;
		for(i = 0; i < program_count; i++){
			if(do_strings_match(n, (programs + i)->name)){
					current_program = (programs + i);
					break;
			}
		}
		if(current_program == NULL){
			// not above any others
			
			// create new program
			program_count++;
			current_program = programs + program_count;
			
			// copy name
			strncpy(current_program->name, (const char *)n, 10);
		
		}
		
		// copy weight to object
		current_program->weight = w;
		
		printf("%s \n", current_program);
		
		if(!end_of_line){
			// more programs to parse
			printf("more programs ");
			
			// count commas
			int programs_above = 1;
			while(*string_pointer != '\n'){
				if(*string_pointer++ == ','){
					programs_above++;
				}
			}
			
			printf("%i\n", programs_above);
			string_pointer = string;
			while(*(string_pointer++) != '>');
			
			do{
				while(*(string_pointer++) != ' ');
				sscanf(string_pointer, "%s", m);
				printf("	%s\n", m);
				for(i = 0; i < 10; i++) m[i] = 0;				
				
			}while(--programs_above);
/* 			// find right place
			do{
				string_pointer++;
			}while(*string_pointer != '>');
			string_pointer+=2; // now pointing to first in list
			
			// parse remaining names in line
			do{
				// parse one name
				sscanf(string_pointer, "%s", n);
				
				printf("	%s\n", n);
				
				// find if any programs match
				program_t *p;
				int match = 0;
				for(i = 0; i < program_count; i++){
					if(do_strings_match(n, (programs + i)->name)){
						match = 1;
						p = programs + i;
						break;
					}
				}
				if(!match){
					// create a program
					program_count++;
					strncpy((programs + program_count)->name, n, 10);
					p = programs + program_count;
					
				}
				
				// assign above as current program
				strncpy(p->below, current_program->name, 10);
				
				// find next space or end of line
				do{
					string_pointer++;
				}while((*string_pointer != '\n') || (*string_pointer != '\0'));
			
				if(*string_pointer == '\0'){
					end_of_line = 1;  // no names left, exit loop
				} else {
					string_pointer++; // pointing to next name, loop
					for(i = 0; i < 10; i++){
						n[i] = 0;
					}
				}
			
			}while(!end_of_line); */
			
		}

	
		reset(); // reset before reading next line

		
	}
	
	
	fclose(file);
	
	find_bottom_program();
	
	
	//printf("Name of bottom program is: %s", bottom_program->name);
	
	return 0;
	
}
