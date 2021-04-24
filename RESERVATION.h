#ifndef RESERVATION_H
#define RESERVATION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//#define RED 0
//#define BLACK 1
/*
typedef struct RBTREE {
	struct RBTREE *parent;
	struct RBTREE *leftchild;
	struct RBTREE *rightchild;
	struct RBTREE *NILL;
	int color;
	char name[20];
	int resevation_number;
	char source;
	char destination;
	int departure_time[25];
	int departure_date[25];
	int arrival_time[25];
	int arrival_date[25];
	int flight_time; //excluding wait time for transfer
	char flight_path[26];
	int is_direct;
	int budget; // ?ãúÍ∞ÑÍ≥º ÎπÑÏö© ?Ç¨?ù¥ ?Ñ†?Éù
	char ticket_grade;
	int number_visiting_city;
} RBTREE;
*/
typedef enum _COLOR { Black, Red } Color;

typedef struct _RNODE {
	struct _RNODE* left;
	struct _RNODE* right;
	struct _RNODE* parent;
	enum _COLOR rb;
	int key;

	char name[20];
	int resevation_number;
	char source;
	char destination;
	int departure_time[25];
	int departure_date[25];
	int arrival_time[25];
	int arrival_date[25];
	int flight_time; //excluding wait time for transfer
	char flight_path[26];
	int is_direct;
	int budget; // ?ãúÍ∞ÑÍ≥º ÎπÑÏö© ?Ç¨?ù¥ ?Ñ†?Éù
	char ticket_grade;
	int number_visiting_city;
} RNode;

typedef struct _RBT {
	struct _RNODE* root;
	struct _RNODE* NIL;
} RBT;

void INSERT_INFORMATION(RNode *T, char name[20], char source, char destination, char ticket_grade, int number_visiting_city);
void INSERT_SCHEDULE(RBT* rbt, int reservation_number, char departure_time[25], char departure_date[25], int arrival_time[25], int arrival_date[25], int flight_time, char flight_path[26]);
void PRINT_RESERVATION_INFORMATION(RBT* rbt, int resevation_number);
RBT* RB_INIT();
RNode* CREATE_NODE(RBT*, int, Color);
void RB_INSERT(RBT*, int);
RNode* RB_DELETE(RBT*, int);
void RB_INSERT_FIXUP(RBT*, RNode*);
void RB_DELETE_FIXUP(RBT*, RNode*);
void LEFT_ROTATE(RBT*, RNode*);
void RIGHT_ROTATE(RBT*, RNode*);
RNode* TREE_SUCCESSOR(RBT*, RNode*);
RNode* MINIMUM(RBT*, RNode*);
RNode* SEARCH_NODE(RBT*, int);

#endif