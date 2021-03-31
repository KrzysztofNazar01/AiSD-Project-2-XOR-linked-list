#ifdef kopiaaaa

#include "Projekt2.h"
class XORLinkedList {
private:
	node* head, * tail, * actual, * previous, * following;

public:
	void set_actual() {
		if (arr_size == 0)
			previous = actual = following = tail = head = NULL;

		if (arr_size == 1)
			previous = actual = following = tail = head;

		if (arr_size == 2) {
			if (actual == head)
				previous = following = tail;
			else
				previous = following = head;
		}

		if (arr_size == 3) {
			if (actual == head) { //AFP
				previous = tail;
				following = XOR(NULL, actual->npx);
			}
			else if (actual == tail) { //FPA
				following = head;
				previous = XOR(NULL, actual->npx);
			}
			else { //PAF
				previous = head;
				following = tail;
			}
		}

		if (arr_size >= 4) {
			if (actual == head) {//AFXP
				following = XOR(actual->npx, NULL);
				previous = tail;
			}
			else if (XOR(head->npx, NULL) == actual) {//PAFX
				previous = head;
				following = XOR(tail->npx, NULL);
			}
			else if (actual == XOR(tail->npx, NULL)) {//XPAF
				following = tail;
				previous = XOR(actual->npx, tail);
			}
			else if (actual == tail) {//FXPA
				previous = XOR(actual->npx, NULL);
				following = head;
			}
		}
	}

	void add_beg(int value) {
		node* newnode = new node;
		newnode->value = value;

		if (head == NULL) {
			newnode->npx = NULL;
			head = tail = newnode;
		}
		else {
			newnode->npx = XOR(NULL, head);
			head->npx = XOR(newnode, XOR(NULL, head->npx));
			head = newnode;
		}
		arr_size++;
		set_actual();
	}
	void add_end(int value) {
		node* newnode = new node;
		newnode->value = value;

		if (NULL == head) {
			newnode->npx = NULL;
			head = tail = newnode;
		}
		else {
			newnode->npx = XOR(tail, NULL);
			tail->npx = XOR(newnode, XOR(tail->npx, NULL));
			tail = newnode;
		}
		arr_size++;
		set_actual();
	}
	void add_actual(int value) {
		if (arr_size <= 1 || actual == head)
			add_beg(value);
		else {
			node* newnode = new node;
			newnode->value = value;
			newnode->npx = XOR(previous, actual);

			previous->npx = XOR(newnode, XOR(actual, previous->npx));
			actual->npx = XOR(newnode, XOR(previous, actual->npx));
			previous = newnode;
			arr_size++;
		}
	}

	void del_end() {
		if (head != NULL) {
			node* newnode = tail;
			node* prev = XOR(newnode->npx, NULL);

			if (NULL == prev)
				head = NULL;
			else
				prev->npx = XOR(newnode, XOR(prev->npx, NULL));

			tail = prev;

			arr_size--;
			set_actual();
		}
	}
	void del_beg() {
		if (head != NULL) {
			node* next = XOR(head->npx, NULL);

			if (next == NULL)
				tail = NULL;
			else
				next->npx = XOR(head, XOR(next->npx, NULL));

			head = next;

			arr_size--;
			set_actual();
		}
	}

	void del_actual() {
		if (actual != NULL) {
			if (arr_size == 1) {
				arr_size--;
				set_actual();
			}
			else {
				if (actual == head) {
					actual = tail;
					del_beg();
				}
				else if (actual == tail) {
					actual = head;
					del_end();
				}
				else {
					node* newnode = new node;
					following->npx = XOR(previous, XOR(actual, following->npx));
					previous->npx = XOR(following, XOR(actual, previous->npx));
					newnode = XOR(previous->npx, following);
					actual = previous;
					previous = newnode;

					arr_size--;
					set_actual();
				}
			}
		}
	}
	void del_value(int value) {
		if (head != NULL) {
			if (arr_size == 1) {
				arr_size--;
				set_actual();
			}
			else {
				node* prev = NULL, * curr = head, * foll = XOR(prev, curr->npx);
				node* f2;
				f2 = XOR(curr, foll->npx);

				while (curr != NULL) {
					if (curr->value == value) {
						if (curr == head || curr == tail) {
							if (curr == head) {
								del_beg();
								curr = head;
							}
							if (curr == tail) {
								del_end();
								curr = NULL;
							}
						}
						else {
							prev->npx = XOR(prev->npx, XOR(curr, f2));
							f2->npx = XOR(f2->npx, XOR(curr, prev));
							curr = f2;
							f2 = XOR(prev, curr->npx);
							arr_size--;
						}
					}
					else {
						foll = XOR(prev, curr->npx);
						prev = curr;
						curr = foll;
						if (curr != NULL)
							f2 = XOR(prev, curr->npx);
					}
				}
			}
		}
	}

