#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "Hotel.h"

//typedef struct _HNode {
//	char name[10];
//	struct _HNode *parent;
//	struct _HNode *left_child;
//	struct _HNode *right_child;
//	struct _HNode *Nill;
//	int price;
//	int duration;
//	int level;
//	char color;
//}HNode;
//typedef struct HotelInfo {
//	char name[10];
//	int level;
//	int price;
//	int duration;
//}HInfo;
HNode *Creat_Nill(HNode*root);
HNode *Create_Node(HNode *parent, HInfo info);
void Left_Rotate(HNode **r, HNode *x);
void Right_Rotate(HNode **r, HNode *y);
void RB_Insert_Fixup(HNode **r, HNode* x);
void RB_Insert(HNode** root, HInfo info);
void Tree_Transplant(HNode **r, HNode *t, HNode *c);
void Delete_Fixup(HNode **r, HNode *x);
void RB_Delete(HNode **r, int key);
void Print_Tree(HNode *node, int level);
HNode* Comparison(HNode* node, int value);
HNode* Max(HNode* root);
HNode* Min(HNode* root);
HNode* Successor(HNode* node);
HNode* Predecessor(HNode* node);
int Height(HNode *node);
void Load_Data(char list[][30]);
void Random_Generate(HInfo*arr, int size, char Hname[][30]);
HInfo* Show_list(HNode*root, int info);
HNode* Make_Hotel_tree(char Hname[][30]);

