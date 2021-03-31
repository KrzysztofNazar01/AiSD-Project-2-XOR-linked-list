#include "Projekt2.h"

char input[MAX_INPUT_LENGTH];

int main() {
	while (scanf("%49s", input) != EOF) {
		int com_index = 0;

		if (get_command(&com_index)) {
			int value = 0;
			get_value(com_index, value);
			do_command(com_index, value);
		}
		else
			printf("Incorrect input\n");
	}
    return 0;
}

bool get_command(int *com_index) {
	char commands[COM_COUNT][COM_LENGTH]{
	"ADD_BEG",
	"ADD_END",
	"ADD_ACT",
	"DEL_VAL",
	"ACTUAL",
	"NEXT",
	"PREV" ,
	"DEL_BEG" ,
	"DEL_END" ,
	"DEL_ACT" ,
	"PRINT_FORWARD" ,
	"PRINT_BACKWARD"
	};

    for (int j = 0; j < COM_COUNT; j++) {
        if (strcmp(input, commands[j]) == 0) {
            *com_index = j;
            return true;
        }
    }
    return false;
}

void do_command(int com_index, int value) {

	switch (com_index) {
		case ADD_BEG:
				XORList.add_beg(value);
			break;
		case ADD_END:
				XORList.add_end(value);
			break;
		case ADD_ACT:
				XORList.add_actual(value);
			break;
		case DEL_VAL:
				XORList.del_value(value);
			break;
		case ACTUAL:
				XORList.show_actual();
			break;
		case NEXT:
				XORList.next_actual();
			break;
		case PREV:
				XORList.prev_actual();
			break;
		case DEL_BEG:
				XORList.del_beg();
			break;
		case DEL_END:
				XORList.del_end();
			break;
		case DEL_ACT:
				XORList.del_actual();
			break;
		case PRINT_FORWARD:
				XORList.print_forward();
			break;
		case PRINT_BACKWARD:
				XORList.print_backward();
			break;
	}
}

void get_value(int com_index, int& value) {
	if (com_index == ADD_BEG || com_index == ADD_END || com_index == ADD_ACT || com_index == DEL_VAL)
		scanf_s("%10d", &value);
}

node* XOR(struct node* x, struct node* y) {
	return (node*)((uintptr_t)(x) ^ (uintptr_t)(y));
}