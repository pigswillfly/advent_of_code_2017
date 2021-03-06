
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_STRING_SIZE 256
#define NAME_SIZE 10
#define TOTAL_PROGRAMS 1500

//const char filename[] = "ex_input_day_7.txt";
const char filename[] = "day_7_input.txt";

char string[LINE_STRING_SIZE];
char *string_pointer = string;

typedef struct program_t{
	char name[NAME_SIZE];
	char below[NAME_SIZE];
	int weight;
}program_t;

program_t *programs;
int program_count = 0;
program_t *bottom_program;

void reset(){

	int i;
	for(i = 0; i < LINE_STRING_SIZE; i++){
		string[i] = 0;
	}
	string_pointer = string;

}

void find_bottom_program(){
	
	int i,j; 
	for(i = 0; i<program_count; i++){
		if(((programs + i)->below[0]) == 0){
			bottom_program = programs + i;
		}
	}
	
}

program_t *get_program(char *n){
	int i;
	program_t *ret_program = NULL;
	
	for(i = 0; i < program_count; i++){
		if(strncmp(n,(programs + i)->name, NAME_SIZE) == 0){
			ret_program = (programs + i);
			break;
		}
	}
	
	if(ret_program == NULL){
		ret_program = (programs + program_count);
		program_count++;
	
		strncpy(ret_program->name, n, NAME_SIZE);
		ret_program->weight = 0;
	}
	
	return ret_program;	
}

void remove_comma(char *m){
	
	while(*m != '\0'){
		if(*m == ',') {
			*m = '\0';
			break;
		}
		m++;
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
		fgets(string, LINE_STRING_SIZE, file);
		line++;
		
		char n[10], m[10];
		int w;
		int success;
		
		success = sscanf(string_pointer, "%s (%i) -> %s", n, &w, m);
		
		// find if any existing programs match name
		// if yes this means they are above another program
		program_t *current_program = get_program(n);
		
		// copy weight to object
		current_program->weight = w;
		
		printf("%s \n", current_program);
		
		if(success > 2){
			// more programs to parse
			printf("more programs ");
			
			// first program name above is already in m
			remove_comma(m);
			program_t *program_above = get_program(m);
			
			strncpy(program_above->below, current_program->name, NAME_SIZE);
			for(i = 0; i < 10; i++) m[i] = 0;

			// count commas for remaining names (one already done)
			int programs_above = 0;
			while((*string_pointer != '\n') && (!feof(file))){
				if(*string_pointer++ == ','){
					programs_above++;
				}
			}
			
			printf("Programs above = %i\n ", (programs_above + 1));

			printf("	%s\n", program_above->name);
			
			if(programs_above){ // more than one program above
				string_pointer = string;
				
				do{
					while(*(string_pointer++) != ',');
					
					sscanf(string_pointer, "%s", m);
					
					remove_comma(m);
					printf("	%s\n", m);
					
					program_above = get_program(m);
					strncpy(program_above->below, current_program->name, NAME_SIZE);
					for(i = 0; i < 10; i++) m[i] = 0;
					
					programs_above--;
					
				}while(programs_above);
				
			}
			
		}
	
		reset(); // reset before reading next line

	}
	
	
	fclose(file);
	
	find_bottom_program();
	
	
	printf("Name of bottom program is: %s", bottom_program->name);
	
	return 0;
	
}