// Red_Black 트리에 각 노드에 왼쪽과 오른쪽 자식에 들어갈 Nill 노드를 생성해 준다.
HNode* Creat_Nill(HNode*root) {
	HNode* Null = (HNode*)malloc(sizeof(HNode));
	Null->color = 'b';
	Null->price = -100;
	Null->left_child = NULL;
	Null->right_child = NULL;
	Null->Nill = NULL;
	root = Null;
	root->Nill = Null;
	return root;
}
// Red_Black 트리에 들어갈 노드를 생성해 준다.
HNode *Create_Node(HNode *parent, HInfo info) {
	HNode *Node = (HNode*)malloc(sizeof(HNode));
	strcpy(Node->name,info.name);
	Node->level = info.level;
	Node->price = info.price;
	Node->duration = info.duration;
	Node->parent = parent;
	Node->left_child = parent->Nill;
	Node->right_child = parent->Nill;
	Node->Nill = parent->Nill;
	if (Node->parent == NULL)
		Node->color = 'b';
	else
		Node->color = 'r';
	return Node;
}
// ==================================	트리 균형 맞추는부분		==================================
void RB_Insert_Fixup(HNode **r, HNode* x)
{
	HNode *u = NULL;

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

					Left_Rotate(r, x);
				}

				(x->parent)->color = 'b';
				(x->parent->parent)->color = 'r';

				Right_Rotate(r, (x->parent->parent));
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

					Right_Rotate(r, x);
				}

				(x->parent)->color = 'b';
				(x->parent->parent)->color = 'r';

				Left_Rotate(r, (x->parent->parent));
			}
		}
	}
	(*r)->color = 'b';
}
// Red_Black 트리 밸런스 맞출때 왼쪽에서 회전할때 작동하는 함수
void Left_Rotate(HNode **r, HNode *x)
{
	HNode *temp;

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
// Red_Black 트리 밸런스 맞출때 왼쪽에서 회전할때 작동하는 함수
void Right_Rotate(HNode **r, HNode *y)
{
	HNode *temp;

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
// ==================================	트리 삽입하는 부분		==================================
void RB_Insert(HNode** root, HInfo info) {
	HNode*z = Create_Node(*root, info);
	HNode* y = (*root)->Nill;
	HNode* x = (*root);
	if ((*root)->price == z->price) exit(1);
	while (x != (*root)->Nill) {
		y = x;
		if (z->price < x->price)
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
		if (z->price < y->price)
			y->left_child = z;
		else
			y->right_child = z;
	}
	RB_Insert_Fixup(root, z);
}
void Tree_Transplant(HNode **r, HNode *t, HNode *c)
{
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

void Delete_Fixup(HNode **r, HNode *x)
{
	HNode *s = NULL;

	while ((x != (*r)) && (x->color == 'b'))
	{
		if (x == (x->parent)->left_child)
		{
			s = (x->parent)->right_child;
			if (s->color == 'r')
			{
				s->color = 'b';
				(x->parent)->color = 'r';
				Left_Rotate(r, x->parent);
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
				Right_Rotate(r, s);
				s = (x->parent)->right_child;
			}
			if ((s->right_child)->color == 'r')
			{
				s->color = (x->parent)->color;
				(s->right_child)->color = 'b';
				(x->parent)->color = 'b';
				Left_Rotate(r, x->parent);

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
				Right_Rotate(r, x->parent);
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
				Left_Rotate(r, s);
				s = (x->parent)->left_child;
			}
			if ((s->left_child)->color == 'r')
			{
				s->color = (x->parent)->color;
				(s->left_child)->color = 'b';
				(x->parent)->color = 'b';
				Right_Rotate(r, x->parent);

				x = (*r);
			}
		}
	}

	x->color = 'b';
}
// ==================================	트리의 노드 제거부분		==================================
void RB_Delete(HNode **r, int key)
{
	HNode *target = (*r);
	HNode *temp = NULL;
	HNode *x = NULL;
	char t_clr;

	while (key != target->price)
	{
		if (target->price > key)
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
		Tree_Transplant(r, target, target->right_child);
	}
	else if (target->right_child == (*r)->Nill)
	{
		x = target->left_child;
		Tree_Transplant(r, target, target->left_child);
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

		Tree_Transplant(r, temp, temp->right_child);
		temp->right_child = target->right_child;
		(temp->right_child)->parent = temp;

		Tree_Transplant(r, target, temp);
		temp->left_child = target->left_child;
		(temp->left_child)->parent = temp;
		temp->color = target->color;
	}

	if (t_clr == 'b')
	{
		Delete_Fixup(r, x);
	}

	free(target);
}
// ==================================	트리 출력부분		==================================
void Print_Tree(HNode *node, int level) {
	int i;
	// 현재 트리가 비어있지 않은 경우
	if (node->price != -100) {
		Print_Tree(node->right_child, level + 1);
		printf("\n");
		if (level==1) {
			printf("Root->");
		}
		// i가 현재레벨보다 낮고 루트가 아닌 경우
		for (i = 0; i < level&& node->parent != NULL; i++) {
			printf("	");
		}
		// 자신의 위치에 데이터를 출력
		printf("%d[%c]", node->price, node->color);
		Print_Tree(node->left_child, level + 1);
	}
}
// ==================================	트리 검색부분		==================================
// 해당 값을 찾는 함수
HNode* Search(HNode* node, int value) {
	if (node == NULL) {
		return NULL;
	}
	if (node->price == value)
		return node;
	else if (node->price > value) {
		Search(node->left_child, value);
	}
	else if (node->price < value) {
		Search(node->right_child, value);
	}
}
// 해당 값과 가까운 값 찾는 함수
HNode* Comparison(HNode* node, int value) {
	if (node->price==value)
		return node;
	else if (node->price > value) {
		if (node->left_child != node->Nill)
			Comparison(node->left_child, value);
		else
			return node;
	}
	else {
		if (node->right_child != node->Nill)
			Comparison(node->right_child, value);
		else
			return node;
	}
}
// 트리에서 가장 큰 노드 찾는 함수
HNode* Max(HNode* root) {
	if (root->right_child!=root->Nill) {
		Max(root->right_child);
	}
	return root;
}
// 트리에서 가장 작은 노드 찾는 함수
HNode* Min(HNode* root) {
	if (root->left_child!=root->Nill) {
		Min(root->left_child);
	}
	return root;
}
// 트리에서 해당 노드의 뒤에 값 찾는 함수
HNode* Successor(HNode* node) {
	HNode* temp;
	if (node->right_child != node->Nill) {
		return Min(node->right_child);
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
// 트리에서 해당 노드의 앞의 값 찾는 함수
HNode* Predecessor(HNode* node) {
	HNode* temp;
	if (node->left_child != node->Nill) {
		return Max(node->left_child);
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
// 트리의 높이 확인하는 함수
int Height(HNode *node) {
	int r = 0, l = 0;
	int max = 0;
	if (node->right_child->price != -100)
		r = Height(node->right_child);
	if (node->left_child->price != -100)
		l = Height(node->left_child);
	max = (r>l) ? r : l;
	return 1 + max;
}
// 텍스트 파일 읽어서 배열에 저장하는 함수
void Load_Data(char list[][30]) {
	int index = 0;
	char buffer[100];
	FILE *file_pointer = fopen("hotels.txt", "r");
	if (file_pointer == NULL) {
		printf("File Open  Error\n");
		exit(0);
	}
	while (!feof(file_pointer)) {
		fscanf(file_pointer,"%s\n",list[index]);
		index++;
	}
	fclose(file_pointer);
}
// 임의로 호텔자료 생성하는 함수
void Random_Generate(HInfo*arr,int size,char Hname[][30]) {
	int loop = 0;
	char num[4];
	HInfo Info;
	int index = 0;
	while (loop < size) {
		Info.price = ((rand() % size+1)*300)+6000;
		Info.duration = 8;
		Info.level = (int)Info.price / 6000 +(rand()%2);
		strcpy(Info.name,Hname[loop]);
		arr[loop] = Info;
		for (int i = 0; i < loop; i++) {
			if (arr[i].price == arr[loop].price) {
				loop--;
				break;
			}
		}
		loop++;
	}
}
// 해당 예산으로 가능한 상위 5개 호텔 정보와 최소 금액 하위 5개 호텔 정보를 제공하는 함수
HInfo* Show_list(HNode*root, int info) {
	HNode* node = Comparison(root, info);
	HNode* temp = (HNode*)malloc(sizeof(HNode));
	//HNode* box[10];
	HInfo *box = malloc(sizeof(HInfo) * 10);
	printf("\n==========================================상위 5개 리스트==========================================\n");
	int loop = 0;
	while (loop < 5) {
		temp = Predecessor(node);
		// 만일 해당 가격이 없을때 loop문을 종료시킨다.
		if (temp->price < 0)
		{
			printf("여기까지 이용가능한 호텔이었습니다.\n");
			loop = 5;
		}
		else {
			printf("(%2d) Name:%12s\tlevel:%d\t\tPrice:%d\tduration:%d\n",loop+1, temp->name, temp->level, temp->price, temp->duration);
			strcpy(box[loop].name, temp->name);
			box[loop].level = temp->level;
			box[loop].duration = temp->duration;
			box[loop].price = temp->price;
			node = temp;
			loop++;
		}
	}
	printf("\n==========================================하위 5개 리스트==========================================\n");
	// 최소값 노드 찾는 과정
	HNode*cur = root;
	while (cur->left_child != root->Nill)
		cur = cur->left_child;
	while (loop < 10) {
		if (temp->price < 0)
		{
			printf("여기까지 이용가능한 호텔이었습니다.\n");
			loop = 10;
		}
		else {
			printf("(%2d) Name:%12s\tlevel:%d\t\tPrice:%d\tduration:%d\n", loop + 1, cur->name, cur->level, cur->price, cur->duration);
			strcpy(box[loop].name, cur->name);
			box[loop].level = cur->level;
			box[loop].duration = cur->duration;
			box[loop].price = cur->price;
			cur = Successor(cur);
			loop++;
		}
	}
	return box;
}
// 호텔 Red_Black_Tree를 만드는 함수
HNode* Make_Hotel_tree(char Hname[][30]) {
	HNode* root = (HNode*)malloc(sizeof(HNode));
	HNode **T = &root;
	int A[20] = { 0 , };
	srand(time(NULL));
	HInfo list[100];
	int size = 100;
	Random_Generate(list, size, Hname);
	root = Creat_Nill(root);
	for (int index = 0; index < 100; index++) {
		RB_Insert(T, list[index]);
	}
	return root;
}
//int main() {
//	char Hname[110][30] = { 0 ,};
//	HNode* Hroot = (HNode*)malloc(sizeof(HNode));
//	HInfo *box;
//	//HNode **table=NULL;
//	Load_Data(Hname);
//	Hroot = Make_Hotel_tree(Hname);
//	//Print_Tree(root, 1);
//	//table = Show_list(Hroot, 300000);
//	box = Show_list(Hroot, 250000);
//	//printf("%s\t%d\n",table[9]->name, table[9]->price);
//	printf("name:%s\tprice:%d\n", box[3].name, box[3].price);
//	return  0;
//}