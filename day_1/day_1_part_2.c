
#include <stdint.h>
#include <stdio.h>

//const char filename[] = "ex_part2.txt";
const char filename[] = "input_day_1.txt";

int sum = 0;
int current = 0;
int opposite = 0;
int number_of_digits = 0;
int halfway = 0;

int main (int argc, char *argv[]){

	FILE *file, *file2;
	file = fopen(filename, "r");
	char c, c2;	
	
	/* Count number of digits in file */
	fscanf(file, "%c", &c);
	while(!feof(file)){
		if(c != EOF){
			number_of_digits++;
		}
		fscanf(file, "%c", &c);
	}	
	printf("number of digits: %i\n", number_of_digits);
	/* Reset pointer to start of file */
	rewind(file);
	
	/* Get first character */
	fscanf(file, "%c", &c);	
		
	/* Use second file pointer for reading opposite chars */
	file2 = fopen(filename, "r");
	halfway = number_of_digits / 2;
	printf("halfway: %i\n", halfway);	

	/* interate so loops ends with c2 as char opposite first */
	while(halfway){
		fscanf(file2, "%c", &c2);
		halfway--;
	}
	fscanf(file2, "%c", &c2);
		
	/* while not end of file on file2 pointer */
	while(!feof(file)){
		
		/* Convert to integer */
		current = (int)c - 48;
		opposite = (int)c2 - 48;

		/* If the opposite integer matches current, add it to the sum */
		if(opposite == current){
			sum += current;
		}
		
		/* Get next characters */
		fscanf(file, "%c", &c);
		fscanf(file2, "%c", &c2);
		if(feof(file2)){
			rewind(file2);
			fscanf(file2, "%c", &c2);
		}
	}
	
	fclose(file);
	fclose(file2);
	
	printf("Total sum of matching digits is %i", sum);
	
	return 0;
	
}
