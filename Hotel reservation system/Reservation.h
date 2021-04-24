#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// ����� ���õ� ����
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

// ���������� ���� ��� ����
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

// Nill ��带 ������ִ� �Լ�
RNode* R_Creat_Nill(RNode*root);
// ���ο� ��带 ������ִ� �Լ�
RNode* R_Create_Node(RNode *parent, RInfo info);
// Red_balck_tree���� ���ʿ��� ���������� ȸ����Ű�� �Լ�
void R_Left_Rotate(RNode **r, RNode *x);
// Red_balck_tree���� �����ʿ��� ���������� ȸ����Ű�� �Լ�
void R_Right_Rotate(RNode **r, RNode *y);
// Red_black_tree���� ������ �����ִ� �Լ�
void R_RB_Insert_Fixup(RNode **r, RNode* x);
// Red_black_tree���� ��带 ���Խ����ִ� �Լ�
void R_RB_Insert(RNode** root, RInfo info);
// Red_black_Tree���� ��带 �Ű��ִ� �Լ�
void R_Tree_Transplant(RNode **r, RNode *t, RNode *c);
// Red_balck_Tree���� ��带 ������ ���� ������ �����ִ� �Լ�
void R_Delete_Fixup(RNode **r, RNode *x);
// Red_black_Tree���� ��带 �����ϴ� �Լ�
void R_RB_Delete(RNode **r, int key);
// Red_Balck_tree���� ��ü Ʈ������� ������ִ��Լ�
void R_Print_Tree(RNode *node, int level);
// �ش� value���� ��ġ�ϴ� ��带�� ã�� �Լ�
RNode* R_Search(RNode* node, int value);
// value���� ����� ���� ã�� �Լ�(�ڽ��� ���ԵǱ� �� Parent�� ��带 ��ȯ�Ѵ�)
RNode* R_Comparison(RNode* node, int value);
// Red_black_tree���� ���� ū ���� ã�� �Լ�
RNode* R_Max(RNode* root);
// Red_balck_tree���� ���� ���� ���� ã�� �Լ�
RNode* R_Min(RNode* root);
// Red_black_tree���� �ڽź��� ū���� ��带 ��ȯ�ϴ� �Լ�
RNode* R_Successor(RNode* node);
// Red_Balck_tree���� �ڽź��� �������� ��带 ��ȯ�ϴ� �Լ�
RNode* R_Predecessor(RNode* node);
void R_Show_Reserv_Info(RNode*root, int id);
// Red_black_tree�� ������ִ� �Լ�
RNode* R_Make_R_Tree();
