
#include <stdint.h>
#include <stdio.h>

#define SIZE 256

//const char filename[] = "ex_input_day_2.txt";
const char filename[] = "day_2_input.txt";

char string[SIZE];
char *space_finder = string;
int numbers[30];
int number_index = 0;
int last_number = 0;
int biggest = 0, smallest = 0;
int checksum = 0;


void reset(){
	int i;
	for(i = 0; i < 30; i++){
		numbers[i] = 0;
	}
	for(i = 0; i < SIZE; i++){
		string[i] = 0;
	}
	number_index = 0;
	last_number = 0;
	space_finder = string;
	biggest = 0;
	smallest = 0;
}


int main (int argc, char *argv[]){

	FILE *file;
	file = fopen(filename, "r");
	int number = 0;	
	reset();
		
	int line = 0;
		
	/* while not end of file */
	while(!feof(file)){
		
		/* Get new line */
		fgets(string, SIZE, file);
		line++;
		
		/* Get numbers */
				
		do{
			sscanf(space_finder, "%i", &number);
			printf("number is %i\n", number);
			if(number != 0){
				numbers[number_index++] = number;
			}				
			
			/* Find beginning of next number */
			while(*space_finder != ' '){
				if((*space_finder == '\n') || (*space_finder == 0)){
					last_number = 1;
					printf("last number\n");
					break;
				}
				space_finder++;
				
			}
			space_finder++; // now pointing at next number			
			
		}while(!last_number);
		
		
		int i;
		biggest = numbers[0];
		smallest = numbers[0];
		for(i = 1; i < number_index; i++){
			printf("%i ", numbers[i]);
			
			if(numbers[i] > biggest){
				biggest = numbers[i];
			}
			
			if(numbers[i] < smallest){
				smallest = numbers[i];
			}
			
			
		}
		
		int diff = (biggest - smallest);
		printf("Line %i difference %i\n", line, diff);
		
		checksum += diff;
		
		reset();

		
	}
	
	
	fclose(file);

	printf("Checksum is %i\n", checksum);
	
	return 0;
	
}
