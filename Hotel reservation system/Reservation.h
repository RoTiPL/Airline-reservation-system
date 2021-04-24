#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// 예약과 관련된 정보
typedef struct Reserve_info {
	int ID;
	int budget;
	int remainder;
	int peroid;
	int T_cost;
	char Ssite[10];
	char Esite[10];
	char tranport[20];
	int transport_cost;
	int route[100];
	int r_num;
	char hotel_name[20];
	int hotel_level;
	int hotel_duration;
	int hotel_price;
}RInfo;

// 예약정보를 담을 노드 정보
typedef struct _RNode {
	struct _RNode *parent;
	struct _RNode *left_child;
	struct _RNode *right_child;
	struct _RNode *Nill;
	int ID;
	int budget;
	int remainder;
	int peroid;
	int T_cost;
	char color;
	char Ssite[10];
	char Esite[10];
	char tranport[20];
	int transport_cost;
	int route[100];
	int r_num;
	char hotel_name[20];
	int hotel_level;
	int hotel_duration;
	int hotel_price;
}RNode;

// Nill 노드를 만들어주는 함수
RNode* R_Creat_Nill(RNode*root);
// 새로운 노드를 남들어주는 함수
RNode* R_Create_Node(RNode *parent, RInfo info);
// Red_balck_tree에서 왼쪽에서 오른쪽으로 회전시키는 함수
void R_Left_Rotate(RNode **r, RNode *x);
// Red_balck_tree에서 오른쪽에서 오른쪽으로 회전시키는 함수
void R_Right_Rotate(RNode **r, RNode *y);
// Red_black_tree에서 균형을 맞춰주는 함수
void R_RB_Insert_Fixup(RNode **r, RNode* x);
// Red_black_tree에서 노드를 삽입시켜주는 함수
void R_RB_Insert(RNode** root, RInfo info);
// Red_black_Tree에서 노드를 옮겨주는 함수
void R_Tree_Transplant(RNode **r, RNode *t, RNode *c);
// Red_balck_Tree에서 노드를 제거한 이후 균형을 맞춰주는 함수
void R_Delete_Fixup(RNode **r, RNode *x);
// Red_black_Tree에서 노드를 제거하는 함수
void R_RB_Delete(RNode **r, int key);
// Red_Balck_tree에서 전체 트리모양을 출력해주는함수
void R_Print_Tree(RNode *node, int level);
// 해당 value값과 일치하는 노드를을 찾는 함수
RNode* R_Search(RNode* node, int value);
// value값과 비슷한 값을 찾는 함수(자신이 삽입되기 전 Parent의 노드를 반환한다)
RNode* R_Comparison(RNode* node, int value);
// Red_black_tree에서 가장 큰 값을 찾는 함수
RNode* R_Max(RNode* root);
// Red_balck_tree에서 가장 작은 값을 찾는 함수
RNode* R_Min(RNode* root);
// Red_black_tree에서 자신보다 큰값의 노드를 반환하는 함수
RNode* R_Successor(RNode* node);
// Red_Balck_tree에서 자신보다 작은값의 노드를 반환하는 함수
RNode* R_Predecessor(RNode* node);
void R_Show_Reserv_Info(RNode*root, int id);
// Red_black_tree를 만들어주는 함수
RNode* R_Make_R_Tree();
