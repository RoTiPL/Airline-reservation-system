#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "Reservation.h"

RNode* R_Creat_Nill(RNode*root);
RNode* R_Create_Node(RNode *parent, RInfo info);
void R_Left_Rotate(RNode **r, RNode *x);
void R_Right_Rotate(RNode **r, RNode *y);
void R_RB_Insert_Fixup(RNode **r, RNode* x);
void R_RB_Insert(RNode** root, RInfo info);
void R_Tree_Transplant(RNode **r, RNode *t, RNode *c);
void R_Delete_Fixup(RNode **r, RNode *x);
void R_RB_Delete(RNode **r, int key);
void R_Print_Tree(RNode *node, int level);
RNode* R_Search(RNode* node, int value);
RNode* R_Comparison(RNode* node, int value);
RNode* R_Max(RNode* root);
RNode* R_Min(RNode* root);
RNode* R_Successor(RNode* node);
RNode* R_Predecessor(RNode* node);
void R_Show_Reserv_Info(RNode*root, int id);
RNode* R_Make_R_Tree();

// Red_Black 트리에 각 노드에 왼쪽과 오른쪽 자식에 들어갈 Nill 노드를 생성해 준다.
RNode* R_Creat_Nill(RNode*root) {
	RNode* Null = (RNode*)malloc(sizeof(RNode));
	Null->color = 'b';
	Null->ID = -100;
//	strcpy(Null->PW, 'shit');
	Null->budget = NULL;
	
	Null->peroid = NULL;
//	strcpy(Null->date,NULL);
	Null->left_child = NULL;
	Null->right_child = NULL;
	Null->Nill = NULL;
	root = Null;
	root->Nill = Null;
	return root;
}
// Red_Black 트리에 들어갈 노드를 생성해 준다.
RNode* R_Create_Node(RNode *parent, RInfo info) {
	RNode *Node = (RNode*)malloc(sizeof(RNode));
	Node->ID = info.ID;
	Node->budget = info.budget;
	Node->peroid = info.peroid;
	Node->remainder = info.remainder;
	strcpy(Node->Ssite, info.Ssite);
	strcpy(Node->Esite, info.Esite);
	Node->r_num = info.r_num;
	for (int loop = 0; loop < info.r_num; loop++) {
		Node->route[loop] = info.route[loop];
	}
	strcpy(Node->tranport, info.tranport);
	Node->transport_cost = info.transport_cost;
	strcpy(Node->hotel_name, info.hotel_name);
	Node->hotel_level = info.hotel_level;
	Node->hotel_duration = info.hotel_duration;
	Node->hotel_price = info.hotel_price;
	Node->transport_cost = info.transport_cost;
	Node->peroid = info.peroid;
	Node->T_cost = info.T_cost;
	Node->color = 'r';	
	Node->left_child = parent->Nill;
	Node->right_child = parent->Nill;
	Node->parent = parent;
	Node->Nill = parent->Nill;
	if (Node->parent == NULL)
		Node->color = 'b';
	else
		Node->color = 'r';
	return Node;
}
// Red_Black 트리 밸런스 맞출때 왼쪽에서 회전할때 작동하는 함수
void R_Left_Rotate(RNode **r, RNode *x){
	RNode *temp;

	temp = x->right_child;
	x->right_child = temp->left_child;

	if (temp->left_child != (*r)->Nill)
	{
		(temp->left_child)->parent = x;
	}

	temp->parent = x->parent;

	if (x->parent == (*r)->Nill)
	{
		(*r) = temp;
	}
	else if (x == (x->parent)->left_child)
	{
		(x->parent)->left_child = temp;
	}
	else
	{
		(x->parent)->right_child = temp;
	}

	temp->left_child = x;
	x->parent = temp;
}

