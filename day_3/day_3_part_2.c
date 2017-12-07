#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

#define NUMBER 277678
//#define NUMBER 805

#define R 0
#define U 1
#define L 2
#define D 3

#define REGULAR 0
#define ONE_BEFORE_TURN 1
#define TURN 2

#define SIZE 256

const int directions_length = 4;
int direction_index = 0;
int distance = 1;
int x = 0, y = 0;
int current_index = 1;
int current_number = 1;

int *array;
int array_num_reallocs = 0;

int top_left = 0;
int mid_left = 0;
int mid_right = 0;
int bottom_left = 0;
int bottom_right = 0;

int top_left_index = 1;

int status = REGULAR;
	
void move(){
	switch(status){
		
	/* Thinking of this: where x (mid_right) is next to be calculated
		origin is always to the left
	            _ _	
	   top_left|_|_|
	   mid_left|_|x|mid_right
	bottom_left|_|_|bottom_right
	
		top_left_index is for loading new values from array (previous layer)
	
	*/
		
		
		case TURN:
		
			top_left = mid_left;
			mid_left = mid_right;
			bottom_left = 0;
			bottom_right = 0;
		
			break;
			
		case ONE_BEFORE_TURN:
		
			bottom_left = mid_left;
			bottom_right = mid_right;
			mid_left = top_left;
			top_left = 0;
		
			break;
			
		case REGULAR:
		default:
		
			bottom_left = mid_left;
			bottom_right = mid_right;
			mid_left = top_left;
			top_left_index++;
			top_left = *(array+top_left_index);		
		
			break;
	}
	
	mid_right = top_left + mid_left + bottom_left + bottom_right;
	
	current_number = mid_right;
}

void calculate_position(){
	/* Use each distance twice */
	int i;
	int32_t j;
	
	array[current_index] = current_number;
	mid_right = current_number;
	
	while(1){
		for(i = 0; i < 2; i++){
			
			/* Use each direction *distance* times */
			for(j = 0; j < distance; j++){
				
				/* Work out which action to take according to how close a corner is */
				if(j == (distance - 1)){
					status = TURN;
				} else if (j == (distance - 2)){
					status = ONE_BEFORE_TURN;
				} else {
					status = REGULAR;
				}
				
				move();
				
				/* Make sure we have enough space for the next number in array */
				current_index++;
				if(current_index > (SIZE * array_num_reallocs)){
					array_num_reallocs++;
					array = realloc(array, (SIZE*array_num_reallocs));
				}
				/* Store number in array for later */
				*(array + current_index) = current_number;
				
				printf("New number, index %i: %i\n", current_index, current_number);
				
				/* Check if number is reached yet */
				if(current_number >= NUMBER){
					return;
				}
				
			}

			/* Increment index once per distance */
			direction_index++;
			direction_index = direction_index % directions_length;

		}
		
		/* Increment distance */
		distance++;	
	}

}

int main (int argc, char *argv[]){
	
	/* Start with 256, should be enough */
	array = malloc(SIZE);
	array_num_reallocs++;
	
	calculate_position();
	
	printf("First value larger is %i", current_number);

	return 0;
}
