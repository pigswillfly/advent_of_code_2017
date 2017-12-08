
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_STRING_SIZE 256
#define NUM_STRINGS 20
#define STRING_SIZE 15

char line_string[LINE_STRING_SIZE];
char words[NUM_STRINGS][STRING_SIZE];
int word_count;

//const char filename[] = "ex2_input_day4.txt";
const char filename[] = "day_4_input.txt";

int phrase_is_valid(){
	
	int i, j;
	
	for(i = 0; i < word_count; i++){
		
		for(j = 0; j < word_count; j++){
			if(j == i) continue;
			
			if(strncmp(words[i], words[j], STRING_SIZE) == 0){
				return 0;
			}

		}
		
	}
	
	return 1;
}

void reset(){
	
	int i, j;
	for(i = 0; i < NUM_STRINGS; i++){
		
		for(j = 0; i < STRING_SIZE; i++){
			
			words[i][j] = 0;
			
		}
		
	}
	word_count = 0;
	
	for(i = 0; i < LINE_STRING_SIZE; i++){
		line_string[i] = 0;
	}
	
}


int main (int argc, char *argv[]){

	FILE *file;
	file = fopen(filename, "r");
	int i, success, line = 0;	
	
	char *string_pointer;
	int valid_phrases = 0;
	
	reset();
	
	while(!feof(file)){

		fgets(line_string, LINE_STRING_SIZE, file);
		line++;
		
		success = sscanf(line_string, 
						"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", 
						words[0], 
						words[1], 
						words[2], 
						words[3], 
						words[4],
						words[5],
						words[6],
						words[7],
						words[8],
						words[9],
						words[10],
						words[11],
						words[12],
						words[13],
						words[14],
						words[15],
						words[16],
						words[17],
						words[18],
						words[19],
						words[20]);
		
		// success = number of words in phrase
		word_count = success;

 		if(phrase_is_valid()){
			valid_phrases++;
			printf("%s valid\n\n", line_string);
		} else{
			printf("%s not valid\n\n", line_string);
		}
		
		reset();
	}
	
	printf("Total phrases %i\n", line);
	printf("Valid phrases %i", valid_phrases);
	
	fclose(file);
	
	return 0;
}