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
// Nill 노드를 만들어 주는 함수
HNode *Creat_Nill(HNode*root);
// 호텔 노드를 만들어주는 함수
HNode *Create_Node(HNode *parent, HInfo info);
// 왼쪽에서 회전시키는 함수
void Left_Rotate(HNode **r, HNode *x);
// 오른쪽에서 회전시키는 함수
void Right_Rotate(HNode **r, HNode *y);
// 삽입시 트리의 균형을 맞춰주는 함수
void RB_Insert_Fixup(HNode **r, HNode* x);
// 트리에 노드를 삽입하는 함수
void RB_Insert(HNode** root, HInfo info);
// 트리에 노드를 옮기는 함수
void Tree_Transplant(HNode **r, HNode *t, HNode *c);
// 제거시 트리의 균형을 맞춰주는 함수
void Delete_Fixup(HNode **r, HNode *x);
// 트리에 노드를 제거하는 함수
void RB_Delete(HNode **r, int key);
// 트리의 모양을 출력하는 함수
void Print_Tree(HNode *node, int level);
// value보다 작은 값의 노드를 찾아서 반환하는 함수
HNode* Comparison(HNode* node, int value);
// 트리에서 가장 큰 값의 노드를 반환하는 함수
HNode* Max(HNode* root);
// 트리에서 가장 작은 값의 노드를 반환하는 함수
HNode* Min(HNode* root);
// 트리에서 자신의 값보다 순서적으로 뒤에 있는 노드를 반환하는 함수
HNode* Successor(HNode* node);
// 트리에서 자신의 값보다 순서적으로 앞에 있는 노드를 반환하는 함수
HNode* Predecessor(HNode* node);
// 트리에 높이를 구하는 함수
int Height(HNode *node);
// 호텔의 정보를 배열에 저장하는 함수
void Load_Data(char list[][30]);
// 호텔의 정보를 랜덤하게 할당하는 함수
void Random_Generate(HInfo*arr, int size, char Hname[][30]);
// 예산에 맞는 상위 5개 호텔(없을시 5개를 만족 못할 수 있다.) 최저가격 5개 호텔을 담은 배열을 반환하는 함수
HInfo* Show_list(HNode*root, int info);
// 호텔 Red_Black_Tree를 만드는 함수
HNode* Make_Hotel_tree(char Hname[][30]);