// Red_Black 트리 밸런스 맞출때 오른쪽에서 회전할때 작동하는 함수
void R_Right_Rotate(RNode **r, RNode *y){
	RNode *temp;

	temp = y->left_child;
	y->left_child = temp->right_child;

	if (temp->right_child != (*r)->Nill)
	{
		(temp->right_child)->parent = y;
	}

	temp->parent = y->parent;

	if (y->parent == (*r)->Nill)
	{
		(*r) = temp;
	}
	else if (y == (y->parent)->left_child)
	{
		(y->parent)->left_child = temp;
	}
	else
	{
		(y->parent)->right_child = temp;
	}

	temp->right_child = y;
	y->parent = temp;
}
// ==================================	트리 균형 맞추는부분		==================================
void R_RB_Insert_Fixup(RNode **r, RNode* x){
	RNode *u = NULL;

	while ((x->parent)->color == 'r')
	{
		if (x->parent == (x->parent->parent)->left_child)
		{
			u = (x->parent->parent)->right_child;
			if (u->color == 'r')
			{
				(x->parent)->color = 'b';
				u->color = 'b';

				(x->parent->parent)->color = 'r';

				x = (x->parent->parent);
			}
			else
			{
				if (x == (x->parent)->right_child)
				{
					x = (x->parent);

					R_Left_Rotate(r, x);
				}

				(x->parent)->color = 'b';
				(x->parent->parent)->color = 'r';

				R_Right_Rotate(r, (x->parent->parent));
			}
		}
		else
		{
			u = (x->parent->parent)->left_child;
			if (u->color == 'r')
			{
				(x->parent)->color = 'b';
				u->color = 'b';

				(x->parent->parent)->color = 'r';

				x = (x->parent->parent);
			}
			else
			{
				if (x == (x->parent)->left_child)
				{
					x = (x->parent);

					R_Right_Rotate(r, x);
				}

				(x->parent)->color = 'b';
				(x->parent->parent)->color = 'r';

				R_Left_Rotate(r, (x->parent->parent));
			}
		}
	}
	(*r)->color = 'b';
}
// ==================================	트리 삽입부분		==================================
void R_RB_Insert(RNode** root, RInfo info) {
	RNode*z = R_Create_Node(*root, info);
	RNode* y = (*root)->Nill;
	RNode* x = (*root);
	if ((*root)->ID == z->ID) exit(1);
	while (x != (*root)->Nill) {
		y = x;
		if (z->ID < x->ID)
			x = x->left_child;
		else
			x = x->right_child;
	}
	z->parent = y;
	if (y == (*root)->Nill)
	{
		(*root) = z;
	}
	else {
		if (z->ID < y->ID)
			y->left_child = z;
		else
			y->right_child = z;
	}
	R_RB_Insert_Fixup(root, z);
}
void R_Tree_Transplant(RNode **r, RNode *t, RNode *c){
	if (t->parent == (*r)->Nill)
	{
		(*r) = c;
	}
	else if (t == (t->parent)->left_child)
	{
		(t->parent)->left_child = c;
	}
	else
	{
		(t->parent)->right_child = c;
	}

	c->parent = t->parent;
}

// ==================================	트리의 노드 제거부분		==================================

void R_Delete_Fixup(RNode **r, RNode *x){
	RNode *s = NULL;

	while ((x != (*r)) && (x->color == 'b'))
	{
		if (x == (x->parent)->left_child)
		{
			s = (x->parent)->right_child;
			if (s->color == 'r')
			{
				s->color = 'b';
				(x->parent)->color = 'r';
				R_Left_Rotate(r, x->parent);
				s = (x->parent)->right_child;
			}
			if ((s->left_child)->color == 'b' && (s->right_child)->color == 'b')
			{
				s->color = 'r';
				x = x->parent;
			}
			else if ((s->left_child)->color == 'r' && (s->right_child)->color == 'b')
			{
				s->color = 'r';
				(s->left_child)->color = 'b';
				R_Right_Rotate(r, s);
				s = (x->parent)->right_child;
			}
			if ((s->right_child)->color == 'r')
			{
				s->color = (x->parent)->color;
				(s->right_child)->color = 'b';
				(x->parent)->color = 'b';
				R_Left_Rotate(r, x->parent);

				x = (*r);
			}

		}
		else
		{
			s = (x->parent)->left_child;
			if (s->color == 'r')
			{
				s->color = 'b';
				(x->parent)->color = 'r';
				R_Right_Rotate(r, x->parent);
				s = (x->parent)->left_child;
			}
			if ((s->left_child)->color == 'b' && (s->right_child)->color == 'b')
			{
				s->color = 'r';
				x = x->parent;
			}
			else if ((s->right_child)->color == 'r' && (s->left_child)->color == 'b')
			{
				s->color = 'r';
				(s->right_child)->color = 'b';
				R_Left_Rotate(r, s);
				s = (x->parent)->left_child;
			}
			if ((s->left_child)->color == 'r')
			{
				s->color = (x->parent)->color;
				(s->left_child)->color = 'b';
				(x->parent)->color = 'b';
				R_Right_Rotate(r, x->parent);

				x = (*r);
			}
		}
	}

	x->color = 'b';
}
void R_RB_Delete(RNode **r, int key){
	RNode *target = (*r);
	RNode *temp = NULL;
	RNode *x = NULL;
	char t_clr;

	while (key != target->ID)
	{
		if (target->ID > key)
		{
			target = target->left_child;
		}
		else
		{
			target = target->right_child;
		}
		if (target == (*r)->Nill)
			return;
	}

	t_clr = target->color;

	if (target->left_child == (*r)->Nill)
	{
		x = target->right_child;
		R_Tree_Transplant(r, target, target->right_child);
	}
	else if (target->right_child == (*r)->Nill)
	{
		x = target->left_child;
		R_Tree_Transplant(r, target, target->left_child);
	}
	else
	{
		temp = target->right_child;

		while (temp->left_child != (*r)->Nill)
		{
			temp = temp->left_child;
		}

		t_clr = temp->color;
		x = temp->right_child;

		R_Tree_Transplant(r, temp, temp->right_child);
		temp->right_child = target->right_child;
		(temp->right_child)->parent = temp;

		R_Tree_Transplant(r, target, temp);
		temp->left_child = target->left_child;
		(temp->left_child)->parent = temp;
		temp->color = target->color;
	}

	if (t_clr == 'b')
	{
		R_Delete_Fixup(r, x);
	}

	free(target);
}

