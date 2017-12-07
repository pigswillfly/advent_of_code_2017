
#include <stdint.h>
#include <stdio.h>

int sum = 0;
int current = 0;
int previous = 0;
int first = 0;

int main (int argc, char *argv[]){

	FILE *file;
	file = fopen("input_day_1.txt", "r");
	char c;	
		
	/* Get first character */
	fscanf(file, "%c", &c);
	first = (int)c - 48;
		
	/* while not end of file */
	while(!feof(file)){
		
		/* Convert to integer */
		current = (int)c - 48;

		/* If the previous integer matches current, add it to the sum */
		if(previous == current){
			sum += previous;
		}
		
		/* Store this character as previous for next round */
		previous = current;
		
		/* Get next character */
		fscanf(file, "%c", &c);
	}
	
	if(previous == first){
		sum += previous;
	}
	
	fclose(file);
	
	printf("Total sum of repeating digits is %i\n", sum);
	
	return 0;
	
}