	void show_actual() {
		if (actual != NULL)
			printf("%d\n", actual->value);
		else
			printf(" NULL ");
	}
	void next_actual() {
		actual = following;
		set_actual();
		show_actual();
	}
	void prev_actual() {
		actual = previous;
		set_actual();
		show_actual();
	}
	void print_backward() {
		if (head != NULL) {
			node* curr = tail;
			node* next = NULL, * prev;

			while (NULL != curr) {
				printf("%d ", curr->value);
				prev = XOR(next, curr->npx);
				next = curr;
				curr = prev;
			}

			printf("\n");
		}
		else
			printf("NULL\n");
	}
	void print_forward() {
		if (head != NULL) {
			node* curr = head;
			node* prev = NULL, * next;

			while (NULL != curr) {
				printf("%d ", curr->value);
				next = XOR(prev, curr->npx);
				prev = curr;
				curr = next;
			}

			printf("\n");
		}
		else
			printf("NULL\n");
	}

} XORList;



node* head, * tail, * actual, * previous, * following;
unsigned int arr_size;
char input[MAX_INPUT_LENGTH];

int main() {
	while (scanf("%49s", input) != EOF) {
		int com_index = 0;

		if (get_command(&com_index)) {
			int value = 0;
			do_command(com_index, value);
		}
		else
			printf("Incorrect input\n");
	}
	return 0;
}


void get_value(int com_index, int& value) {
	if (com_index == ADD_BEG || com_index == ADD_END || com_index == ADD_ACT || com_index == DEL_VAL)
		scanf_s("%10d", &value);
}

