#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct _HNode {
	char name[10];
	struct _HNode *parent;
	struct _HNode *left_child;
	struct _HNode *right_child;
	struct _HNode *Nill;
	int price;
	int duration;
	int level;
	char color;
}HNode;
typedef struct HotelInfo {
	char name[10];
	int level;
	int price;
	int duration;
}HInfo;
// Nill ��带 ����� �ִ� �Լ�
HNode *Creat_Nill(HNode*root);
// ȣ�� ��带 ������ִ� �Լ�
HNode *Create_Node(HNode *parent, HInfo info);
// ���ʿ��� ȸ����Ű�� �Լ�
void Left_Rotate(HNode **r, HNode *x);
// �����ʿ��� ȸ����Ű�� �Լ�
void Right_Rotate(HNode **r, HNode *y);
// ���Խ� Ʈ���� ������ �����ִ� �Լ�
void RB_Insert_Fixup(HNode **r, HNode* x);
// Ʈ���� ��带 �����ϴ� �Լ�
void RB_Insert(HNode** root, HInfo info);
// Ʈ���� ��带 �ű�� �Լ�
void Tree_Transplant(HNode **r, HNode *t, HNode *c);
// ���Ž� Ʈ���� ������ �����ִ� �Լ�
void Delete_Fixup(HNode **r, HNode *x);
// Ʈ���� ��带 �����ϴ� �Լ�
void RB_Delete(HNode **r, int key);
// Ʈ���� ����� ����ϴ� �Լ�
void Print_Tree(HNode *node, int level);
// value���� ���� ���� ��带 ã�Ƽ� ��ȯ�ϴ� �Լ�
HNode* Comparison(HNode* node, int value);
// Ʈ������ ���� ū ���� ��带 ��ȯ�ϴ� �Լ�
HNode* Max(HNode* root);
// Ʈ������ ���� ���� ���� ��带 ��ȯ�ϴ� �Լ�
HNode* Min(HNode* root);
// Ʈ������ �ڽ��� ������ ���������� �ڿ� �ִ� ��带 ��ȯ�ϴ� �Լ�
HNode* Successor(HNode* node);
// Ʈ������ �ڽ��� ������ ���������� �տ� �ִ� ��带 ��ȯ�ϴ� �Լ�
HNode* Predecessor(HNode* node);
// Ʈ���� ���̸� ���ϴ� �Լ�
int Height(HNode *node);
// ȣ���� ������ �迭�� �����ϴ� �Լ�
void Load_Data(char list[][30]);
// ȣ���� ������ �����ϰ� �Ҵ��ϴ� �Լ�
void Random_Generate(HInfo*arr, int size, char Hname[][30]);
// ���꿡 �´� ���� 5�� ȣ��(������ 5���� ���� ���� �� �ִ�.) �������� 5�� ȣ���� ���� �迭�� ��ȯ�ϴ� �Լ�
HInfo* Show_list(HNode*root, int info);
// ȣ�� Red_Black_Tree�� ����� �Լ�
HNode* Make_Hotel_tree(char Hname[][30]);