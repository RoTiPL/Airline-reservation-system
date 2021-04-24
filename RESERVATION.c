#include "RESERVATION.h"

int date (float time ){
    return time/1440;
}
int hour (float time ){
    int a= (int)time%1440;
    return a/60;
}
int minute(float time){
    int a=(int)time%1440;
    return a%60;
}

void INSERT_INFORMATION(RNode *T, char name[20], char source, char destination, char ticket_grade, int number_visiting_city) {
	for (int i = 0; i < 20; i++) {
		T->name[i] = name[i];
	}
	T->source = source;
	T->destination = destination;
	T->ticket_grade = ticket_grade;
}

void INSERT_SCHEDULE(RBT* rbt, int reservation_number, char departure_time[25], char departure_date[25], int arrival_time[25], int arrival_date[25], int flight_time, char flight_path[26]) {
	
	RNode* T = SEARCH_NODE(rbt, reservation_number);
	for (int i = 0; i < 25; i++) {
		T->departure_time[i] = departure_time[i];
		T->departure_date[i] = departure_date[i];
		T->arrival_time[i] = arrival_time[i];
		T->arrival_date[i] = arrival_date[i];
		T->flight_path[i] = flight_path[i];
	}
	T->flight_path[25] = flight_path[25];
	T->flight_time = flight_time;

}
void PRINT_RESERVATION_INFORMATION(RBT* rbt, int resevation_number){
	RNode* T = SEARCH_NODE(rbt, resevation_number);
	printf("Resevation number: %d \n", T->resevation_number);
	printf("Departure: %c \n", T->source);
	printf("Departure date & Departure time: %d / %d \n", T->departure_date, T->departure_time);
	printf("Destination: %c \n", T->destination);
	printf("Arrival date & Arrival time: %d / %d \n", T->arrival_date, T->arrival_time);
	puts("");
	
}

RBT* RB_INIT() {
	RBT* tree = (RBT*)malloc(sizeof(RBT));
	tree->NIL = (RNode*)malloc(sizeof(RNode));
	tree->NIL->left = tree->NIL->right = tree->NIL->parent = NULL;
	tree->NIL->rb = Black;
	tree->root = tree->NIL;
	return tree;
}

RNode* CREATE_NODE(RBT* rbt, int data, Color color) {
	RNode* newNode = (RNode*)malloc(sizeof(RNode));
	newNode->key = data;
	newNode->left = newNode->right = newNode->parent = rbt->NIL;
	newNode->rb = color;
	return newNode;
}

void RB_INSERT(RBT * rbt, int data) {
	RNode* y = rbt->NIL;
	RNode* x = rbt->root;
	RNode* z = CREATE_NODE(rbt, data, Red);

	while (x != rbt->NIL) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		}
		else if (z->key > x->key){
			x = x->right;
		}
		else{
			printf("You already reservated");
			return;
		}
	}
	z->parent = y;
	if (y == rbt->NIL) {
		rbt->root = z;
	}
	else {
		if (z->key < y->key) {
			y->left = z;
		}
		else {
			y->right = z;
		}
	}

	z->left = rbt->NIL;
	z->right = rbt->NIL;
	RB_INSERT_FIXUP(rbt, z);
}

void RB_INSERT_FIXUP(RBT * rbt, RNode * z) {
	while (z->parent->rb == Red) {
		if (z->parent == z->parent->parent->left) {
			RNode* y = z->parent->parent->right;
			if (y->rb == Red) {
				z->parent->rb = Black;
				y->rb = Black;
				z->parent->parent->rb = Red;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					LEFT_ROTATE(rbt, z);
				}
				z->parent->rb = Black;
				z->parent->parent->rb = Red;
				RIGHT_ROTATE(rbt, z->parent->parent);
			}
		}
		else {
			RNode* y = z->parent->parent->left;
			if (y->rb == Red) {
				z->parent->rb = Black;
				y->rb = Black;
				z->parent->parent->rb = Red;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					RIGHT_ROTATE(rbt, z);
				}
				z->parent->rb = Black;
				z->parent->parent->rb = Red;
				LEFT_ROTATE(rbt, z->parent->parent);
			}
		}
	}
	rbt->root->rb = Black;
}

