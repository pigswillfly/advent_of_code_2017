
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
	struct program_t *parent;
	int weight;
	int cumulative_weight;
	int num_children;
	struct program_t *children[NAME_SIZE];
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
		if((programs + i)->parent == NULL){
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
		ret_program->num_children = 0;
	}
	
	return ret_program;	
}

void calculate_cumulative_weights(){
	
	program_t *p;
	int i, w;
	for(i = 0; i < program_count; i++){
		p = (programs + i);
		w = p->weight;
		do{
			p->cumulative_weight += w;
			p = p->parent;
		}while(p != NULL);
	}
}

int find_weight_difference(){
	int i;
	int weights[bottom_program->num_children];
	for(i = 0; i < bottom_program->num_children; i++){
		weights[i] = bottom_program->children[i]->cumulative_weight;	
	}
	int highest = weights[0], lowest = weights[0];
	for(i = 1; i < bottom_program->num_children; i++){
		if(weights[i] < lowest){
			lowest = weights[i];
		}
		if(weights[i] > highest){
			highest = weights[i];
		}
	}
	
	//printf("Highest %i, lowest %i \n", highest, lowest);
	
	return (highest - lowest);
	
}

program_t *find_different_weight(program_t *get_my_children){
	
	int i, j, n;
	n = get_my_children->num_children;
	
	int same[n];
	
	printf("%s %i ", get_my_children->name, get_my_children->num_children);
	
	program_t *p = NULL;
	
	for(i = 0; i < n; i++){
		
		printf("  %s (%i), ", get_my_children->children[i]->name, get_my_children->children[i]->cumulative_weight);
		same[i] = 0;
		
		for(j = 0; j < n; j++){
			
			if(i == j) continue;
			if((get_my_children->children[i]->cumulative_weight) ==
			(get_my_children->children[j]->cumulative_weight)){
				same[i]++;
			}
		}
	}
	printf("\n");
	for(i = 0; i < n; i++){
		printf("%i ", same[i]);
		if(same[i] == 0){
			p = get_my_children->children[i];
		}
	}
	printf("\n");
	return p; 
	
}

program_t *find_wrong_weight_program(){
	
	program_t *p = bottom_program; 
	program_t *q;
		
	do{
		q = find_different_weight(p);
		//printf(" different %s\n", q->name);
		if(q != NULL){
			p = q;
		}
		
	} while(q != NULL);
	
	return p;
	
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
		
		if(success > 2){
			// more programs to parse
			
			// first program name above is already in m
			remove_comma(m);
			program_t *child = get_program(m);
			for(i = 0; i < 10; i++) m[i] = 0;
			
			// assign parent 
			child->parent = current_program;
			
			// assign as child of current program
			current_program->children[current_program->num_children] = child;
			current_program->num_children++;

			// count commas for remaining names (one already done)
			int programs_above = 0;
			while((*string_pointer != '\n') && (!feof(file))){
				if(*string_pointer++ == ','){
					programs_above++;
				}
			}
			
			if(programs_above){ // more than one program above
				string_pointer = string;
				
				do{
					while(*(string_pointer++) != ',');
					
					sscanf(string_pointer, "%s", m);
					
					remove_comma(m);	
					child = get_program(m);
					for(i = 0; i < 10; i++) m[i] = 0;
					
					// assign parent 
					child->parent = current_program;
					
					// assign as child of current program
					current_program->children[current_program->num_children] = child;
					current_program->num_children++;
					
					programs_above--;
					
				}while(programs_above);
				
			}
			
		}
	
		reset(); // reset before reading next line

	}
	
	
	fclose(file);
	
	find_bottom_program();	
	
	calculate_cumulative_weights();
	/*
	
	for(i = 0; i < program_count; i++){
		program_t *p = (programs + i);
		printf("%s (%i)/(%i), parent %s, children ", p->name, p->weight, p->cumulative_weight, p->parent->name);
		int j;
		for(j = 0; j < p->num_children; j++){
			printf("%s ", p->children[j]->name);
		}
		printf("\n");
	}
	*/
	
	int weight_diff = find_weight_difference();
	
	program_t *wrong_weight_program = find_wrong_weight_program();
	
	printf("Wrong program %s weight %i - %i = %i\n", wrong_weight_program->name, wrong_weight_program->weight,  weight_diff, wrong_weight_program->weight - weight_diff);
	
	

	
	
	
	return 0;
	
}
