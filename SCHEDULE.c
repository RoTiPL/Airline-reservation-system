#include "SCHEDULE.h"

int CreateSchedule(int x) {
	int dep_time;
	srand((unsigned)time(NULL));
	int y = rand() % 24;
	int z = rand() % 60;
	dep_time = x * 1440 + y * 60 + z; //�ð��� ���? �� ������ �ٲ�. (x�� ������ 0~30�̹Ƿ� ���߿� 1~31�� �ٲ������?.)

	return dep_time;
}

int*** CreateMonthSchedule(Graph* pgraph){
	int*** Month = (int***)calloc(40, sizeof(int**));
	for(int i=0; i<40; i++){
		Month[i] = (int**)calloc(30, sizeof(int*));
		for(int j=0; j<30; j++){
			Month[i][j] = (int*)calloc(30, sizeof(int));
		}
	}
	
	for(int date=0; date<=30; date++){
		for(int i=0; i<26; i++){
			Node* cur = pgraph->heads[i]->next;
			while(cur != NULL){
				int dest = cur->id;
				int dis = cur->distance;
				int today = CreateSchedule(date);
				Month[date][i][dest] = today;
				cur = cur->next;
			}
		}
	}

	return Month;
}
