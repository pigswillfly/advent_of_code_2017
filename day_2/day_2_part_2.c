
#include <stdint.h>
#include <stdio.h>

#define SIZE 256

//const char filename[] = "ex2_input_day_2.txt";
const char filename[] = "day_2_input.txt";

char string[SIZE];
char *space_finder = string;
int numbers[30];
int number_index = 0;
int last_number = 0;
int numerator = 0, denominator = 0;
int divtotal = 0;


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
			//printf("number is %i\n", number);
			if(number != 0){
				numbers[number_index++] = number;
			}				
			
			/* Find beginning of next number */
			while(*space_finder != ' '){
				if((*space_finder == '\n') || (*space_finder == 0)){
					last_number = 1;
					//printf("last number\n");
					break;
				}
				space_finder++;
				
			}
			space_finder++; // now pointing at next number			
			
		}while(!last_number);
		
		
		int i,j;
		numerator = 0;
		denominator = 0;

		for(i = 0; i < number_index; i++){
			
			for(j = 0; j < number_index; j++){
				
				if(i == j) continue;
				
				if(numbers[i] > numbers[j]){
					if((numbers[i] % numbers[j]) == 0){
						numerator = numbers[i];
						denominator = numbers[j];
					}
				}
				
				if(numerator != 0){
					break;
				}
				
			}
			
			if(denominator != 0){
				break;
			}
			
			//printf("%i ", numbers[i]);

			
			
		}
		
		int division = numerator / denominator;
		
		printf("Line %i division is %i div %i = %i\n", line, numerator, denominator, division);
		
		divtotal += division;
		
		reset();

		
	}
	
	
	fclose(file);

	printf("Division total is %i\n", divtotal);
	
	return 0;
	
}
