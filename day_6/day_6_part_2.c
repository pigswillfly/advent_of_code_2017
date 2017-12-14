
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_BANKS 16
//#define NUM_BANKS 4
#define MAX_STATES 20000

const int start_state[NUM_BANKS] = {4, 1, 15, 12, 0, 9, 9, 5, 5, 8, 7, 3, 14, 5, 12, 3};
//const int start_state[NUM_BANKS] = {0, 2, 7, 0};

int states[MAX_STATES][NUM_BANKS];
int current_state;
int repeat_state;

int find_biggest_bank(){
	
	int biggest = 0;
	
	int i;
	for(i = 1; i < NUM_BANKS; i++){
		if(states[current_state][i] > states[current_state][biggest]){
			biggest = i;
		}
	}
	
	return biggest;
}

void reallocate(int biggest_index){
	
	int i;
	for(i = 0; i < NUM_BANKS; i++){
		states[current_state][i] = states[current_state - 1][i];
	}
	
	int num = states[current_state][biggest_index];
	states[current_state][biggest_index] = 0;
	
	i = (biggest_index + 1) % NUM_BANKS;
	do{
		states[current_state][i] += 1;
		num--;
		i = (i + 1)%NUM_BANKS;
		
	}while(num);
	
}

int matches(int *bank1, int *bank2){
	
	int match = 1;
	
	int i;
	for(i = 0; i < NUM_BANKS; i++){
		if(*(bank1 + i) != *(bank2 + i)){
			match = 0;
			break;
		}
	}
	
	return match;
	
}

int has_been_seen_before(){
	
	int seen = 0;
	
	int i, j;
	
	for(j = 0; j < current_state; j++){
			
		if(matches(states[current_state], states[j])){
			seen = 1;
			break;
		}
		
	}
	
	return seen;
}

void print_states(int until){
	
	int i, j;
	for(j = 0; j < until; j++){
		for(i = 0; i < NUM_BANKS; i++){
			
			printf("%i ", states[j][i]);
			
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]){
	
	int seen_before = 0;
	int last_repeat_state = -1;
	
	int i;
	for(i = 0; i < NUM_BANKS; i++){
		states[0][i] = start_state[i];
	}
	
	current_state = 0;
	
	do{
		int biggest = find_biggest_bank();
		
		current_state++;
		if(current_state == MAX_STATES){
			
			//print_states(MAX_STATES);
			
			return 0;
		}
		
		reallocate(biggest);
		
		if(seen_before == 0){
			if(has_been_seen_before()){
				seen_before++;				
				printf("Repeat at state %i\n", current_state);
				last_repeat_state = current_state;
			}	
		} else {
			if(matches(states[current_state], states[last_repeat_state])){
				seen_before++;
				printf("Repeat again after %i states\n", current_state - last_repeat_state);
				last_repeat_state = current_state;
			}
		}

		
		if(seen_before == 3){
			//print_states(current_state + 1);
			return 0;
		}
		
		
	} while(1);
	
	return 0;
}