RNode* RB_DELETE(RBT * rbt, int data) {
	RNode* z = SEARCH_NODE(rbt, data);
	RNode* y;
	RNode* x;

	if (z == NULL){
		printf("There is not the key in the Tree");
		return NULL;
	}
	
	if (z->left == rbt->NIL || z->right == rbt->NIL) {
		y = z;
	}
	else {
		y = TREE_SUCCESSOR(rbt, z);
	}
	
	if (y->left != rbt->NIL) {
		x = y->left;
	}
	else {
		x = y->right;
	}
	x->parent = y->parent;
	if (y->parent == rbt->NIL) {
		rbt->root = x;
	}
	else {
		if (y == y->parent->left) {
			y->parent->left = x;
		}
		else
		{
			y->parent->right = x;
		}
	}
	if (y != x) {
		z->key = y->key;
	}
	if (y->rb == Black) {
		RB_DELETE_FIXUP(rbt, x);
	}
	return y;
}

void RB_DELETE_FIXUP(RBT * rbt, RNode * x) {
	while (x != rbt->root && x->rb == Black) {
		if (x == x->parent->left) {
			RNode* w = x->parent->right;
			if (w->rb = Red) {
				w->rb = Black;
				x->parent->rb = Red;
				LEFT_ROTATE(rbt, x->parent);
				w = x->parent->right;
			}
			if (w->left->rb == Black && w->right->rb == Black) {
				w->rb = Red;
				x = x->parent;
			}
			else {
				if (w->right->rb == Black) {
					w->left->rb = Black;
					w->rb = Red;
					RIGHT_ROTATE(rbt, w);
					w = x->parent->right;
				}
				w->rb = x->parent->rb;
				x->parent->rb = Black;
				w->right->rb = Black;
				LEFT_ROTATE(rbt, x->parent);
				x = rbt->root;
			}
		}
		else {
			RNode* w = x->parent->left;
			if (w->rb = Red) {
				w->rb = Black;
				x->parent->rb = Red;
				RIGHT_ROTATE(rbt, x->parent);
				w = x->parent->left;
			}
			if (w->left->rb == Black && w->right->rb == Black) {
				w->rb = Red;
				x = x->parent;
			}
			else {
				if (w->left->rb == Black) {
					w->right->rb = Black;
					w->rb = Red;
					LEFT_ROTATE(rbt, w);
					w = x->parent->left;
				}
				w->rb = x->parent->rb;
				x->parent->rb = Black;
				w->left->rb = Black;
				RIGHT_ROTATE(rbt, x->parent);
				x = rbt->root;
			}
		}
	}
	x->rb = Black;
}

void LEFT_ROTATE(RBT * rbt, RNode * x) {
	RNode* y = x->right;
	x->right = y->left;
	if (y->left != rbt->NIL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == rbt->NIL) {
		rbt->root = y;
	}
	else {
		if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
	}
	y->left = x;
	x->parent = y;
}

void RIGHT_ROTATE(RBT * rbt, RNode * x) {
	RNode* y = x->left;
	x->left = y->right;
	if (y->right != rbt->NIL) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == rbt->NIL) {
		rbt->root = y;
	}
	else {
		if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
	}
	y->right = x;
	x->parent = y;
}

RNode* TREE_SUCCESSOR(RBT* rbt, RNode * x) {
	if (x->right != rbt->NIL) {
		return MINIMUM(rbt, x->right);
	}
	else {
		RNode* y = x->parent;
		while (y != rbt->NIL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}
}

RNode* MINIMUM(RBT* rbt, RNode * x) {
	while (x->left != rbt->NIL) {
		x = x->left;
	}
	return x;
}

RNode* SEARCH_NODE(RBT * rbt, int data) {
	RNode* cur = rbt->root;
	while (cur != rbt->NIL && cur->key != data) {

		if (data < cur->key) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}

	return cur;
}

void PRINT_BST(RBT* rbt, RNode* root, int height) {
	if (root == rbt->NIL) return;

	height += 10;

	PRINT_BST(rbt, root->right, height);
	printf("\n");
	for (int i = 10; i < height; i++) {
		printf(" ");
	}
	printf("%d", root->key);
	if (root->rb == Red) printf("|R\n");
	else if(root->rb == Black) printf("|B\n");
	PRINT_BST(rbt, root->left, height);
}