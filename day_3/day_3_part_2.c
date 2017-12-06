#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define NUMBER 277678

#define R 0
#define U 1
#define L 2
#define D 3

const int directions_length = 4;
int direction_index = 0;
int32_t distance = 1;
int32_t x = 0, y = 0;
int32_t current_number = 1;

	
void move(){
	switch(direction_index){
		case R:{
			x++; 
			//printf("move right\n");
			break;	
		} 
		case U:{
			y++; 
			//printf("move up\n");
			break;
		} 
		case L: {
			x--;
			//printf("move left\n");
			break;
		} 
		case D: {
			y--; 
			//printf("move down\n");
			break;
		}
	}
}

void calculate_position(){
	/* Use each distance twice */
	int i;
	int32_t j;
	while(1){
		for(i = 0; i < 2; i++){
			
			/* Use each direction *distance* times */
			for(j = 0; j < distance; j++){
				move();
				current_number++;
				//printf("current number is %u\n", current_number);
				
				if(current_number == NUMBER){
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
	
	calculate_position();
	int32_t distance = (abs(x) + abs(y));
	
	printf("Distance is %i", distance);

	return 0;
}