// ==================================	트리 출력부분	==================================
void R_Print_Tree(RNode *node, int level) {
	int i;
	// 현재 트리가 비어있지 않은 경우
	if (node->ID != -100) {
		R_Print_Tree(node->right_child, level + 1);
		printf("\n");
		if (level==1) {
			printf("Root->");
		}
		// i가 현재레벨보다 낮고 루트가 아닌 경우
		for (i = 0; i < level&& node->parent != NULL; i++) {
			printf("	");
		}
		// 자신의 위치에 데이터를 출력
		printf("%d[%c]", node->ID, node->color);
		R_Print_Tree(node->left_child, level + 1);
	}
}
// ==================================	트리의 정보 탐색부분	==================================
// value에 맞는 노드를 찾는 함수
RNode* R_Search(RNode* node, int value) {
	if (node == NULL) {
		return NULL;
	}
	if (node->ID == value)
		return node;
	else if (node->ID > value) {
		R_Search(node->left_child, value);
	}
	else if (node->ID < value) {
		R_Search(node->right_child, value);
	}
}
// 해당 값과 비슷한 노드 찾는 함수
RNode* R_Comparison(RNode* node, int value) {
	if (node->ID==value)
		return node;
	else if (node->ID > value) {
		if (node->left_child != node->Nill)
			R_Comparison(node->left_child, value);
		else
			return node;
	}
	else {
		if (node->right_child != node->Nill)
			R_Comparison(node->right_child, value);
		else
			return node;
	}
}
// 트리에서 최대값 노드 찾는 함수
RNode* R_Max(RNode* root) {
	if (root->right_child!=root->Nill) {
		R_Max(root->right_child);
	}
	return root;
}
// 트리에서 최솟값 노드 찾는 함수
RNode* R_Min(RNode* root) {
	if (root->left_child!=root->Nill) {
		R_Min(root->left_child);
	}
	return root;
}
// 해당 노드보다 뒤에 위치한 노드 찾는 함수
RNode* R_Successor(RNode* node) {
	RNode* temp;
	if (node->right_child != node->Nill) {
		return R_Min(node->right_child);
	}
	else {
		temp = node->parent;
		while (temp != node->Nill && node == temp->right_child)
		{
			node = temp;
			temp = temp->parent;
		}
		return temp;
	}
}
// 해당 노드보다 뒤에 위치한 노드 찾는 함수
RNode* R_Predecessor(RNode* node) {
	RNode* temp;
	if (node->left_child != node->Nill) {
		return R_Max(node->left_child);
	}
	else {
		temp = node->parent;
		while (temp != node->Nill && node == temp->left_child)
		{
			node = temp;
			temp = temp->parent;
		}
		return temp;
	}
}
void R_Show_Reserv_Info(RNode*root,int id) {
	RNode *box;
	box = R_Search(root, 4);
	printf("\n\n");
	printf("ID:%d\tTotal_Cost:%d\n", box->ID, box->budget);
}
RNode* R_Make_R_Tree() {
	RNode* root = (RNode*)malloc(sizeof(RNode));
	RNode **T = &root;
	root = R_Creat_Nill(root);
	return root;
}
//int main(){
//	RInfo sample[10];
//	RNode **root = (RNode*)malloc(sizeof(RNode));
//	for (int loop = 0; loop < 10; loop++) {
//		sample[loop].budget = 10000;
//		sample[loop].ID = loop + 1;
//		//strcpy(sample[loop].PW , 'p');
//		sample[loop].peroid = 10;
//		sample[loop].remainder = 0;
//	}
//	root = R_Make_R_Tree();
//	for (int index = 0; index < 10; index++) {
//		R_RB_Insert(&root, sample[index]);
//	}
//	R_Print_Tree(root, 1);
//	R_Show_Reserv_Info(root,5);
//}