bool get_command(int* com_index) {
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


node* XOR(struct node* x, struct node* y) {
	return (node*)((uintptr_t)(x) ^ (uintptr_t)(y));
}

void set_actual() {
	if (arr_size == 0)
		previous = actual = following = tail = head = NULL;

	if (arr_size == 1)
		previous = actual = following = tail = head;

	if (arr_size == 2) {
		if (actual == head)
			previous = following = tail;
		else
			previous = following = head;
	}

	if (arr_size == 3) {
		if (actual == head) { //AFP
			previous = tail;
			following = XOR(NULL, actual->npx);
		}
		else if (actual == tail) { //FPA
			following = head;
			previous = XOR(NULL, actual->npx);
		}
		else { //PAF
			previous = head;
			following = tail;
		}
	}

	if (arr_size >= 4) {
		if (actual == head) {//AFXP
			following = XOR(actual->npx, NULL);
			previous = tail;
		}
		else if (XOR(head->npx, NULL) == actual) {//PAFX
			previous = head;
			following = XOR(tail->npx, NULL);
		}
		else if (actual == XOR(tail->npx, NULL)) {//XPAF
			following = tail;
			previous = XOR(actual->npx, tail);
		}
		else if (actual == tail) {//FXPA
			previous = XOR(actual->npx, NULL);
			following = head;
		}
	}
}

void add_beg(int value) {
	node* newnode = new node;
	newnode->value = value;

	if (head == NULL) {
		newnode->npx = NULL;
		head = tail = newnode;
	}
	else {
		newnode->npx = XOR(NULL, head);
		head->npx = XOR(newnode, XOR(NULL, head->npx));
		head = newnode;
	}
	arr_size++;
	set_actual();
}
void add_end(int value) {
	node* newnode = new node;
	newnode->value = value;

	if (NULL == head) {
		newnode->npx = NULL;
		head = tail = newnode;
	}
	else {
		newnode->npx = XOR(tail, NULL);
		tail->npx = XOR(newnode, XOR(tail->npx, NULL));
		tail = newnode;
	}
	arr_size++;
	set_actual();
}
void add_actual(int value) {
	if (arr_size <= 1 || actual == head)
		add_beg(value);
	else {
		node* newnode = new node;
		newnode->value = value;
		newnode->npx = XOR(previous, actual);

		previous->npx = XOR(newnode, XOR(actual, previous->npx));
		actual->npx = XOR(newnode, XOR(previous, actual->npx));
		previous = newnode;
		arr_size++;
	}
}

void del_end() {
	if (head != NULL) {
		node* newnode = tail;
		node* prev = XOR(newnode->npx, NULL);

		if (NULL == prev)
			head = NULL;
		else
			prev->npx = XOR(newnode, XOR(prev->npx, NULL));

		tail = prev;

		arr_size--;
		set_actual();
	}
}
void del_beg() {
	if (head != NULL) {
		node* next = XOR(head->npx, NULL);

		if (next == NULL)
			tail = NULL;
		else
			next->npx = XOR(head, XOR(next->npx, NULL));

		head = next;

		arr_size--;
		set_actual();
	}
}

void del_actual() {
	if (actual != NULL) {
		if (arr_size == 1) {
			arr_size--;
			set_actual();
		}
		else {
			if (actual == head) {
				actual = tail;
				del_beg();
			}
			else if (actual == tail) {
				actual = head;
				del_end();
			}
			else {
				node* newnode = new node;
				following->npx = XOR(previous, XOR(actual, following->npx));
				previous->npx = XOR(following, XOR(actual, previous->npx));
				newnode = XOR(previous->npx, following);
				actual = previous;
				previous = newnode;

				arr_size--;
				set_actual();
			}
		}
	}
}
void del_value(int value) {
	if (head != NULL) {
		if (arr_size == 1) {
			arr_size--;
			set_actual();
		}
		else {
			node* prev = NULL, * curr = head, * foll = XOR(prev, curr->npx);
			node* f2;
			f2 = XOR(curr, foll->npx);

			while (curr != NULL) {
				if (curr->value == value) {
					if (curr == head || curr == tail) {
						if (curr == head) {
							del_beg();
							curr = head;
						}
						if (curr == tail) {
							del_end();
							curr = NULL;
						}
					}
					else {
						prev->npx = XOR(prev->npx, XOR(curr, f2));
						f2->npx = XOR(f2->npx, XOR(curr, prev));
						curr = f2;
						f2 = XOR(prev, curr->npx);
						arr_size--;
					}
				}
				else {
					foll = XOR(prev, curr->npx);
					prev = curr;
					curr = foll;
					if (curr != NULL)
						f2 = XOR(prev, curr->npx);
				}
			}
		}
	}
}

void show_actual() {
	if (actual != NULL)
		printf("%d\n", actual->value);
	else
		printf(" NULL ");
}
void next_actual() {
	actual = following;
	set_actual();
	show_actual();
}
void prev_actual() {
	actual = previous;
	set_actual();
	show_actual();
}
void print_backward() {
	if (head != NULL) {
		node* curr = tail;
		node* next = NULL, * prev;

		while (NULL != curr) {
			printf("%d ", curr->value);
			prev = XOR(next, curr->npx);
			next = curr;
			curr = prev;
		}

		printf("\n");
	}
	else
		printf("NULL\n");
}
void print_forward() {
	if (head != NULL) {
		node* curr = head;
		node* prev = NULL, * next;

		while (NULL != curr) {
			printf("%d ", curr->value);
			next = XOR(prev, curr->npx);
			prev = curr;
			curr = next;
		}

		printf("\n");
	}
	else
		printf("NULL\n");
}


void do_command(int com_index, int value) {

	get_value(com_index, value);

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
#endif
