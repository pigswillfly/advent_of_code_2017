

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define NUM_REGISTERS 1000
#define LINE_STRING_SIZE 100
#define NAME_SIZE	10
#define OP_SIZE 3
#define INC_DEC_SIZE 4

const char less_than[OP_SIZE] = "<";
const char greater_than[OP_SIZE] = ">";
const char less_than_equal[OP_SIZE] = "<=";
const char greater_than_equal[OP_SIZE] = ">=";
const char equals[OP_SIZE] = "==";
const char not_equal[OP_SIZE] = "!=";

const char increase[INC_DEC_SIZE] = "inc";
const char decrease[INC_DEC_SIZE] = "dec";

//const char filename[] = "ex_input_day_8.txt";
const char filename[] = "day_8_input.txt";

typedef struct reg_t {
	char name[NAME_SIZE];
	int value;
} reg_t;


char line_string[LINE_STRING_SIZE];
reg_t *registers;
int register_index = 0;


char op_reg_name[NAME_SIZE];
char inc_dec[INC_DEC_SIZE];
int op_by;
char condition_reg_name[NAME_SIZE];
char condition_op[OP_SIZE];
int condition_op_by;
	
void reset(){
	int i;
	for(i = 0; i < NAME_SIZE; i++){
		if(i < OP_SIZE){
			condition_op[i] = 0;
		}
		if(i < INC_DEC_SIZE){
			inc_dec[i] = 0;
		}
		op_reg_name[i] = 0;
		condition_reg_name[i] = 0;
	}
	op_by = 0;
	condition_op_by = 0;
}

reg_t *get_reg(char *n){
	int i;
	reg_t *ret_reg = NULL;
	
	for(i = 0; i < register_index; i++){
		if(strncmp(n,(registers + i)->name, NAME_SIZE) == 0){
			ret_reg = (registers + i);
			break;
		}
	}
	
	if(ret_reg == NULL){
		ret_reg = (registers + register_index);
		register_index++;
	
		strncpy(ret_reg->name, n, NAME_SIZE);
		ret_reg->value = 0;
	}
	
	return ret_reg;	
}

int find_largest_value(){
	
	int i, largest_val = (registers)->value;
	
	for(i = 1; i < register_index; i++){
		if((registers + i)->value > largest_val){
			largest_val = (registers + i)->value;	
		}
	}
	return largest_val;
	
}

int main (int argc, char *argv[]){

	FILE *file;
	file = fopen(filename, "r");

	registers = malloc(sizeof(reg_t) * NUM_REGISTERS);
	
	int i, line;
	char *string_pointer = line_string;
		
	do{
		// get line
		fgets(line_string, LINE_STRING_SIZE, file);
		line++;
		
		sscanf(string_pointer, "%s %s %i if %s %s %i",
								op_reg_name,
								inc_dec,
								&op_by,
								condition_reg_name,
								condition_op,
								&condition_op_by);
								
		// check if reg exists, if not, create
		reg_t *op_reg = get_reg(op_reg_name);
		reg_t *condition_reg = get_reg(condition_reg_name);
		
		
		
		//find out if condition is true
		int condition = 0;
		
		if(strncmp(condition_op, less_than, OP_SIZE) == 0){
			if(condition_reg->value < condition_op_by){
				condition = 1;
			}
		} else if(strncmp(condition_op, greater_than, OP_SIZE) == 0){
			if(condition_reg->value > condition_op_by){
				condition = 1;
			}			
		
		} else if(strncmp(condition_op, greater_than_equal, OP_SIZE) == 0){
			if(condition_reg->value >= condition_op_by){
				condition = 1;
			}
		} else if(strncmp(condition_op, less_than_equal, OP_SIZE) == 0){
			if(condition_reg->value <= condition_op_by){
				condition = 1;
			}
		} else if(strncmp(condition_op, equals, OP_SIZE) == 0){
			if(condition_reg->value == condition_op_by){
				condition = 1;
			}
		} else if(strncmp(condition_op, not_equal, OP_SIZE) == 0){
			if(condition_reg->value != condition_op_by){
				condition = 1;
			}
		}
		
		if(condition == 1){
			// operate on register
			if(strncmp(inc_dec, increase, INC_DEC_SIZE) == 0){
				
				op_reg->value += op_by;
				
			} else if(strncmp(inc_dec, decrease, INC_DEC_SIZE) == 0){
				
				op_reg->value -= op_by;
				
			}
			
		}
		
		printf("%s --- Line %i: condition %i\n", line_string, line, condition);
		
	} while(!feof(file));
	
	int largest_value = find_largest_value();
	
	printf("\nLargest value in any register is %i\n", largest_value);
	
	fclose(file);

	return 0;
	
}
